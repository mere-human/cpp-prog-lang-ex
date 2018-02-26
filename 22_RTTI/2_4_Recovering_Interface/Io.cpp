#include <sstream>
#include <memory>
#include <map>
#include <iostream>

class Io_obj {
public:
  virtual Io_obj* clone() const = 0; // polymorphic
  virtual ~Io_obj() {}
};

class Shape {
public:
  virtual void draw() = 0;
};

//// use already defined Shape unchanged
//class Shape : public Io_obj {
//};

class Circle : public Shape {
public:
  void draw() override
  {
    std::cout << "circle\n";
  }
};

class Triangle : public Shape {
public:
  void draw() override
  {
    std::cout << "triangle\n";
  }
};

//// tedious...
//struct Io_circle : Circle, Io_obj {
//  Io_circle(std::istream& is) {} // init from input stream
//  Io_circle* clone() const { return new Io_circle{ *this }; } // use copy ctor
//  static Io_obj* new_circle(std::istream& is) { return new Io_circle{ is }; } // for io_map
//};
//
//struct Io_triangle : Triangle, Io_obj {
//  Io_triangle(std::istream& is) {}
//  Io_triangle* clone() const { return new Io_triangle{ *this }; }
//  static Io_obj* new_triangle(std::istream& is) { return new Io_triangle{ is }; }
//};

//// error: T is not a legal base class (for int)
//template<class T>
//struct Io : T, Io_obj {
//  Io(std::istream& is) {}
//  Io* clone() const override { return new Io{ *this }; }
//  static Io_obj* new_io(std::istream& is) { return new Io{ is }; }
//};

template<class T>
struct Io : Io_obj {
  T val;
  Io(std::istream& is) {}
  Io* clone() const override { return new Io{ *this }; }
  static Io_obj* new_io(std::istream& is) { return new Io{ is }; }
};

using Io_circle = Io<Circle>;
using Io_triangle = Io<Triangle>;
using Io_int = Io<int>;

template<typename T>
T* get_val(Io_obj* p)
{
  if (auto pp = dynamic_cast<Io<T>*>(p))
    return &pp->val;
  return nullptr;
}

using Pf = Io_obj*(*)(std::istream&); // ptr to func returning an Io_obj*

std::map<std::string, Pf> io_map; // maps string to creation functions

// read a word from is; throw if the read failed
std::string get_word(std::istream& is)
{
  std::string res;
  is >> res;
  return res;
}

class Unknown_class
{};

Io_obj* get_obj(std::istream& is)
{
  auto str = get_word(is); // read initial word
  if (auto f = io_map[str]) // look up to get func
    return f(is); // call func
  throw Unknown_class{}; // no match for str
}

//void user()
//{
//  std::stringstream ss;
//  std::unique_ptr<Io_obj> p{ get_obj(ss) }; // read object from stream
//  if (auto sp = dynamic_cast<Shape*>(p.get()))
//  {
//    // use the Shape
//    sp->draw();
//  }
//  else
//  {
//    // oops: non-shape in Shape file
//  }
//}
void user()
{
  std::stringstream ss;
  ss << "Io_circle\n";

  std::unique_ptr<Io_obj> p{ get_obj(ss) }; // read object from stream
  //// error: can not cast from Io<Circle>* to Io<Shape>*
  //if (auto sp = get_val<Shape>(p.get()))
  if (auto sp = get_val<Circle>(p.get()))
  {
    // use the Shape
    sp->draw();
  }
  else
  {
    // oops: non-shape in Shape file
  }
}

int main()
{
  // init
  //// tedious...
  //io_map["Io_circle"] = &Io_circle::new_circle;
  //io_map["Io_triangle"] = &Io_triangle::new_triangle;
  io_map["Io_circle"] = &Io_circle::new_io;
  io_map["Io_triangle"] = &Io_triangle::new_io;
  io_map["Io_int"] = &Io_int::new_io;
  
  user();
}