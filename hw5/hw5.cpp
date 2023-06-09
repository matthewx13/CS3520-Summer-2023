#include "bug.hpp"
#include "simulation.hpp"
#include "simulationWindow.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

int main() {
  int numDoodle;
  int numQueen;
  int numMale;
  int numWorker;

  cout << "Enter the number of doodlebugs, queens, male ants, and workers (in that order): " << endl;

  vector<int> nums;

  for (int i = 0; i < 4; i++) {
    int value;

    while (!(cin >> value) || value < 0) {
      cout << "Invalid input. Try again: " << endl;
      cin.clear();
      cin.ignore(123, '\n');
    }

    nums.push_back(value);
  }

  while (nums[0] + nums[1] + nums[2] + nums[3] > 1500) {
    cout << "You entered too many bugs. Please try again." << endl;
    nums.clear();

    for (int i = 0; i < 4; i++) {
      int value;

      while (!(cin >> value) || value < 0) {
        cout << "Invalid input. Try again: " << endl;
        cin.clear();
        cin.ignore(123, '\n');
      }

      nums.push_back(value);
    }
  }

  numDoodle = nums[0];
  numQueen = nums[1];
  numMale = nums[2];
  numWorker = nums[3];

  game(numDoodle, numQueen, numMale, numWorker);

  return 0;
}
