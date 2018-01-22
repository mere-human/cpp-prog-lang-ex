/*
[8] (*1.5) Modify class Intset into a set of nodes, where Node is a structure you define
*/

// Simple implementation using nodes.
// Implementation could be more optimal if search of the node will be done
// before insertion/modification etc.

// Sample output:
//a: 1 3 5
//b : 2 3 4
//a union b : 1 2 3 4 5
//a intersection b : 3
//a symm_diff b : 1 2 4 5

#include <vector>
#include <algorithm>
#include <iostream>

class IntSet
{
public:
  struct Node
  {
    Node* left;
    Node* right;
    int value;
  };

  IntSet()
    : top{ nullptr }
  {}

  IntSet(const IntSet& other)
    : top{ nullptr }
  {
    add_nodes(other.top);
  }

  IntSet(IntSet&& other)
    : top{ other.top }
  {
    other.top = nullptr;
  }

  ~IntSet()
  {
    clear();
  }

  IntSet& operator=(const IntSet& other)
  {
    clear();
    add_nodes(other.top);
    return *this;
  }

  IntSet& operator=(IntSet&& other)
  {
    clear();
    top = other.top;
    other.top = nullptr;
    return *this;
  }

  bool contains(int v) const
  {
    return has_node_with_value(top, v);
  }

  void add(int n)
  {
    add_node(top, n);
  }

  void unite_with(const IntSet& other)
  {
    add_nodes(other.top);
  }

  IntSet unite(const IntSet& other) const
  {
    IntSet c{ *this };
    c.unite_with(other);
    return c;
  }

  IntSet intersect(const IntSet& other) const
  {
    IntSet c;
    intersect_nodes(top, other, c);
    return c;
  }

  IntSet symm_diff(const IntSet& other) const
  {
    IntSet c;
    add_diff_nodes(top, other, c);
    add_diff_nodes(other.top, *this, c);
    return c;
  }

private:

  friend std::ostream& operator<<(std::ostream& os, const IntSet& s);

  void clear()
  {
    clear_nodes(top);
    top = nullptr;
  }

  bool has_node_with_value(Node* n, int v) const
  {
    if (!n) return false;
    if (n->value == v) return true;
    else if (n->value > v) return has_node_with_value(n->left, v);
    else return has_node_with_value(n->right, v);
  }

  void clear_nodes(Node* n)
  {
    if (!n) return;
    clear_nodes(n->left);
    n->left = nullptr;
    clear_nodes(n->right);
    n->right = nullptr;
    delete n;
  }

  void print_nodes(Node* n, std::ostream& os) const
  {
    if (!n) return;
    print_nodes(n->left, os);
    os << n->value << " ";
    print_nodes(n->right, os);    
  }

  void add_nodes(Node* n)
  {
    if (n)
    {
      add_node(top, n->value);
      add_nodes(n->left);
      add_nodes(n->right);
    }
  }

  // n is a reference to a pointer
  void add_node(Node*& n, int value)
  {
    if (!n)
    {
      n = new Node{ nullptr, nullptr, value };
    }
    else if (n->value > value)
    {
      add_node(n->left, value);
    }
    else if (n->value == value)
    {
      // do nothing - ignore duplicates
    }
    else // n.value < value
    {
      add_node(n->right, value);
    }
  }

  void intersect_nodes(Node* n, const IntSet& other, IntSet& dest) const
  {
    if (!n) return;
    if (other.contains(n->value)) dest.add(n->value);
    intersect_nodes(n->left, other, dest);
    intersect_nodes(n->right, other, dest);
  }

  void add_diff_nodes(Node* n, const IntSet& other, IntSet& dest) const
  {
    if (!n) return;
    if (!other.contains(n->value)) dest.add(n->value);
    add_diff_nodes(n->left, other, dest);
    add_diff_nodes(n->right, other, dest);
  }

  Node* top;
};

std::ostream& operator<<(std::ostream& os, const IntSet& s)
{
  s.print_nodes(s.top, os);
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