#pragma once
#include <iostream>

class World; // Add this forward declaration

class Organism {

public:
    Organism(int x, int y);
    virtual ~Organism();

    virtual void move(World* world) = 0;
    virtual void breed(World* world) = 0;
    virtual void starve(World* world) = 0;
    virtual char get_symbol() const = 0;

    int get_x() const;
    int get_y() const;

    void set_x(int x);
    void set_y(int y);

protected:
    int x, y;
};
