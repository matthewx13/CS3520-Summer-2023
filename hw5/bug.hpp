#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <cstdbool>

#ifndef BUG_HPP
#define BUG_HPP

using namespace std;

class Ant;
class DoodleBug;
class Queen;
class Worker;

class Bug {
protected:
  int x;
  int y;
  int initializedTime;
  char symbol;

public:
  Bug(int x, int y, int initializedTime);
  virtual ~Bug(){};

  virtual void move(vector<pair<int, int>> positions) = 0;
  virtual bool starve() const = 0;
  virtual vector<pair<int, int>> canMove(vector<Bug*>& bugs, int x, int y) const = 0;
  virtual bool canBreed() const = 0;
  virtual void breed(vector<Bug*>& bugs) const = 0;

  static void operator++(Bug& bug);
  static bool compareBugs(const Bug* a, const Bug* b);
  static void addBug(vector<Bug*>& bugs, const Bug* newBug);

  static bool bugExists(vector<Bug*>& bugs, int x, int y);
  static void drawBug(Bug* bug);
  static void removeEatenBug(vector<Bug*>& bugs, int x, int y);

  int getX() const;
  int getY() const;
  char getSymbol() const;
  int getInitializedTime() const;
  void setX(int x);
  void setY(int y);

  static void displayBugInfo(int count, int x, int y, Bug* bug);
};

class DoodleBug : public Bug {
protected:
  int timeSinceEating;

public:
  DoodleBug(int x, int y, int initializedTime);
  virtual ~DoodleBug();

  virtual void move(vector<pair<int, int>> positions) override;
  virtual bool starve() const override;
  virtual vector<pair<int, int>> canMove(vector<Bug*>& bugs, int x, int y) const override;
  virtual bool canBreed() const override;
  virtual void breed(vector<Bug*>& bugs) const override;
};

class Ant : public Bug {
public:
  Ant(int x, int y, int lifetime);
  virtual ~Ant();
};

class Queen : public Ant {
protected:
  int timeSinceLayedEggs;
  int timeSinceMadeQueen;
  int timeSinceMated;

public:
  Queen(int x, int y, int lifetime);
  virtual ~Queen();

  virtual void move(vector<pair<int, int>> positions) override;
  virtual bool starve() const override;
  virtual vector<pair<int, int>> canMove(vector<Bug*>& bugs, int x, int y) const override;
  virtual bool canBreed() const override;
  virtual void breed(vector<Bug*>& bugs) const override;

  bool canMate() const;
  bool canMove() const;
};

class Worker : public Ant {
protected:
  int timeSinceMoved;

public:
  Worker(int x, int y, int initializedTime);
  virtual ~Worker();

  virtual void move(vector<pair<int, int>> positions) override;
  virtual bool starve() const override;
  virtual vector<pair<int, int>> canMove(vector<Bug*>& bugs, int x, int y) const override;
  virtual bool canBreed() const override;
  virtual void breed(vector<Bug*>& bugs) const override;
};

class MaleAnt : public Worker {
public:
  MaleAnt(int x, int y, int initializedTime);
  virtual ~MaleAnt();
  virtual bool canBreed() const override;
  virtual void breed(vector<Bug*>& bugs) const override;
};

#endif
