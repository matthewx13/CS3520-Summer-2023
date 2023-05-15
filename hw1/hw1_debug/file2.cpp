// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits
Example : If areacode = 617, exchange = 424
Output : 
"I am calling to tell you to buy a subscription to Dogs Monthly Magazine!"
617-424-0001
617-424-0002
617-424-0003
...
617-424-9998
617-424-9999
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)
/*
 - First the statement Enter a three-digit area code " was not in complete quotes
 - the first input should ask for the int areaCode not exchange
 - cin also did not have std:: and it was using the incorrect operands
 - change the second input varaible to exchange from areaCode
 - the original while loop should be changed to a for loop to account for the 3rd digit
 - I then added a while loop and it should only have one condition to account for the 4th digit
*/
#include<iostream>
  
int main(){
   char digit1, digit2, digit3, digit4;
   int areaCode, exchange;
  
   std::cout<< "Hello, I am a telemarketing calling making program.\n";
   std::cout<< "Enter a three-digit area code ";
   std::cin>>areaCode;
   std::cout<<"Enter a three-digit exchange to call ";
   std::cin>>exchange;
  
   for (digit1 = '0'; digit1 <= '9'; ++digit1) {
        for (digit2 = '0'; digit2 <= '9'; ++digit2) {
            for (digit3 = '0'; digit3 <= '9'; ++digit3) {
                while (digit4 <= '9') { 
                    std::cout << "Dialing " << areaCode<< "-" <<exchange<< "-";
                    std::cout << digit1 << digit2 << digit3 << digit4 << std::endl;
                    std::cout << "I am calling to tell you to buy a subscription to Dogs Monthly Magazine!\n";
                    digit4++;  // Increment digit4 within the while loop
                }
                digit4 = '0';  // Reset digit4 back to '0' for the next iteration of digit3
            }
        }
    }
    
   std::cout<< "\nCalls completed"<<std::endl;
   return 0;
} 
