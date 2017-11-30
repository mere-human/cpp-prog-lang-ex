#include <memory>

template<typename T, typename A = std::allocator<T>>
class Vector
{
  T* elem;  // start of allocation
  T* space; // end of element sequence, start of space allocated for possible expansion
  T* last;  // end of allocated space
  A alloc;  // allocator
public:
  using size_type = unsigned int;
  using iterator = T*;

  //// elaborate implementation
  //Vector(size_type size, const T& val = T(), const A& a = A())
  //  : alloc{ a }
  //{
  //  // allocate may throw
  //  // T's copy constructor may throw

  //  // get memory for elements
  //  // throw will exit before any resources are aquired
  //  elem = alloc.allocate(size);

  //  iterator p;
  //  try
  //  {
  //    iterator end = elem + n;
  //    for (p = elem; p != end; ++p)
  //    {
  //      // copy element
  //      // if T's copy throw we have acquired some memory that must be freed
  //      alloc.construct(p, val);
  //    }
  //    last = space = p;
  //  }
  //  catch (...)
  //  {
  //    for (iterator q = elem; q != space; ++q)
  //      alloc.destroy(q); // destroy constructed elements
  //    alloc.deallocate(elem, size); // free memory
  //    throw; // rethrow
  //  }
  //}

  Vector(size_type size, const T& val = T(), const A& a = A())
    : alloc{ a }
  {
    // allocate may throw
    // T's copy constructor may throw

    elem = alloc.allocate(size); // get memory for elements
    try
    {
      std::uninitialized_fill(elem, elem + n, val); // copy elements
      last = space = elem + n;
    }
    catch (...)
    {
      alloc.deallocate(elem, size); // free memory
      throw; // rethrow
    }
  }

  ~Vector()
  {
    for (T* p = elem; p != space; ++p)
      alloc.destroy(p);
    alloc.deallocate(elem, size());
  }

  size_type size() const
  {
    return space - elem;
  }

  size_type capacity() const
  {
    return last - elem;
  }

  // increase capacity to n
  void reserve(size_type n)
  {

  }

  // increase size to n
  void resize(size_type n)
  {

  }

  // add an element to end
  void push_back(const T& e)
  {

  }
};

int main()
{
  Vector<int> v(4, 1);
  return 0;
}