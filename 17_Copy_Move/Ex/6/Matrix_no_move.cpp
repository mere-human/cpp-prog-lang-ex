/*
[6] (*3) Implement a simple Matrix along the lines of the one in ch.17.5.2.
Measure the performance of an addition of 1000-by-1000 matrices with and
without move operations. If you did not have the option of adding move
operations, what would you do?
*/
#include <iostream>
#include <ctime>

// Version w/o move
// Reults (clang C++03):
// default: ~75,4
// MATRIX_USE_PLUS_EQ: ~57,7
// MATRIX_SHARED: 54,2

// verbose output, helps to ensure everything works okay, should be used with small dimension
//#define VERBOSE_OUTPUT

// use operator+= instead of operator+
//#define MATRIX_USE_PLUS_EQ

// Use approach similar to std::shared_ptr (which was absent in C++03)
//#define MATRIX_SHARED

template<typename T>
class Matrix
{
  int dim0; // 2 dimensions
  int dim1;
  T* elem; // ptr to dim0*dim1 elems of type T
#ifdef MATRIX_SHARED
  int* cnt;
#endif
public:
  Matrix(int d1, int d2) : dim0(d1), dim1(d2), elem(0) // simplified
  {
    if (d1 != d2)
      throw std::runtime_error("only square matrices are supported for now");
    elem = new T[d1*d2];
#ifdef MATRIX_SHARED
    cnt = new int(1);
#endif
  }

  ~Matrix()
  {
    remove_ref();
  }

  int size() const { return rows() * cols(); }

  int rows() const { return dim0; }

  int cols() const { return dim1; }

  // copy ctor
#ifdef MATRIX_SHARED
  Matrix(const Matrix& m)
    : dim0(m.dim0), dim1(m.dim1),
      elem(m.elem),
      cnt(m.cnt)
  {
    ++(*cnt);
  }
#else
  Matrix(const Matrix& m)
    : dim0(m.dim0), dim1(m.dim1),
    elem(new T[m.size()])
  {
    std::copy(m.elem, m.elem + m.size(), elem); // copy elems
  }
#endif

  // copy assignment
#ifdef MATRIX_SHARED
  Matrix& operator=(const Matrix& m)
  {
    if (&m != this)
    {
      remove_ref();
      cnt = m.cnt;
      elem = m.elem;
      ++(*cnt);
    }
    return *this;
  }
#else
  Matrix& operator=(const Matrix& m)
  {
    // self assignment is safe
    Matrix tmp(m); // make a copy
    std::swap(tmp, *this); // swap representation
    return *this;
  }
#endif

#ifndef MATRIX_SHARED
  Matrix& operator+=(const Matrix& b)
  {
    if (dim0 != b.dim0 || dim1 != b.dim1)
      throw std::runtime_error("unequal Matrix sizes in +");
    const int n = size();
    for (int i = 0; i != n; ++i)
      elem[i] += b.elem[i];
    return *this;
  }
#endif

  template<typename U>
  friend Matrix<U> operator+(const Matrix<U>& a, const Matrix<U>& b);

  const T& operator()(int i, int j) const { return elem[pos(i, j)]; }
  T& operator()(int i, int j) { return elem[pos(i, j)]; }

private:
  int pos(int i, int j) const { return dim0 * i + j; }
  void remove_ref()
  {
    // simplified
    if (--(*cnt) == 0)
    {
      delete[] elem;
      delete cnt;
    }
  }
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
  // res[i][j] = a[i][j] + b[i][j] for each i and j
  if (a.dim0 != b.dim0 || a.dim1 != b.dim1)
    throw std::runtime_error("unequal Matrix sizes in +");
  Matrix<T> res(a.dim0, a.dim1);
  const int n = a.size();
  for (int i = 0; i != n; ++i)
    res.elem[i] = a.elem[i] + b.elem[i];
  return res;
}

void fill(Matrix<double>& mm)
{
  for (int i = 0; i != mm.rows(); ++i)
  {
    for (int j = 0; j != mm.cols(); ++j)
      mm(i, j) = std::rand() % 100;
  }
}

void print(const Matrix<double>& mm)
{
  for (int i = 0; i != mm.rows(); ++i)
  {
    for (int j = 0; j != mm.cols(); ++j)
      std::cout << mm(i, j) << " ";
    std::cout << "\n";
  }
}

int main()
{
  std::srand(123);
  const int dim = 1000;

  Matrix<double> m1(dim, dim);
  fill(m1);
#ifdef VERBOSE_OUTPUT
  std::cout << "M1:\n";
  print(m1);
#endif

  Matrix<double> m2(dim, dim);
  fill(m2);
#ifdef VERBOSE_OUTPUT
  std::cout << "M2:\n";
  print(m2);
#endif

  const std::clock_t t0 = std::clock();
#ifdef MATRIX_USE_PLUS_EQ
  Matrix<double> m3(m1);
  m3 += m2;
#else
  Matrix<double> m3(m1 + m2);
#endif
  const std::clock_t t1 = std::clock();
#ifdef VERBOSE_OUTPUT
  std::cout << "M3:\n";
  print(m3);
#endif
  std::cout << "duration, ms: " << (1000.0 * (t1 - t0) / CLOCKS_PER_SEC) << "\n";

  return 0;
}
