/*
17.2.4 Calling Constructors and Destructors
*/
class Nonlocal
{
public:
  void destroy() { this->~Nonlocal(); }
private:
  ~Nonlocal() {}
};

int main()
{
  //Nonlocal x; // Error	C2248	'Nonlocal::~Nonlocal': cannot access private member
  Nonlocal* p = new Nonlocal;
  //delete p; // Error
  p->destroy();
}