class X
{
public:
  void operator=(const X&) = delete;
  void operator&() = delete;
  void operator,(const X&) = delete;
};

void f(X a, X b)
{
  a = b; // Error	C2280	'void X::operator =(const X &)': attempting to reference a deleted function
  &a; // Error	C2280	'void X::operator &(void)': attempting to reference a deleted function
  a, b; // Error	C2280	'void X::operator ,(const X &)': attempting to reference a deleted function
}

int main()
{
}