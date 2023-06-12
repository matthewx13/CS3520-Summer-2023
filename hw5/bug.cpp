#include <ncurses.h>
#include <cstdlib>
#include "bug.hpp"

// Bug methods
Bug::Bug(int x, int y, int initializedTime)
    : x(x), y(y), initializedTime(initializedTime), symbol('?') {}

bool Bug::bugExists(const vector<Bug*>& bugs, int x, int y) {
    for (const Bug* bug : bugs) {
        if (bug->getX() == x && bug->getY() == y) {
            return true;
        }
    }
    return false;
}

void Bug::drawBug(Bug* bug) {
    mvprintw(bug->getY(), bug->getX(), "%c", bug->getSymbol());
}

void Bug::displayBugInfo(int count, int x, int y, Bug* bug) {
    mvprintw(x, y, "[%i] Bug: x %i, y %i, it %i, s %c ", count, bug->getX(),
             bug->getY(), bug->getInitializedTime(), bug->getSymbol());
}

void Bug::removeEatenBug(vector<Bug*>& bugs, int x, int y) {
    for (auto it = bugs.begin(); it != bugs.end();) {
        if ((*it)->getX() == x && (*it)->getY() == y) {
            delete *it;
            it = bugs.erase(it);
        } else {
            ++it;
        }
    }
}

void Bug::operator++(Bug& bug) {
    ++(bug.it);
}

bool Bug::compareBugs(const Bug* a, const Bug* b) {
    const string order = "XQow";
    auto orderA = order.find(a->getSymbol());
    auto orderB = order.find(b->getSymbol());
    return orderA < orderB;
}

void Bug::addBug(vector<Bug*>& bugs, Bug* newBug) {
    auto it = lower_bound(bugs.begin(), bugs.end(), newBug, compareBugs);
    bugs.insert(it, newBug);
}

char Bug::getSymbol() const {
    return symbol;
}

int Bug::getX() const {
    return x;
}

int Bug::getY() const {
    return y;
}

int Bug::getInitializedTime() const {
    return initializedTime;
}

void Bug::setX(int x) {
    this->x = x;
}

void Bug::setY(int y) {
    this->y = y;
}

// DoodleBug methods
DoodleBug::DoodleBug(int x, int y, int initializedTime)
    : Bug(x, y, initializedTime) {
    symbol = 'X';
    timeSinceEating = 0;
}

DoodleBug::~DoodleBug() {}

void DoodleBug::move(vector<pair<int, int>> positions) {
    // TODO: Implement DoodleBug move logic
}

bool DoodleBug::starve() const {
    // TODO: Implement DoodleBug starve logic
    return false;
}

vector<pair<int, int>> DoodleBug::canMove(vector<Bug*>& bugs, int x, int y) const {
    // TODO: Implement DoodleBug canMove logic
    return false;
}

bool DoodleBug::canBreed() const {
    return (initializedTime > 0 && initializedTime % 10 == 0);
}

void DoodleBug::breed(vector<Bug*>& bugs) const {
    // TODO: Implement DoodleBug breed logic
}

// Ant methods
Ant::Ant(int x, int y, int lifetime) : Bug(x, y, lifetime) {
    symbol = 'a';
}

Ant::~Ant() {}

// Queen methods
Queen::Queen(int x, int y, int lifetime) : Ant(x, y, lifetime) {
    symbol = 'Q';
    timeSinceMadeQueen = 0;
    timeSinceLayedEggs = 0;
    timeSinceMated = 0;
}

Queen::~Queen() {}

void Queen::move(vector<pair<int, int>> positions) {
    // TODO: Implement Queen move logic
}

bool Queen::starve() const {
    // TODO: Implement Queen starve logic
    return false;
}

vector<pair<int, int>> Queen::canMove(vector<Bug*>& bugs, int x, int y) const {
    // TODO: Implement Queen canMove logic
    return false;
}

bool Queen::canMate() const {
    // TODO: Implement Queen canMate logic
    return false;
}

bool Queen::canMove() const {
    // TODO: Implement Queen canMove logic
    return false;
}

bool Queen::canBreed() const {
    // TODO: Implement Queen canBreed logic
    return false;
}

void Queen::breed(vector<Bug*>& bugs) const {
    // TODO: Implement Queen breed logic
}

// Worker methods
Worker::Worker(int x, int y, int initializedTime) : Ant(x, y, initializedTime) {
    symbol = 'w';
    timeSinceMoved = 0;
}

Worker::~Worker() {}

void Worker::move(vector<pair<int, int>> positions) {
    // TODO: Implement Worker move logic
}

bool Worker::starve() const {
    // TODO: Implement Worker starve logic
    return false;
}

vector<pair<int, int>> Worker::canMove(vector<Bug*>& bugs, int x, int y) const {
    // TODO: Implement Worker canMove logic
    return false;
}

bool Worker::canBreed() const {
    // TODO: Implement Worker canBreed logic
    return false;
}

void Worker::breed(vector<Bug*>& bugs) const {
    // TODO: Implement Worker breed logic
}

// MaleAnt methods
MaleAnt::MaleAnt(int x, int y, int initializedTime) : Worker(x, y, initializedTime) {
    symbol = 'o';
}

bool MaleAnt::canBreed() const {
    // TODO: Implement MaleAnt canBreed logic
    return false;
}

void MaleAnt::breed(vector<Bug*>& bugs) const {
    // TODO: Implement MaleAnt breed logic
}

MaleAnt::~MaleAnt() {}
