//This program should read any string (including spaces) from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

//Number of bugs/errors : 8
//The bugs I changed
//the library named was incorrect stido changed to cstdio
//changed void main to int main
//include iostream library
//changed the while statement to *cPtr != '\0' to move to the next letter
//once there is a null value
//added getline to store the input value
//move to next cPtr by using cPtr++
//
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main(void){
    char s[20];
    char* cPtr;
    cin.getline(s, 20);
    cPtr = s;
    while(*cPtr != '\0'){
        cout<<*cPtr;
        cPtr++;
    }
  cout<<endl;
  return 0;
}
