#include "ant.h"
#include "world.h"

Ant::Ant(int x, int y) : Organism(x, y), move_counter(0), starve_counter(0) {}

Ant::~Ant() {}

void Ant::move(World* world) {
    int current_x = get_x();
    int current_y = get_y();

    int direction = rand() % 8;
    int new_x = current_x;
    int new_y = current_y;

    switch (direction) {
        case 0: // Move up
            if (current_y - 1 < 0) {
                new_y = current_y + 1;
            } else {
                new_y = current_y - 1;
            }
            break;
        case 1: // Move down
            if (current_y + 1 >= world->get_world_size()) {
                new_y = current_y - 1;
            } else {
                new_y = current_y + 1;
            }
            break;
        case 2: // Move left
            if (current_x - 1 < 0) {
                new_x = current_x + 1;
            } else {
                new_x = current_x - 1;
            }
            break;
        case 3: // Move right
            if (current_x + 1 >= world->get_world_size()) {
                new_x = current_x - 1;
            } else {
                new_x = current_x + 1;
            }
            break;
        case 4: // Move up-left
            if (current_x - 1 < 0) {
                new_x = current_x + 1;
            } else {
                new_x = current_x - 1;
            }
            if (current_y - 1 < 0) {
                new_y = current_y + 1;
            } else {
                new_y = current_y - 1;
            }
            break;
        case 5: // Move up-right
            if (current_x + 1 >= world->get_world_size()) {
                new_x = current_x - 1;
            } else {
                new_x = current_x + 1;
            }
            if (current_y - 1 < 0) {
                new_y = current_y + 1;
            } else {
                new_y = current_y - 1;
            }
            break;
        case 6: // Move down-left
            if (current_x - 1 < 0) {
                new_x = current_x + 1;
            } else {
                new_x = current_x - 1;
            }
            if (current_y + 1 >= world->get_world_size()) {
                new_y = current_y - 1;
            } else {
                new_y = current_y + 1;
            }
            break;
        case 7: // Move down-right
            if (current_x + 1 >= world->get_world_size()) {
                new_x = current_x - 1;
            } else {
                new_x = current_x + 1;
            }
            if (current_y + 1 >= world->get_world_size()) {
                new_y = current_y - 1;
            } else {
                new_y = current_y + 1;
            }
            break;
    }

    if (world->is_empty(new_x, new_y)) {
        set_x(new_x);
        set_y(new_y);

        move_counter++;
        starve_counter = 0;
    } else {
        starve_counter++;
        return;
    }
}

void Ant::breed(World* world) {
    return; // Ants do not breed
}

void Ant::starve(World* world) {
    if (starve_counter >= 5) {
        world->remove_organism(this);
    }
}
