#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "bug.hpp"
#include "simulation.hpp"
#include "simulationWindow.hpp"

using namespace std;

void generatePoints(int *bugX, int *bugY, int width, int height, int xOffset, int yOffset) {
  *bugX = rand() % width + xOffset + 1;
  *bugY = rand() % height + yOffset + 1;
}

void game(int numDoodle, int numQueen, int numMale, int numWorker) {
  enum State { INIT, ALIVE, DEAD, EXIT };
  enum State state = INIT;

  static int maxX, maxY;
  static int xOffset, yOffset;

  GameWindow_t *gameWindow;

  vector<Bug *> bugs;
  vector<Bug *> tempBugs;

  const int windowHeight = 30;
  const int windowWidth = 50;

  char inputChar;
  int score = 0;
  int speed = 1;
  int sizeX;
  int sizeY;

  bool canQueenBreed;

  int numAnts = 0;
  int numDoodlebugs = 0;

  int debugPrintBugs;
  int bugCounter;

  char snakeHeadChar;
  int snakeLengthAtDeath;

  srand((int)time(0));
  struct timespec timeret;
  timeret.tv_sec = 200;

  while (state != EXIT) {
    switch (state) {
      case INIT:
        initscr();
        start_color();
        nodelay(stdscr, TRUE);
        noecho();
        getmaxyx(stdscr, maxY, maxX);
        keypad(stdscr, TRUE);
        curs_set(0);
        timeout(100);

        xOffset = (maxX / 2) - (windowWidth / 2);
        yOffset = (maxY / 2) - (windowHeight / 2);

        gameWindow = initGameWindow(xOffset, yOffset, windowWidth, windowHeight);

        drawGameWindow(gameWindow);

        int bugX, bugY, i, j, k, l;

        generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);

        for (int i = 0; i < numDoodle; i++) {
          while (Bug::bugExists(bugs, bugX, bugY)) {
            generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);
          }
          Bug::addBug(bugs, new DoodleBug(bugX, bugY, 0));
        }

        generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);

        for (int j = 0; j < numQueen; j++) {
          while (Bug::bugExists(bugs, bugX, bugY)) {
            generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);
          }
          Bug::addBug(bugs, new Queen(bugX, bugY, 0));
        }

        for (int k = 0; k < numWorker; k++) {
          while (Bug::bugExists(bugs, bugX, bugY)) {
            generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);
          }
          Bug::addBug(bugs, new Worker(bugX, bugY, 0));
        }

        for (int l = 0; l < numMale; l++) {
          while (Bug::bugExists(bugs, bugX, bugY)) {
            generatePoints(&bugX, &bugY, windowWidth, windowHeight, xOffset, yOffset);
          }
          Bug::addBug(bugs, new Male(bugX, bugY, 0));
        }

        state = ALIVE;
        break;

      case ALIVE:
        inputChar = getch();

        if (inputChar == 'q') {
          state = EXIT;
          break;
        }

        if (inputChar == 'p') {
          debugPrintBugs = 1;
        }

        if (inputChar == 'w' && speed > 1) {
          speed--;
        }

        if (inputChar == 's') {
          speed++;
        }

        score++;
        if (score % 3 == 0) {
          canQueenBreed = true;
        } else {
          canQueenBreed = false;
        }

        tempBugs.clear();
        tempBugs.insert(tempBugs.begin(), bugs.begin(), bugs.end());

        for (int i = 0; i < tempBugs.size(); i++) {
          tempBugs[i]->move(tempBugs, canQueenBreed);
          if (tempBugs[i]->getEnergy() == 0) {
            tempBugs[i]->die();
          }
        }

        for (int i = 0; i < bugs.size(); i++) {
          if (bugs[i]->isAlive()) {
            bugs[i]->breed(bugs, canQueenBreed);
          } else {
            delete bugs[i];
            bugs.erase(bugs.begin() + i);
            i--;
          }
        }

        drawGameWindow(gameWindow);
        wrefresh(gameWindow->window);

        if (debugPrintBugs) {
          debugPrintBugs = 0;
          for (int i = 0; i < bugs.size(); i++) {
            cout << *bugs[i];
          }
        }

        break;

      case DEAD:
        mvprintw(0, 0, "Game Over!");
        mvprintw(1, 0, "Final Score: %d", score);
        mvprintw(2, 0, "Press 'q' to quit.");

        if (inputChar == 'q') {
          state = EXIT;
        }

        break;

      default:
        break;
    }
  }

  delete gameWindow;
  endwin();
}

int main() {
  int numDoodle = 5;
  int numQueen = 2;
  int numMale = 5;
  int numWorker = 10;

  game(numDoodle, numQueen, numMale, numWorker);

  return 0;
}

