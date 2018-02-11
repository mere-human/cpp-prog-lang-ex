/*
19.4.1 Finding Friends
*/

class C1 {};
void f1();

namespace N
{
  class C2 {};
  void f2();

  class C
  {
    int x;
  public:
    friend class C1; // prev defined
    friend void f1();

    friend class C3; // enclosed NS
    friend void f3();
    friend class C4; 
    friend void f4();
  };

  class C3 {};
  void f3() { C x; x.x = 1; }
}

class C4 {}; // not a friend
//void f4() { N::C x; x.x = 1; } // error

int main()
{

}