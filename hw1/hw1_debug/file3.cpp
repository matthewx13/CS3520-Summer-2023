/*  This program should determine if a number is a prime or composite number 
    The program should ask user for a number 'num'
    If 'num' is 0 or 1, print "num is not prime or composite"
    For any value > 1, print "num is a prime number" or "num is a composite number" depending on the number */

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

/*
  - most important fixes are that && must be changed to ||
 - case sensitive so False must be false and True must be true
 - else statement is used with if statement, not a for loop
 - add the for loop under the else statement
*/

#include<iostream> // typo: this should be changed to iostream
using namespace std;

int main(void){
    int num,i;
    bool factor_found = false; // case sensitive: False changed to false
    cout<<"Enter Number:\n";
    cin>>num;
    if (num == 0 || num == 1) {  // replaced && with ||
        cout << num << " is not prime or composite\n";  // missing semicolon was added
    } else { // else statement added
        for (i = 2; i < num; ++i) {  // comma replaced with semicolon
            if (num % i == 0) {
                factor_found = true;  //changed False to true and factor_Found to factor_found
                break;
            }
        }
        if (factor_found) { // changed 'if not' to 'if'
            cout << num << " is a composite number\n";  // i added a missing semicolon
        } else {
            cout << num << " is a prime number\n";  // replaced the symbol ) with ;
        }
    }

    return 0;  // added a missing semicolon (;)
}
