// Program to check if the user-provided number is a palindrome
// Number of errors/bugs = 25


//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.

/* Issues that I am fixing
- void main should be changed to int main
- i changed input from a char to an int
- changed the void function to a bool and named the function pal_func
- remove the result argument from pal_func
- add remainder varaible
- fix small syntax issues in pal_func


*/

#include<iostream>
using namespace std;

bool pal_func(int n); 

int main() {
      int input;
		  cout<<"enter an integer please: "; 
      cin >> input;
      bool return_val = pal_func(input);
        if (return_val){ 
                cout<<"It is not a palindrome" <<endl; // added "" and ;
        }
        else{
                cout<<"It is a palindrome"<<endl;
        }
		
		return 0; // missing ;
}

//the return value of your func should be true / false only
bool pal_func(int n) // removed result
{
    int given_number = n;
    int temp = 0;
    int remainder; // added remainder
    while (n != 0) { // change = to !=
      remainder = n % 10; // change from / to % for remainder
			n = n/10; // n =n/10 not just n/10
      temp = temp * 10 + remainder; // set temp =
    }

    if (given_number == temp) // change to given_number
    {
            return false;
    }
    else
    {
            return true; 
        }
}
