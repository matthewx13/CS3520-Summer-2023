// Debug T-3 - Matthew Xue - 6/10/23
// A container class for displaying a comma-separated list.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide a list of the most important fixes (in comments)
/*
- Fixed variable name, changed 'y' to 'x'
- Declare and assign values to four kinds of CommaSeparatedLists
- Calculate size and create CommaSeparatedList objects
*/
#include <iostream>
#include <string>
using namespace std;

template <class T>
class CommaSeparatedList
{
private:
   T *data;
   int size;

public:
   CommaSeparatedList(T *d, int s);
   void printList();
};

template <class T>
CommaSeparatedList<T>::CommaSeparatedList(T *d, int s) // Fixed parameter name
{
   data = d;
   size = s;
}

template <class T>
void CommaSeparatedList<T>::printList() // Added missing closing angle bracket
{
   cout << "Comma-separated list:" << endl; // Fixed operator, changed '>>' to '<<'
   for (int x = 0; x < size; ++x)
   {
      cout << data[x]; // Fixed variable name, changed 'y' to 'x'
      if (x != size - 1)
         cout << ", ";
   }
   cout << endl << endl;
}

class Book
{
   friend ostream &operator<<(ostream &, const Book &);

private:
   string title;
   int year;

public:
   void setBook(string, int);
};

void Book::setBook(string Title, int pr)
{
   title = Title;
   year = pr;
}

ostream &operator<<(ostream &out, const Book &b)
{
   out << b.title << " was published in " << b.year; // Added space after 'in'
   return out;
}

class Customer
{
   friend ostream &operator<<(ostream &, const Customer &);

private:
   string name;
   double balDue;

public:
   void setCustomer(string, double);
};

void Customer::setCustomer(string CustomerName, double pr)
{
   name = CustomerName;
   balDue = pr;
}

ostream &operator<<(ostream &out, const Customer &aCustomer)
{
   out << aCustomer.name << " owes $" << aCustomer.balDue; // Added '$' before the balance amount
   return out;
}

int main()
{
   int CommaSeparatedListSize;
   // Declare and assign values to four kinds of CommaSeparatedLists
   int someInts[] = {12, 34, 55, 77, 99};
   double someDoubles[] = {11.11, 23.44, 44.55, 123.66};
   Book someBook[2];
   someBook[0].setBook("Wizard of Oz", 1986);
   someBook[1].setBook("Harry Potter", 2000);
   Customer someCustomers[6];
   someCustomers[0].setCustomer("Zaps", 23.55);
   someCustomers[1].setCustomer("Martin", 155.77);
   someCustomers[2].setCustomer("Fine", 333.88);
   someCustomers[3].setCustomer("Torrence", 123.99);
   someCustomers[4].setCustomer("Richard", 20.06);
   someCustomers[5].setCustomer("Curtin", 56999.19);

   // Calculate size and create CommaSeparatedList objects
   CommaSeparatedListSize = sizeof(someInts) / sizeof(someInts[0]);
   CommaSeparatedList<int> CommaSeparatedListOfIntegers(someInts, CommaSeparatedListSize);
   CommaSeparatedListSize = sizeof(someDoubles) / sizeof(someDoubles[0]);
   CommaSeparatedList<double> CommaSeparatedListOfDoubles(someDoubles, CommaSeparatedListSize);
   CommaSeparatedListSize = sizeof(someBook) / sizeof(someBook[0]); // Fixed typo, changed 'sizeif' to 'sizeof'
   CommaSeparatedList<Book> CommaSeparatedListOfBooks(someBook, CommaSeparatedListSize);
   CommaSeparatedListSize = sizeof(someCustomers) / sizeof(someCustomers[0]);
   CommaSeparatedList<Customer> CommaSeparatedListOfCustomers(someCustomers, CommaSeparatedListSize);

   // Use printList() with each CommaSeparatedList
   CommaSeparatedListOfIntegers.printList();
   CommaSeparatedListOfDoubles.printList();
   CommaSeparatedListOfBooks.printList(); // Fixed typo, changed 'prinList' to 'printList'
   CommaSeparatedListOfCustomers.printList();

   return 0;
}
