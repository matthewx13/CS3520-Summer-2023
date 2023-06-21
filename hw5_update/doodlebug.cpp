#include "doodlebug.h"
#include "world.h"
#include <vector>

Doodlebug::Doodlebug(int x, int y) : Organism(x, y), time_since_last_meal(0), move_counter(0) {}

Doodlebug::~Doodlebug() {}

void Doodlebug::move(World* world) {
    // movement of doodlebug and eats ants as well
    // find the location
    int x = get_x();
    int y = get_y();


    if (is_adjacent_to_ant(world)) {
        // if there is adjacent ant, find pos of any
        std::pair<int, int> ant_position = get_adjacent_ant(world);

        // ant removed
        world->remove_organism(world->get_organism(ant_position.first, ant_position.second));

        // doodlebug goes toward ant
        set_x(ant_position.first);
        set_y(ant_position.second);
        move_counter++;

        // time checker
        time_since_last_meal = 0;

        return;
    } else {

        // find direction that doodlebug is in
        int direction = rand() % 8;

        // find new pos
        int new_x = x;
        int new_y = y;

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

        // doodlebug can move into unoccupied areas
        if (world->is_empty(new_x, new_y)) {

            set_x(new_x);
            set_y(new_y);

            // count time for when it ate last meal
            time_since_last_meal++;
            move_counter++;
        }
    }
}

// breeding
void Doodlebug::breed(World* world) {
    if (move_counter >= 10) {
        create_new_doodlebug(world);

       
        move_counter = 0;
    }
}

void Doodlebug::starve(World* world) {
    if (time_since_last_meal > 10) {
        // doodlebug death
        world->remove_organism(this);
    }
}

char Doodlebug::get_symbol() const {
    return 'X';
}

bool Doodlebug::is_adjacent_to_ant(World* world) {

    int x = get_x();
    int y = get_y();

    // define possible pos of adjacent block
    const int adjacent_positions[][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    // check for adjacent ants
    for (const auto& pos : adjacent_positions) {
        int new_x = x + pos[0];
        int new_y = y + pos[1];
        if (is_ant(world, new_x, new_y)) {
            return true;
        }
    }

    return false;
}

bool Doodlebug::is_ant(World* world, int x, int y) {

    if (x < 0 || x >= world->get_world_size() || y < 0 || y >= world->get_world_size()) {
        return false;
    }

    Organism* organism = world->get_organism(x, y);

    // check type
    if (organism != nullptr) {
        char symbol = organism->get_symbol();
        return symbol == 'Q' || symbol == 'w' || symbol == 'o';
    }

    return false;
}

std::pair<int, int> Doodlebug::get_adjacent_ant(World* world) {

    int x = get_x();
    int y = get_y();


    if (is_ant(world, x - 1, y - 1)) {
        return std::make_pair(x - 1, y - 1);
    } else if (is_ant(world, x, y - 1)) {
        return std::make_pair(x, y - 1);
    } else if (is_ant(world, x + 1, y - 1)) {
        return std::make_pair(x + 1, y - 1);
    } else if (is_ant(world, x - 1, y)) {
        return std::make_pair(x - 1, y);
    } else if (is_ant(world, x + 1, y)) {
        return std::make_pair(x + 1, y);
    } else if (is_ant(world, x - 1, y + 1)) {
        return std::make_pair(x - 1, y + 1);
    } else if (is_ant(world, x, y + 1)) {
        return std::make_pair(x, y + 1);
    } else if (is_ant(world, x + 1, y + 1)) {
        return std::make_pair(x + 1, y + 1);
    } else {
        return std::make_pair(-1, -1);
    }
}

void Doodlebug::create_new_doodlebug(World *world) {
    // new doodlebug 
    int x = get_x();
    int y = get_y();

    // find empty cells
    std::vector<std::pair<int, int>> empty_cells;

    for (int i = std::max(0, x - 2); i <= std::min(world->get_world_size() - 1, x + 2); i++) {
        for (int j = std::max(0, y - 2); j <= std::min(world->get_world_size() - 1, y + 2); j++) {
            if (world->is_empty(i, j)) {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }

    // spawn doodlebug in empty cells
    if (!empty_cells.empty()) {
        int random_index = rand() % empty_cells.size();
        std::pair<int, int> random_empty_cell = empty_cells[random_index];

        world->add_organism(new Doodlebug(random_empty_cell.first, random_empty_cell.second));
    }
}
