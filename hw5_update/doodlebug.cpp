#include "doodlebug.h"
#include "world.h"
#include <vector>
#include <cstdlib>

Doodlebug::Doodlebug(int x, int y) : Organism(x, y), time_since_last_meal(0), move_counter(0) {}

Doodlebug::~Doodlebug() {}

void Doodlebug::move(World* world) {
    int x = get_x();
    int y = get_y();

    if (is_adjacent_to_ant(world)) {
        std::pair<int, int> ant_position = get_adjacent_ant(world);
        world->remove_organism(world->get_organism(ant_position.first, ant_position.second));
        set_x(ant_position.first);
        set_y(ant_position.second);
        move_counter++;
        time_since_last_meal = 0;
        return;
    } else {
        int direction = rand() % 8;
        int new_x = x;
        int new_y = y;

        switch (direction) {
            case 0: // up
                new_y = (y - 1 < 0) ? y + 1 : y - 1;
                break;
            case 1: // down
                new_y = (y + 1 >= world->get_world_size()) ? y - 1 : y + 1;
                break;
            case 2: // left
                new_x = (x - 1 < 0) ? x + 1 : x - 1;
                break;
            case 3: // right
                new_x = (x + 1 >= world->get_world_size()) ? x - 1 : x + 1;
                break;
            case 4: // up-left
                new_x = (x - 1 < 0) ? x + 1 : x - 1;
                new_y = (y - 1 < 0) ? y + 1 : y - 1;
                break;
            case 5: // up-right
                new_x = (x + 1 >= world->get_world_size()) ? x - 1 : x + 1;
                new_y = (y - 1 < 0) ? y + 1 : y - 1;
                break;
            case 6: // down-left
                new_x = (x - 1 < 0) ? x + 1 : x - 1;
                new_y = (y + 1 >= world->get_world_size()) ? y - 1 : y + 1;
                break;
            case 7: // down-right
                new_x = (x + 1 >= world->get_world_size()) ? x - 1 : x + 1;
                new_y = (y + 1 >= world->get_world_size()) ? y - 1 : y + 1;
                break;
        }

        if (world->is_empty(new_x, new_y)) {
            set_x(new_x);
            set_y(new_y);
            time_since_last_meal++;
            move_counter++;
        }
    }
}

void Doodlebug::breed(World* world) {
    if (move_counter >= 10) {
        create_new_doodlebug(world);
        move_counter = 0;
    }
}

void Doodlebug::starve(World* world) {
    if (time_since_last_meal > 10) {
        world->remove_organism(this);
    }
}

char Doodlebug::get_symbol() const {
    return 'X';
}

bool Doodlebug::is_adjacent_to_ant(World* world) {
    int x = get_x();
    int y = get_y();
    const int adjacent_positions[][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
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
    int x = get_x();
    int y = get_y();
    std::vector<std::pair<int, int>> empty_cells;
    for (int i = std::max(0, x - 2); i <= std::min(world->get_world_size() - 1, x + 2); i++) {
        for (int j = std::max(0, y - 2); j <= std::min(world->get_world_size() - 1, y + 2); j++) {
            if (world->is_empty(i, j)) {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }
    if (!empty_cells.empty()) {
        int random_index = rand() % empty_cells.size();
        std::pair<int, int> random_empty_cell = empty_cells[random_index];
        world->add_organism(new Doodlebug(random_empty_cell.first, random_empty_cell.second));
    }
}
