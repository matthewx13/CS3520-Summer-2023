#include "ant.h"
#include "world.h"

Ant::Ant(int x, int y) : Organism(x, y), move_counter(0), starve_counter(0) {}

Ant::~Ant() {}

void Ant::move(World* world) {
    // get the current position of the ant
    int x = get_x();
    int y = get_y();

    // get the direction of the ant
    int direction = rand() % 8;
    int new_x = x;
    int new_y = y;

    // calculate the new position of the ant, if it hits a wall, it will bounce like a ball
    switch (direction) {
        case 0: // up
            if (y - 1 < 0) {
                new_y = y + 1;
            } else {
                new_y = y - 1;
            }
            break;
        case 1: // down
            if (y + 1 >= world->get_world_size()) {
                new_y = y - 1;
            } else {
                new_y = y + 1;
            }
            break;
        case 2: // left
            if (x - 1 < 0) {
                new_x = x + 1;
            } else {
                new_x = x - 1;
            }
            break;
        case 3: // right
            if (x + 1 >= world->get_world_size()) {
                new_x = x - 1;
            } else {
                new_x = x + 1;
            }
            break;
        case 4: // up-left
            if (x - 1 < 0) {
                new_x = x + 1;
            } else {
                new_x = x - 1;
            }
            if (y - 1 < 0) {
                new_y = y + 1;
            } else {
                new_y = y - 1;
            }
            break;
        case 5: // up-right
            if (x + 1 >= world->get_world_size()) {
                new_x = x - 1;
            } else {
                new_x = x + 1;
            }
            if (y - 1 < 0) {
                new_y = y + 1;
            } else {
                new_y = y - 1;
            }
            break;
        case 6: // down-left
            if (x - 1 < 0) {
                new_x = x + 1;
            } else {
                new_x = x - 1;
            }
            if (y + 1 >= world->get_world_size()) {
                new_y = y - 1;
            } else {
                new_y = y + 1;
            }
            break;
        case 7: // down-right
            if (x + 1 >= world->get_world_size()) {
                new_x = x - 1;
            } else {
                new_x = x + 1;
            }
            if (y + 1 >= world->get_world_size()) {
                new_y = y - 1;
            } else {
                new_y = y + 1;
            }
            break;
    }

    // if the new position is out of bounds, bounce the ant off the wall

    // if the new position is unoccupied, move the ant to the new position
    if (world->is_empty(new_x, new_y)) {
        // move the ant to the new position
        set_x(new_x);
        set_y(new_y);

        // increment the move counter
        move_counter++;
        starve_counter = 0;
    } else { // otherwise, increment the starve counter
        // increment the starve counter
        starve_counter++;

        return;
    }
}

void Ant::breed(World* world) {
    return; // ants do not breed
}

void Ant::starve(World* world) {
    // ants starve if they have not moved after 5 time steps
    // if the ant has not moved after 5 time steps, it dies
    if (starve_counter >= 5) {
        world->remove_organism(this);
    }
}
