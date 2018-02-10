/*
19.3 A String Class
*/

#include <iostream>

char* expand(const char* ptr, int n) // expand into free store
{
  char* p = new char[n];
  strcpy(p, ptr);
  return p;
}

class String
{
public:
  String()
    : sz{ 0 }, ptr{ ch } // ptr points to elements, ch is an initial location
  {
    ch[0] = 0; // terminating 0
  }
  String(const char* p)
    : sz{ static_cast<int>(strlen(p)) },
      ptr{(sz <= short_max) ? ch : new char[sz + 1]},
      space{ 0 }
  {
    strcpy(ptr, p); // copy all characters from p
  }

  String(const String& a)
  {
    copy_from(a);
  }
  String& operator=(const String& a)
  {
    if (this == &a) // self-assignment
      return *this; 
    char* p = (short_max < sz) ? ptr : 0;
    copy_from(a);
    delete[] p;
    return *this;
  }

  String(String&& a)
  {
    move_from(a);
  }
  String& operator=(String&& a)
  {
    if (this == &a) // self-assignment
      return *this;
    if (short_max < sz)
      delete[] ptr; // delete target
    move_from(a); // does not throw
    return *this;
  }

  ~String()
  {
    if (short_max < sz)
      delete[]ptr;
  }

  // unchecked elements access
  char& operator[](int n) { return ptr[n]; }
  char operator[](int n) const { return ptr[n]; }

  // range-checked elements access
  char& at(int n)
  {
    check(n);
    return ptr[n];
  }
  char at(int n) const
  {
    check(n);
    return ptr[n];
  }

  String& operator+=(char c) // add c at end
  {
    if (sz == short_max) // expand to long string
    {
      int n = sz + sz + 2; // double the allocation (+2 because of the terminating 0)
      ptr = expand(ptr, n);
      space = n - sz - 2;
    }
    else if (short_max < sz)
    {
      if (space == 0) // expand in free store
      {
        int n = sz + sz + 2; // double the allocation (+2 because of the terminating 0)
        char* p = expand(ptr, n);
        delete[] ptr;
        ptr = p;
        space = n - sz - 2;
      }
      else
      {
        --space;
      }
    }
    ptr[sz] = c; // add c at end
    ptr[++sz] = 0; // increase the size and set terminator
    return *this;
  }

  // C-style string access
  char* c_str() { return ptr; }
  const char* c_str() const { return ptr; }

  int size() const { return sz; }
  int capacity() const { return (sz <= short_max) ? short_max : sz + space; }

private:
  static const int short_max = 15;
  int sz; // num of characters
  char* ptr;
  union
  {
    int space; // unused allocated space
    char ch[short_max + 1]; // leave space for remaining 0
  };

  void check(int n) const // range check
  {
    if (n < 0 || sz <= n)
      throw std::out_of_range("String::at()");
  }

  // ancillary member functions
  void copy_from(const String& x)
  {
    if (x.sz <= short_max)
    {
      memcpy(this, &x, sizeof(x)); // copy *this
      ptr = ch;
    }
    else
    {
      ptr = expand(x.ptr, x.sz + 1);
      sz = x.sz;
      space = 0;
    }
  }
  void move_from(String& x)
  {
    if (x.sz <= short_max)
    {
      memcpy(this, &x, sizeof(x)); // copy *this
      ptr = ch;
    }
    else // grab the elements
    {
      ptr = x.ptr;
      sz = x.sz;
      space = x.space;
      x.ptr = x.ch; // x = ""
      x.sz = 0;
      x.ch[0] = 0;
    }
  }
};

// stream I/O

std::ostream& operator<<(std::ostream& os, const String& s)
{
  return os << s.c_str();
}

std::istream& operator >> (std::istream& is, String& s)
{
  s = ""; // clear the target string
  is >> std::ws; // skip whitespace
  char ch = ' ';
  while (is.get(ch) && !isspace(ch))
    s += ch;
  return is;
}

// comparison

bool operator==(const String& a, const String& b)
{
  if (a.size() != b.size())
    return false;
  for (int i = 0; i != a.size(); ++i)
    if (a[i] != b[i])
      return false;
  return true;
}

bool operator!=(const String& a, const String& b)
{
  return !(a == b);
}

// range-for loop

char* begin(String& x)
{
  return x.c_str();
}

char* end(String& x)
{
  return x.c_str() + x.size();
}

const char* begin(const String& x)
{
  return x.c_str();
}

const char* end(const String& x)
{
  return x.c_str() + x.size();
}

String& operator+=(String& a, const String& b) // concatenation
{
  for (auto x : b)
    a += x;
  return a;
}

String operator+(const String& a, const String& b) // concatenation
{
  String res{ a };
  res += b;
  return res;
}

String operator""_s(const char* p, size_t)
{
  return String(p);
}

int hash(const String& s)
{
  int h{ s[0] };
  for (int i = 1; i != s.size(); ++i)
    h ^= s[i] >> 1;
  return h;

}

int main()
{
  String s("abcdefghij");
  std::cout << s << "\n";
  s += 'k';
  s += 'l';
  s += 'm';
  s += 'n';
  std::cout << s << "\n";

  String s2 = "Hell";
  s2 += " and high water";
  std::cout << s2 << "\n";

  String s3 = "qwerty";
  s3 = s3;
  String s4 = "the quick brown fox jumped over the lazy dog";
  s4 = s4;
  std::cout << s3 << " " << s4 << "\n";
  std::cout << s + ". " + s3 + String(". ") + "Horsefeathers\n";

  String buf;
  while (std::cin >> buf && buf != "quit")
    std::cout << buf << buf.size() << " " << buf.capacity() << "\n";
}