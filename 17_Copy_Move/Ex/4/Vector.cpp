/*
[4] (*1) Design, implement and test a Vector class with an initializer-list
constructor and no constructor that takes a integer as a size. Instead,
give it a constructor that takes a Count type, so that you can’t get ambiguities
between and integer number of elements and an integer element value.
*/

// I am lazy, so I do not want to implement vector from scracth.
// I will just inherit from it and define necessary constructors.
// If I had to implement it I would base it on code from ch.13.

#include <vector>
#include <iostream>

struct Count
{
  size_t value;
  explicit Count(size_t v = 0) : value{ v } {}
};

template<typename T>
class Vector
  : public std::vector<T>
{
  using _Base = std::vector<T>;
public:
  explicit Vector(Count count = Count{}, const T& val = {})
    : _Base(count.value, val) {}
  Vector(std::initializer_list<T> l)
    : _Base(l) {}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
  os << "[";
  for (const auto& x : v)
    os << " " << x;
  os << " ]";
  return os;
}

int main()
{
  Vector<int> v1; // default
  std::cout << "v1 " << v1 << "\n";

  Vector<int> v2(Count{ 2 }); // 2 elements with default value
  std::cout << "v2 " << v2 << "\n";

  Vector<int> v3(Count{ 2 }, 1); // 2 elements with value 1 or 1 element with value 2?
  std::cout << "v3 " << v3 << "\n";

  Vector<int> v4({ 1, 2, 3, 4 }); // init list
  std::cout << "v4 " << v4 << "\n";

  Vector<int> v5(v2); // copy
  std::cout << "v5 " << v5 << "\n";

  Vector<int> v6(std::move(v3)); // move
  std::cout << "v6 " << v6 << "\n";

  v6 = v4; // assign
  std::cout << "v6 " << v6 << "\n";
  return 0;
}