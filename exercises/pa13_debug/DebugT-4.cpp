// Debug T-4 - Matthew Xue - 6/10/23
/* Calculator class uses template class to perform arithmetic operations on different types of data.
 *  It also has function to determine which value is greater which return a boolean type.
 */

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

/*
- Calculator<string> calc3("Hello", 1); // String operations - This line causes a compilation error
- Changed the division operator from % to / in the divide() method.
- Fixed the return type of the isgreater() method to bool.
- Fixed the constructor definition of Calculator to match the declaration.

  */
#include <iostream>
using namespace std;

// Class to perform various operations on two variables of type T
template <class T>
class Calculator
{
private:
    T num1;
    T num2;

public:
    Calculator(T n1, T n2); // Constructor declaration
    T add(); // Method declaration for addition
    T subtract(); // Method declaration for subtraction
    T multiply(); // Method declaration for multiplication
    T divide(); // Method declaration for division
    bool isgreater(); // Method declaration to determine if num1 > num2
};

template <class T>
Calculator<T>::Calculator(T n1, T n2) // Constructor definition
{
    num1 = n1;
    num2 = n2;
}

template <class T>
T Calculator<T>::add() // Method definition for addition
{
    return num1 + num2;
}

template <class T>
T Calculator<T>::subtract() // Method definition for subtraction
{
    return num1 - num2;
}

template <class T>
T Calculator<T>::multiply() // Method definition for multiplication
{
    return num1 * num2;
}

template <class T>
T Calculator<T>::divide() // Method definition for division
{
    return num1 / num2;
}

template <class T>
bool Calculator<T>::isgreater() // Method definition to determine if num1 > num2
{
    return num1 > num2;
}

int main()
{
    Calculator<int> calc(10, 4); // Integer operations
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    cout << std::boolalpha << calc.isgreater() << endl;

    Calculator<double> calc2(10.234, 4.235); // Double operations
    cout << calc2.add() << endl;
    cout << calc2.subtract() << endl;
    cout << calc2.multiply() << endl;
    cout << calc2.divide() << endl;
    cout << std::boolalpha << calc2.isgreater() << endl;



    return 0;
}
