#include <exception>
#include <string>
#include <sstream>
#include <iostream>

namespace Assert {
  enum class Mode { throw_, terminate_, ignore_ };
  constexpr Mode current_mod = Mode::throw_;
  constexpr int current_level = 2;
  constexpr int default_level = 1;

  constexpr bool level(int n) { return n <= current_level; }

  struct Error : std::runtime_error {
    Error(const std::string& s) : std::runtime_error( s ) {}
  };

  std::string compose(const char* file, int line, const std::string& message) {
    std::ostringstream os("(");
    os << file << "," << line << "):" << message;
    return os.str();
  }

  template<bool cond = level(default_level), class Except = Error>
  void dynamic(bool assertion, const std::string& message = "Assert::dynamic failed") {
    if (assertion)
      return;
    if (current_mod == Mode::throw_)
      throw Except{ message };
    if (current_mod == Mode::terminate_)
      std::terminate();
  }

  template<>
  void dynamic < false, Error >(bool, const std::string&) {
  }

  //void dynamic(bool b, const std::string& message) {
  //  dynamic(b, message);
  //}
}

void f(int n) {
  //Assert::dynamic<Assert::level(2)>(
  //  (n <= 0 || n < 100), Assert::compose(__FILE__, __LINE__, "range problem"));
  Assert::dynamic(n <= 0 || n < 100);
}

int main() {
  try {
    f(0);
    f(1);
    f(999);
  }
  catch (std::exception& e) {
    std::cout << e.what() << "\n";
  }
}