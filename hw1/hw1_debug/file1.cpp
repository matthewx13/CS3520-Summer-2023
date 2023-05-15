/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'
*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments
//

// Code for sum of odd and even numbers
// the for loop intialization must include variable type 
// the first if statement should be == to compare instead of = which is used to assign
// the second if statement was switched to else and no condition is needed
// the if statement should use modulo, not division to identify even numbers

// Code for ABCD
// the cout statement formatting was incorrect, << should be used instead of ,
// for the alphabet c should began as Z and the condition should account for
// any letter that is greater than A
// The last cout statement should use the variable c and not i

#include <iostream>
using namespace std;

int main(){
    int limit = 10;
    int even_product = 1;
    int odd_product = 1;
    int sum = 0;
    char c;
    cout<<"The value of limit is "<< limit<<endl;

    for(int i = 1; i <= limit; ++i){ 
       if(i % 2 == 0){
           even_product *= i;
       }   
        else{
           odd_product *= i;
       }
        sum = even_product + odd_product;
    }
    cout << "The Sum = " << sum << endl;
  
    for(c = 'Z'; c >= 'A'; c -= 2){
    	cout<<" "<< c;
    }
    
    return 0;
}
