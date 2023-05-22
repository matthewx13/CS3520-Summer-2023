/*
HW 2 Question 3 Maze Generator (Matthew Xue 5/22)

The purpose of this code is to generate a random maze given a size from the user. 

Out of the five outputs that I copy and pasted below only maze 3 and 5 was valid. My program may be too random sometimes so thats why the mazes being outputted are not always valid.


Enter the size of the maze: 10
Maze 1:
. . . . # # # # # . # # 
. . # . # # # # . # # # 
# # # . # . . # # # . . 
# . # # # # . . . # . # 
# # . . . . . # . # # . 
. # . . . . # # # # # . 
# . . . . . . # . # . # 
# # . # # # # . # . # # 
# . . . # # # # # # # # 
. . # # # . . . # # . # 
# . . # . . . . # . . # 
# # . . . # # # # # # . 

Maze 2:
# # # # # # . # # # # . 
# . . # # # # . . . . # 
# . # # . # . . . . # . 
# # . . . # # . # . . . 
. . # # . # . # . # . # 
# # . . # . . # # # . . 
# # . # . # . # . . . # 
# # # . . # # # # . # # 
# . # # . # . # # . . # 
# # # # # . # . . . . # 
# # . . # # . # # . . # 
# # # . . # # # # # # # 

Maze 3:
# . # # . . # . # # # # 
# # # . # # . # # # # # 
# . . . . # # . . # # # 
# . . . . # . . # # # # 
# # # # . # . . . . . # 
# . # . # . . # . # # # 
# . . . . # . # # # # # 
# # # # . # . # . # . . 
# # . . . # # . # . . # 
. . . . # # . # # . # # 
# # # # # . # . . . . # 
# # # # # # # # # # # # 

Maze 4:
# # # # # # # # # # # # 
# # # . . . . . # . . # 
# # # # # # # . . # . # 
# # . # . . . # . . # # 
# # . # # # # . . # . # 
# # # . # # . # # # # # 
. . # . . # . # # # . # 
# # # . . # . . # . . . 
. . . # # # # . # # . . 
. . . # # # # . . # . # 
. # . # . # # . . # # # 
# # # . # . # # # # # # 

Maze 5:
# . # # # . . # . # # # 
# . . # . # . . # # . . 
# . # # # # . . . # # . 
# # . . . # # . # . . . 
# . # # . . # # # # # . 
# . . . # . . . . # . # 
# . . # # # # # . # . # 
# # . . # . # # . . . . 
# # # # . # # # . . # # 
# # # . . . . . . . # # 
# . . . # # # . # # # . 
# # # # # # # . # . # # 

 
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

const int max_size = 100; // Maximum size of the maze

// intialize a mazegenerator class
class MazeGenerator {
public:
    // function creates and generates a maze given a size from the user
    void create_maze(char maze[][max_size], int size) {
        // creates a border for the maze by making it more likely for #
        // to be printed out compared to .
        for (int i = 0; i < size + 2; i++) {
            for (int j = 0; j < size + 2; j++) {
                if (i == 0 || i == size + 1 || j == 0 || j == size+1) {
                    maze[i][j] = (rand() % 5 == 0) ? 46 : 35;
                }
            }
        }
        // goes through the array and prints out . and # at a 50% rate
        // to fill in the inside of the maze
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                maze[i][j] = (rand() % 2 == 0) ? 35 : 46;
            }
        }
    }
    // prints the maze that is generated
    void printing_maze(char maze[][max_size], int size) {
        for (int i = 0; i < size + 2; i++) {
            for (int j = 0; j < size + 2; j++) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
  // intialize variables
  int size;
  int num_mazes = 5;
  char maze[max_size][max_size];

  // generate a new seed each time
  srand (time(NULL));
  // input validation to insure size is always int
  while (true) {
        cout << "enter the size for maze: ";
        // input size has to be greater than 1 and less than 100
        if (cin >> size && size > 0 && size <= max_size) {
            // if the next input is a space break
            if (cin.peek() == '\n') 
                break;
        }
        // clears the errors so cin can run again and discards invalid output
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer up to " << max_size << endl;
    }
  // intialize class my_maze and use functions to generate and print maze
  MazeGenerator my_maze;
   for (int i = 0; i < num_mazes; i++) {
        cout << "maze number " << i + 1 << ":" << endl;
        my_maze.create_maze(maze, size);
        my_maze.printing_maze(maze, size);
        cout << endl;
    }
  return 0;
}