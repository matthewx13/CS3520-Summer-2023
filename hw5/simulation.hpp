#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>

enum State { INIT, ALIVE, DEAD, EXIT };

class Bug {
public:
  virtual void move(std::vector<Bug *> &bugs, bool canQueenBreed) = 0;
  virtual void breed(std::vector<Bug *> &bugs, bool canQueenBreed) = 0;
  virtual void die() = 0;
  virtual bool isAlive() = 0;
  virtual int getEnergy() = 0;
  virtual ~Bug() {}
};

class Male : public Bug {
public:
  Male(int x, int y, int energy);
  void move(std::vector<Bug *> &bugs, bool canQueenBreed);
  void breed(std::vector<Bug *> &bugs, bool canQueenBreed);
  void die();
  bool isAlive();
  int getEnergy();

private:
  int x;
  int y;
  int energy;
};

class Queen : public Bug {
public:
  Queen(int x, int y, int energy);
  void move(std::vector<Bug *> &bugs, bool canQueenBreed);
  void breed(std::vector<Bug *> &bugs, bool canQueenBreed);
  void die();
  bool isAlive();
  int getEnergy();

private:
  int x;
  int y;
  int energy;
};

class Worker : public Bug {
public:
  Worker(int x, int y, int energy);
  void move(std::vector<Bug *> &bugs, bool canQueenBreed);
  void breed(std::vector<Bug *> &bugs, bool canQueenBreed);
  void die();
  bool isAlive();
  int getEnergy();

private:
  int x;
  int y;
  int energy;
};

class Doodle : public Bug {
public:
  Doodle(int x, int y, int energy);
  void move(std::vector<Bug *> &bugs, bool canQueenBreed);
  void breed(std::vector<Bug *> &bugs, bool canQueenBreed);
  void die();
  bool isAlive();
  int getEnergy();

private:
  int x;
  int y;
  int energy;
};

class GameWindow {
public:
  GameWindow(int width, int height, int x_offset, int y_offset);
  ~GameWindow();
  void draw(int x, int y, char c);
  void clear();
  void refresh();

  int getWidth();
  int getHeight();
  int getXOffset();
  int getYOffset();
  WINDOW *getWindow();

private:
  int width;
  int height;
  int x_offset;
  int y_offset;
  WINDOW *window;
};

void game(int numDoodle, int numQueen, int numMale, int numWorker);
void generatePoints(int *bugX, int *bugY, int windowWidth, int windowHeight, int xOffset, int yOffset);

#endif  // SIMULATION_HPP
