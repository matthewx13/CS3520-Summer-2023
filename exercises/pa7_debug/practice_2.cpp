// practice 2(Matthew Xue - 5/25/23)
// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.

// Number of errors/bugs = 10
/* Biggest fixes
- add const variable Size
- change int Matrix[size + 1][size + 1]; to int Matrix[Size][Size]; 
- syntax errors for for loops in main
- change how the function is called in main
- disply function change syntax of for loops

*/
#include <iostream>
using namespace std;

const int Size = 3; // call new variable Size

void display(int Matrix[Size][Size], int size); 

int main() {
    int Matrix[Size][Size]; 
    cout << "Enter 9 elements of the matrix:" << endl; // change cin to cout
    for (int i = 0; i < Size; i++) { // give i int
        for (int j = 0; j < Size; j++) { // intialize j in for loop
            cin >> Matrix[i][j];
        }
    }
    display(Matrix, Size); //change how the function is called
    return 0;
}

void display(int Matrix[Size][Size], int size) {
    for (int i = 0; i < size; i++) { // add semicolon
        for (int j = 0; j < size; j++) { // change i++ to j++
            cout << Matrix[i][j] << ", ";
        }
        cout << endl;
    }
}





