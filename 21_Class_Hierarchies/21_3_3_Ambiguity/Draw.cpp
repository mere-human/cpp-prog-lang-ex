#include <iostream>

class Window {
public:
  virtual void draw() {
    std::cout << "Window display image\n";
  }
};

class Cowboy {
public:
  virtual void draw() {
    std::cout << "Cowboy pull gun from holster\n";
  }
};

//// Wrong: different semantics
//class Cowboy_window : public Cowboy, public Window {
//public:
//  void draw() override {}
//};

struct WWindow : Window {
  using Window::Window; // inherit ctors
  virtual void win_draw() = 0; // force derived to override
  void draw() override final { win_draw(); } // display image
};

struct CCowboy : Cowboy {
  using Cowboy::Cowboy; // inherit ctors
  virtual void cow_draw() = 0; // force derived to override
  void draw() override final { cow_draw(); } // pull gun from holster
};

class Cowboy_window : public CCowboy, public WWindow {
public:
  void cow_draw() override { Cowboy::draw(); }
  void win_draw() override { Window::draw(); }
  //// error: can not override final
  //void draw() override {}
};

int main()
{
  Cowboy_window cw;
  //// error: ambiguous call
  //cw.draw();
  cw.cow_draw();
  cw.win_draw();
}