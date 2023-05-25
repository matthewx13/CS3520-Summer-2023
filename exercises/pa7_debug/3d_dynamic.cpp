//This program allocated memory for an NxM integer array dynamicaly 
//The program then prints the 2D array in a matrix form using a combination of * and [] operators
//Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

//Number of bugs/errors : 6
/* I fixed the for loop adding in brackets and I fixed one of the statements
 * by ending it with a semicolon
 * - changed the allocation of memory for the 2d array to use malloc correctly
 * - fixed the way the 2d array is intialized d_array[i][j] instead of *(d_array+i+j).
 * - corrected 2d array when printing *(*(d_array + i) + j) or d_array[i][j].
 * -deallocation of memory by using free(d_array[i]) inside the loop.
 *
 */
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	int N = 3, M = 5;
	int i, j; 
	int** d_array = (int**) malloc( N * sizeof(int*) ); 	//Allocating memory for 2D array (N rows)
	for(i=0; i< N;  i++){
	     d_array[i] = (int*) malloc(M * sizeof(int) );
	}  //Allocating memory for each row with M columns)
	//Initializing 2D array using [ ][ ] notation
	cout << "Initializing array values!" << endl;
	for(i=0; i< N; i++) {			 
	     for(j=0; j < M; j++) {
	          d_array[i][j] = i+j; 
	     }
	}
	//Accessing 2D array using a combination of * and [] notation
	cout << endl;
	for(i=0; i< N; i++) {			 
	     for(j=0; j < N; j++) {
	          cout<<*(d_array[i]+j);
	     }
	     cout<< endl;
	}

	//Deallocating 2D array
	for(i=0; i< N; i++)			 
		free(d_array[i]);
	free(d_array);
}
