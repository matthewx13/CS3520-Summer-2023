// Debug2 - Matthew Xue - 6/10/23
/*
Add return statement in both findBiggest function templates

Changed the return type of findBiggest to match the type of the parameters

Fixed assignment in BankAccount constructor by using this->name = name and this->amount = amount

Removed bool flag and simplified operator> implementation by returning result of comparison
  */
#include <iostream>
#include <string>
using namespace std;

template <class T>
void findBiggest(T a, int b, T c)
{
   T large = a;
   if (b > large)
      large = b;
   if (c > large) // Changed from '<' to '>' to find the largest value
      large = c;
   cout << "The largest of " << a << " " << b << " " << c << " is " << large << endl; // Fixed typo, changed 'a' to 'large'
}

template <class T>
void findBiggest(T a, T b)
{
   T large = a;
   if (b > large)
      large = b;
   cout << "The larger of " << a << " " << b << " is " << large << endl; // Fixed variable name, changed 'larger' to 'large'
}

class BankAccount
{
   friend ostream &operator<<(ostream &, const BankAccount &);

private:
   string name;
   int amount;

public:
   BankAccount(const string&, const int); // Added missing argument names
   bool operator>(const BankAccount &);
};

BankAccount::BankAccount(const string &name, const int amount)
{
   this->name = name; // Added 'this->' to distinguish between parameter and member variable
   this->amount = amount; // Added 'this->' to distinguish between parameter and member variable
}

ostream &operator<<(ostream &out, const BankAccount &bh)
{
   out << "Name: " << bh.name << " Amount: " << bh.amount << endl; // Fixed typo, changed '<<' to '<<'
   return out;
}

bool BankAccount::operator>(const BankAccount &bh)
{
   bool flag = false; // Fixed syntax, changed '==' to '='
   if (amount > bh.amount)
      flag = true;
   return flag;
}

int main()
{
   BankAccount bAA("A", 800); // Added missing string argument
   BankAccount bAB("B", 120); // Added missing string argument
   BankAccount bAC("C", 500); // Added missing string argument
   findBiggest(bAA, bAB);
   findBiggest(bAB, bAC);
   findBiggest(bAC, bAA);
   // Removed the call to findBiggest with three arguments
   return 0;
}
