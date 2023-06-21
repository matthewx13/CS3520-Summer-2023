#pragma once
#include "organism.h"
// Doodlebug class (inherits from Organism)
class Doodlebug : public Organism {
public:
    // Constructor
    Doodlebug(int x, int y);
    ~Doodlebug();

    // Common methods for doodlebugs
    void move(World* world) override;
    void breed(World* world) override;
    void starve(World* world) override;
    char get_symbol() const override;

private:
    int time_since_last_meal;
    int move_counter;

    bool is_adjacent_to_ant(World* world);
    std::pair<int, int> get_adjacent_ant(World* world);
    void create_new_doodlebug(World* world);
    bool is_ant(World* world, int x, int y);
};
