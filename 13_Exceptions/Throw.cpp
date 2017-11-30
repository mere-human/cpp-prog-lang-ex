#include <iostream>

struct Error {
  Error() = default;
  Error(const Error&) {
    std::cout << "copy\n";
  }
  Error& operator=(const Error&) {
    std::cout << "copy assign\n";
  }
};

void f() {
  throw Error();
}

void h() {
  try {
    f();
  }
  catch (...) {
    throw;
  }

}

int main() {

  try {
    f();
  }
  catch (Error) {

  }

  try {
    f();
  }
  catch (const Error&) {

  }

  try {
    h();
  }
  catch (const Error&) {

  }
}