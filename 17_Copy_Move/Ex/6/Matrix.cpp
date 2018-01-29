/*
[6] (*3) Implement a simple Matrix along the lines of the one in ch.17.5.2.
Measure the performance of an addition of 1000-by-1000 matrices with and
without move operations. If you did not have the option of adding move
operations, what would you do?
*/
#include <array>
#include <iostream>
#include <chrono>

// If move is not available:
// - copy and operator+= instead of operator+
// - use private constructor which takes pointer and imitate move with copy (as was done in std::auto_ptr)
// - use function add() which takes reference to result
// Reults:
// clang, duration, ms: ~25
// clang, MATRIX_DELETE_MOVE, duration, ms: ~100
// clang, MATRIX_DELETE_MOVE, MATRIX_USE_PLUS_EQ: ~40
// clang, MATRIX_DELETE_MOVE, MATRIX_USE_NO_MOVE_WORKAROUND: ~25
// MSVC, duration, ms: ~5
// MSVC, MATRIX_DELETE_MOVE:
// Error	C2280	'Matrix<double>::Matrix(Matrix<double> &&)': attempting to reference a deleted function
// MSVC, MATRIX_DELETE_MOVE, MATRIX_USE_PLUS_EQ: ~5

// move constructor and operator are =delete-d
//#define MATRIX_DELETE_MOVE

// use operator+= instead of operator+
//#define MATRIX_USE_PLUS_EQ

// use workaround for operator+ when move is not available
//#define MATRIX_USE_NO_MOVE_WORKAROUND

template<typename T>
class Matrix
{
  std::array<int, 2> dim; // 2 dimensions
  T* elem; // ptr to dim[0]*dim[1] elems of type T
public:
  explicit Matrix(int d1, int d2) : dim{ d1, d2 }, elem{ nullptr } // simplified
  {
    if (d1 != d2)
      throw std::runtime_error("only square matrices are supported for now");
    elem = new T[d1*d2];
  }

  int size() const { return rows() * cols(); }

  int rows() const { return dim[0]; }

  int cols() const { return dim[1]; }

  // copy ctor
  Matrix(const Matrix& m)
    : dim{ m.dim },
    elem{ new T[m.size()] }
  {
    std::uninitialized_copy(m.elem, m.elem + m.size(), elem); // copy elems
  }

  // copy assignment
  Matrix& operator=(const Matrix& m)
  {
    // self assignment is safe
    Matrix tmp{ m }; // make a copy
    std::swap(tmp, *this); // swap representation
    return *this;
  }

  // move ctor
#ifdef MATRIX_DELETE_MOVE
  Matrix(Matrix&& m) = delete;
#else
  Matrix(Matrix&& m)
    : dim{ m.dim }, // grab representation
    elem{ m.elem }
  {
    // clear representation
    m.dim = { 0, 0 };
    m.elem = nullptr;
  }
#endif

  // move assignment
#ifdef MATRIX_DELETE_MOVE
  Matrix& operator=(Matrix&& m) = delete;
#else
  Matrix& operator=(Matrix&& m)
  {
    // swap representations
    std::swap(dim, m.dim);
    std::swap(elem, m.elem);
    return *this;
  }
#endif

  Matrix& operator+=(const Matrix& b)
  {
    if (dim[0] != b.dim[0] || dim[1] != b.dim[1])
      throw std::runtime_error("unequal Matrix sizes in +");
    const auto n = size();
    for (int i = 0; i != n; ++i)
      elem[i] += b.elem[i];
    return *this;
  }

  template<typename U>
  friend Matrix<U> operator+(const Matrix<U>& a, const Matrix<U>& b);

  const T& operator()(int i, int j) const { return elem[pos(i, j)]; }
  T& operator()(int i, int j) { return elem[pos(i, j)]; }

private:
  int pos(int i, int j) const { return dim[0] * i + j; }
#ifdef MATRIX_USE_NO_MOVE_WORKAROUND
  Matrix(int d1, int d2, T* e) : dim{ d1, d2 }, elem{ e } {}
  T* take()
  {
    T* tmp = elem;
    elem = nullptr;
    return tmp;
  }
#endif
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
  // res[i][j] = a[i][j] + b[i][j] for each i and j
  if (a.dim[0] != b.dim[0] || a.dim[1] != b.dim[1])
    throw std::runtime_error("unequal Matrix sizes in +");
  Matrix<T> res{ a.dim[0], a.dim[1] };
  const auto n = a.size();
  for (int i = 0; i != n; ++i)
    res.elem[i] = a.elem[i] + b.elem[i];
#ifdef MATRIX_USE_NO_MOVE_WORKAROUND
  return{ a.dim[0], a.dim[1], res.take() };
#else
  return res; // move
#endif
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
  //std::cout << "M1:\n";
  //print(m1);

  Matrix<double> m2(dim, dim);
  fill(m2);
  //std::cout << "M2:\n";
  //print(m2);

  using hrc = std::chrono::high_resolution_clock;
  using ms = std::chrono::milliseconds;

  auto t0 = hrc::now();
#ifdef MATRIX_USE_PLUS_EQ
  Matrix<double> m3(m1);
  m3 += m2;
#else
  Matrix<double> m3(m1 + m2);
#endif
  auto t1 = hrc::now();
  //std::cout << "M3:\n";
  //print(m3);
  std::cout << "duration, ms: " << std::chrono::duration_cast<ms>(t1 - t0).count() << "\n";

  return 0;
}