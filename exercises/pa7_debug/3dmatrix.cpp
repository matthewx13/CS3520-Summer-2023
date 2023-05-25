// Program to read 3-dimensional matrix and display the elements as 1xSIZE^3 matrix
// TODO
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
/* The changes I made include:
 * I added arguments to the display function
 * added const to the matrix argument for the disply function
 * avioided nested loops for display function
 * calculated the indices for a b and c for the display function
 *
 *
*/
#include <iostream>
#define SIZE 7

using namespace std;

void update_3d(double Matrix_3d[][SIZE][SIZE], int size);
void display_1d(const double Matrix_3d[][SIZE][SIZE], int size);

int main(void)
{
    double Matrix_3d[SIZE][SIZE][SIZE] = {};
    update_3d(Matrix_3d, SIZE);
    display_1d(Matrix_3d, SIZE);
    return 0;
}

void update_3d(double matrix[][SIZE][SIZE], int size)
{
    cout << "Entering SIZE^3 elements of the matrix:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                cin >> matrix[i][j][k]; 
            }
        }
    }
}

void display_1d(const double Matrix_3d[][SIZE][SIZE], int size)
{
    cout << "Matrix values with addresses:" << endl;
    const double* ptr = &Matrix_3d[0][0][0];
    for (int i = 0; i < size * size * size; i++)
    {
        cout << "Address: " << ptr << ", Value: " << *ptr << endl;
        ptr++;
    }
}
