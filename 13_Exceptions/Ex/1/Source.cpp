/*
[1] (*3) Write a Checked_ptr<T> that uses exceptions to signal run-time errors
for a pointer supposed to point to an element of an array (or
one-beyond-the-end-of the array).
*/

#include <iostream>

struct Out_of_range_exception {};

template<typename T>
class Checked_ptr
{
public:

  // use integer template argument to ensure that array is passed
  // and to easily get array's size
  template<size_t N>
  Checked_ptr(T (&arr)[N], size_t pos = 0)
    : _ptr{ &arr[0] }, _pos{ pos }, _len{ N }
  {}

  T& operator++()
  {
    ++_pos;
    return operator*();
  }

  T& operator--()
  {
    --_pos;
    return operator*();
  }

  T& operator*()
  {
    check();
    return _ptr[_pos];
  }

  const T& operator*() const
  {
    check();
    return _ptr[_pos];
  }

private:

  void check() const
  {
    if ((_pos < 0) || (_pos >= _len)) throw Out_of_range_exception{};
  }

  T* _ptr;
  size_t _pos;
  const size_t _len;
};

int main()
{
  int a[] = { 0, 2, 3 };
  try
  {
    Checked_ptr<int> p{ a };
    *p = 1;
    for (int i = 0; i <= 3; ++i, ++p)
      std::cout << *p << "\n";
  }
  catch (Out_of_range_exception&)
  {
    std::cerr << "Error: out of range\n";
  }
  return 0;
}