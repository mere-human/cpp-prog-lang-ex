/*
17.5.1 Copy
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
    //// provides basic but not the strong guarantee:
    //// if a copy of an elem throws an exception, the targed may be left
    //// with a mixture of its old value and new
    //if (dim[0] != m.dim[0] || dim[1] != m.dim[1])
    //  throw std::runtime_error("bad size in Matrix=");
    //std::copy(m.elem, m.elem + m.size(), elem); // copye elems

    // self assignment is safe
    Matrix tmp{ m }; // make a copy
    std::swap(tmp, *this); // swap representation
    return *this;
  }

  // move ctor
  Matrix(const Matrix&& m);
  // move assignment
  Matrix& operator=(Matrix&& m);

  ~Matrix() { delete[] elem; }
};