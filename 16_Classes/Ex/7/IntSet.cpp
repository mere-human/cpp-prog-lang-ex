/*
[7] (*3) Define, implement, and test a set of integers, class Intset.
Provide union, intersection, and symmetric difference operations.
*/

// Naive implementation using vectors.

// Sample output:
//a: 1 3 5
//b : 2 3 4
//a union b : 1 2 3 4 5
//a intersection b : 3
//a symm_diff b : 1 2 4 5

#include <vector>
#include <algorithm>
#include <iostream>

struct IntSetData
{
  std::vector<int> elems;
  bool sorted = true;
};

class IntSet
{
public:
  IntSet()
    : data{ new IntSetData() }
  {}

  IntSet(const IntSet& other)
    : data{ new IntSetData() }
  {
    data->elems = other.data->elems;
    data->sorted = other.data->sorted;
  }

  IntSet(IntSet&& other)
    : data{ other.data }
  {
    other.data = nullptr;
  }

  ~IntSet()
  {
    delete data;
  }

  IntSet& operator=(const IntSet& other)
  {
    data->elems = other.data->elems;
    data->sorted = other.data->sorted;
    return *this;
  }

  IntSet& operator=(IntSet&& other)
  {
    delete data;
    data = other.data;
    other.data = nullptr;
    return *this;
  }

  size_t size() const
  {
    return data->elems.size();
  }

  int get(size_t i) const
  {
    if (!data->sorted)
      sort_data();
    return data->elems.at(i);
  }

  void add(int n)
  {
    data->sorted = false;
    data->elems.push_back(n);
  }

  void unite_with(const IntSet& other)
  {
    // add elements from other
    for (size_t i = 0; i != other.size(); ++i)
      add(other.get(i));
    // sort
    sort_data();
    // remove duplicates (elems will be still sorted)
    auto it = std::unique(data->elems.begin(), data->elems.end());
    data->elems.resize(it - data->elems.begin());
  }

  IntSet unite(const IntSet& other) const
  {
    IntSet c{ *this };
    c.unite_with(other);
    return c;
  }

  void intersect_with(const IntSet& other)
  {
    // reassign with elements that are present in both
    if (size() > other.size())
      data->elems = collect_same_elems(other.data->elems, data->elems);
    else
      data->elems = collect_same_elems(data->elems, other.data->elems);
    data->sorted = false;
  }

  IntSet intersect(const IntSet& other) const
  {
    IntSet c{ *this };
    c.intersect_with(other);
    return c;
  }

  void symm_diff_with(const IntSet& other)
  {
    // get common elements
    const auto isx = intersect(other);
    IntVec new_elems;
    // add elems from this that are not in common
    for (size_t i = 0; i != size(); ++i)
    {
      int d = data->elems[i];
      auto it = std::find(isx.data->elems.begin(), isx.data->elems.end(), d);
      if (it == isx.data->elems.end())
        new_elems.push_back(d);
    }
    // add elems from other that are not in common
    for (size_t i = 0; i != other.size(); ++i)
    {
      int d = other.data->elems[i];
      auto it = std::find(isx.data->elems.begin(), isx.data->elems.end(), d);
      if (it == isx.data->elems.end())
        new_elems.push_back(d);
    }
    // reassign with new elements
    data->elems = new_elems;
    data->sorted = false;
  }

  IntSet symm_diff(const IntSet& other) const
  {
    IntSet c{ *this };
    c.symm_diff_with(other);
    return c;
  }

private:

  using IntVec = std::vector<int>;

  void sort_data() const
  {
    std::sort(data->elems.begin(), data->elems.end());
    data->sorted = true;
  }

  static IntVec collect_same_elems(const IntVec& a, const IntVec& b)
  {
    // not very effective...
    IntVec same_elems;
    for (size_t i = 0; i != a.size(); ++i)
    {
      int d = a[i];
      auto it = std::find(b.begin(), b.end(), d);
      if (it != b.end())
        same_elems.push_back(d);
    }
    return same_elems;
  }

  IntSetData* data;
};

std::ostream& operator<<(std::ostream& os, const IntSet& set)
{
  for (size_t i = 0; i != set.size(); ++i)
    os << set.get(i) << " ";
  return os;
}

int main()
{
  IntSet a;
  a.add(1);
  a.add(3);
  a.add(5);
  std::cout << "a: " << a << "\n";

  IntSet b;
  b.add(2);
  b.add(4);
  b.add(3);
  std::cout << "b: " << b << "\n";

  std::cout << "a union b: " << a.unite(b) << "\n";
  std::cout << "a intersection b: " << a.intersect(b) << "\n";
  std::cout << "a symm_diff b: " << a.symm_diff(b) << "\n";
  return 0;
}