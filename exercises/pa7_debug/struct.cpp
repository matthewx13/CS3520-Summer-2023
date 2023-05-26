// car struct (Matthew Xue - 5/26/23)
// This program includes a struct called car that is used to store information
// about a given car The program should ask the user for information about their
// car and initialize a car structure with the given information The program
// should also print the information using a pointer to the initialized struct
// The information printed using the struct and the pointer should be the same

// Bugs to fix : 9
// The biggest fixes
// I changed name to string
// I cganged cout to cin for the question when was it launched
// changed some syntax for how much speed
#include <iostream>
#include <string>
using namespace std;
struct car {
  string name; //string for more flexibility
  int modelYear;
  float speed;
};

int main(void) {
  string n; // changed to string
  int a;
  float w;

  struct car c;
  car *cPtr = &c;

  cout << "What is your favorite car's name: ";
  cin >> n;
  c.name = n;

  cout << "When was it launched : ";
  cin >> a; // change to cin
  c.modelYear = a; 

  cout << "How much speed does it give : ";
  cin >> w; // change << to >>
  c.speed = w; // change to w


  cout << "Car's name is " << c.name << ", and should be the same as " << cPtr->name << ".\n";

  cout << "Car's model year is " << c.modelYear << ", and should be the same as " << c.modelYear << ".\n"; // changed to c bc car is c
  cout << "Car's speed is " << c.speed << ", and should be the same as "
       << w << ".\n";
}
