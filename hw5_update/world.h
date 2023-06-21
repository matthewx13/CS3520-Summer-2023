#pragma once

#include "organism.h"
#include "queen_ant.h"
#include "worker_ant.h"
#include "male_ant.h"
#include "doodlebug.h"

class World {
public:
    World();
    ~World();

    void initialize(int doodlebugs, int queen_ants, int worker_ants, int male_ants); 
    bool run_simulation(int steps);

    void add_organism(Organism* organism);
    void remove_organism(Organism* organism);
    bool is_empty(int x, int y);
    Organism* get_organism(int x, int y);

    static int get_world_size() { return WORLD_SIZE; }

private:
    static const int WORLD_SIZE = 52;

    std::vector<Organism*> doodlebugs;
    std::vector<Organism*> ants;

    Organism* grid[WORLD_SIZE][WORLD_SIZE];

    void move_organisms();
    void breed_organisms();
    void starve_organisms();
    void display_world();
};
