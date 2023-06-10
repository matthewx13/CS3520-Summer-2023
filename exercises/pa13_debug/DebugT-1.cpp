// Debug1 - Matthew Xue - 6/10/23
/*

Added missing type declaration for the parameter 'y' in the add() function template.

Changed 'U' to 'T' in the add() function template to match the template type.

Fixed the capitalization of 'person' to 'Person' in the declaration of operator+ in the Person class.

Added the 'const' qualifier to the parameter 'per' in the operator<< function for Person class.

Fixed the assignment of values in the Person::setValues() function by using 'this->' to refer to the member variable 'age'.

Corrected the assignment of 'temp.age' in the Person::operator+ function.

*/
#include <iostream>
#include <string>
using namespace std;


template <class T>
T add(T x, T y) // Fixed the missing type declaration for parameter 'y'
{
   T sum; // Changed 'U' to 'T' to match the template type
   sum = x + y;
   return sum;
}

class Person
{
   friend ostream &operator<<(ostream &, const Person &);

private:
   string lastName;
   string firstName;
   int age;

public:
   void setValues(string, string, int);
   Person operator+(Person); // Fixed the capitalization of 'person' to 'Person'
};

ostream &operator<<(ostream &out, const Person &per) // Added 'const' qualifier to the parameter 'per'
{
   out << per.firstName << " " << per.lastName << " " << per.age << " years old" << endl;
   return out; // Added the return statement
}

void Person::setValues(string last, string first, int age)
{
   lastName = last;
   firstName = first;
   this->age = age; // Added 'this->' to clarify the assignment to the member variable
}

Person Person::operator+(Person p)
{
   Person temp;
   temp.lastName = "of Age";
   temp.firstName = "Sum";
   temp.age = p.age - age; // Fixed the assignment of 'age' to 'temp.age'
   return temp;
}

int main()
{
   int a = 7, b = 26, c;
   double d = 39.25, e = 2.01, f;
   Person g, h, i;
   g.setValues("Mitchell", "Donald", 40);
   h.setValues("Clayton", "Rita", 35);
   c = add(a, b);
   f = add(d, e);
   i = add(g, h);
   cout << c << endl;
   cout << f << endl;
   cout << i << endl;
   return 0;
}
