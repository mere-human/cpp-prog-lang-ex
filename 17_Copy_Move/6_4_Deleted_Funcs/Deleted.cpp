/*
17.6.4 deleted Functions
*/

struct Foo {};

template<typename T>
T* clone(T* p)
{
  return new T{ *p };
}

Foo* clone(Foo*) = delete;


struct Z
{
  Z(double) {}
  Z(int) = delete;
};

struct Not_on_stack
{
  ~Not_on_stack() = delete; // can not delete, private dtor is better 
};

struct Not_on_free_store
{
  void* operator new(size_t) = delete;
};

int main()
{
  int d = 1;
  int* p1 = clone(&d);
  Foo f;
  //Foo* p2 = clone(&f); // Error	C2280	'Foo *clone(Foo *)': attempting to reference a deleted function

  Z z1{ 1.1 };
  //Z z2{ 1 }; // Error	C2280	'Z::Z(int)': attempting to reference a deleted function

  //Not_on_stack n1; // Error	C2280	'Not_on_stack::~Not_on_stack(void)': attempting to reference a deleted function
  auto n2 = new Not_on_stack{};
  //auto n3 = new Not_on_free_store{}; // Error	C2280	'void *Not_on_free_store::operator new(std::size_t)': attempting to reference a deleted function

  Not_on_free_store n4;

  return 0;
}