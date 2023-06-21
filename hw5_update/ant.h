#pragma once
#include "organism.h"

class Ant : public Organism {
public:
    // Constructor
    Ant(int x, int y);
    virtual ~Ant();

    // Common methods for ants
    void move(World* world) override;
    void breed(World* world) override;
    void starve(World* world) override;

private:
    int move_counter;
    int starve_counter;
};
