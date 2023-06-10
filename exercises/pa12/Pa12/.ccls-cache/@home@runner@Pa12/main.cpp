#include <iostream>
#include <memory>
#include <cstring>

class MyString {
  std::unique_ptr<char[]> str;

public:
  MyString() : str(new char[1]) {
    str[0] = '\0';
  }

  MyString(const char* val) {
    if (val == nullptr) {
      str.reset(new char[1]);
      str[0] = '\0';
    } else {
      size_t length = strlen(val);
      str.reset(new char[length + 1]);
      strcpy(str.get(), val);
      str[length] = '\0';
      std::cout << "The given string is: " << str.get() << std::endl;
    }
  }

  MyString(const MyString& source) {
    size_t length = strlen(source.str.get());
    str.reset(new char[length + 1]);
    strcpy(str.get(), source.str.get());
    str[length] = '\0';
  }

  MyString(MyString&& source) noexcept = default;

  ~MyString() = default;
};

int main() {
  std::cout << "Start!" << std::endl;

  MyString a;
  MyString b("Hello");
  MyString c(a);
  MyString d(MyString("World"));

  std::cout << "Bye" << std::endl;

  return 0;
}