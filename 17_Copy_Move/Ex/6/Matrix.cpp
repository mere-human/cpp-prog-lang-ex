/*
[6] (*3) Implement a simple Matrix along the lines of the one in ch.17.5.2.
Measure the performance of an addition of 1000-by-1000 matrices with and
without move operations. If you did not have the option of adding move
operations, what would you do?
*/
#include <array>

template<typename T>
class Matrix
{
  std::array<int, 2> dim; // 2 dimensions
  T* elem; // ptr to dim[0]*dim[1] elems of type T
public:
  Matrix(int d1, int d2) : dim{ d1, d2 }, elem{ new T[d1*d2] } // simplified
  {}
  int size() const { return dim[0] * dim[1]; }

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
  Matrix(Matrix&& m)
    : dim{ m.dim }, // grab representation
    elem{ m.elem }
  {
    // clear representation
    m.dim = { 0, 0 };
    m.elem = nullptr;
  }

  // move assignment
  Matrix& operator=(Matrix&& m)
  {
    // swap representations
    std::swap(dim, m.dim);
    std::swap(elem, m.elem);
    return *this;
  }

  ~Matrix() { delete[] elem; }
};

int main()
{
  return 0;
}