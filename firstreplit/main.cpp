// This is my test program (Matthew Xue - 5/8)
/* std namespace is part of all header files which includes popular functions that we often use
- you can use those with std:: or instead use "using namespace std"
- \n and endl basically are similar (end of line markers: CR and LF but not same. \n gets flushed at the end of program while endl gets flushed immediately)
*/
#include <iostream>
using namespace std;
int main() {
  int my_var = 0;
  cin >> my_var;
  cout << "Hello World! " + to_string(my_var) << endl;
  return EXIT_SUCCESS;
}