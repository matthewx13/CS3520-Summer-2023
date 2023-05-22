// hw2 question 1 rolling dice (Matthew Xue 5/21/23)
/*
This code simulates the rolling of two dice. It rolls it 36000 times and it will keep track of the dice
roll combinations in a array and it will also keep track of the percentage of the occurences of each
combination in another array.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int size = 36000;  // 36000 dices rolls

int main() {
  int dice_rolls[6][6] = {};  // creating a 2d array filled with zeros
  int sums[11] = {};  //array to store sum of dice rolls

  srand(time(nullptr));

  // roll dice 36000 times and value is recorded
  for (int i = 0; i < size; i++) {
    // dice 1 and 2 will be rolled and the possible values are 1 to 6
    int dice_1 = rand() % 6 + 1;  
    int dice_2 = rand() % 6 + 1;  

    // increase the corresponding combinations in the dice_rolls array
    dice_rolls[dice_1 - 1][dice_2 - 1]++;  
    int sum = dice_1 + dice_2;
    sums[sum - 2]++;  
  }

  // printing the combinations of the dice rolls
  cout << "combination of dice rolls:" << endl;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      cout << i + 1 << " + " << j + 1 << " rolled " << dice_rolls[i][j] << " times" << endl;
    }
  }

  // print percentage of occurences for each combination in tabular format
  cout << "\nSum Tally:" << endl;
  cout << "Sum| Occurences| Percentage" << endl;
  for (int i = 0; i < 11; i++) {
    int sum = i + 2;
    int occurrences = sums[i];
    double percentage = (static_cast<double>(occurrences) / size) * 100;
    cout << sum << "     " << occurrences << "\t\t" << percentage << "%" << endl;
  }

  return 0;
}