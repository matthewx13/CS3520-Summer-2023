#include "doodlebug.h"
#include "world.h"
#include <vector>
#include <random>
#include <algorithm>

Doodlebug::Doodlebug(int x, int y) : Organism(x, y), time_since_last_meal(0), move_counter(0) {}

Doodlebug::~Doodlebug() {}

void Doodlebug::move(World* world) {
    int x = get_x();
    int y = get_y();

    if (is_adjacent_to_ant(world)) {
        std::pair<int, int> ant_position = get_adjacent_ant(world);
        world->remove_organism(world->get_organism(ant_position.first, ant_position.second));
        set_position(ant_position.first, ant_position.second);
        move_counter++;
        time_since_last_meal = 0;
        return;
    } else {
        std::vector<std::pair<int, int>> possible_moves = get_possible_moves(x, y, world->get_world_size());
        if (!possible_moves.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, possible_moves.size() - 1);
            int random_index = dis(gen);
            std::pair<int, int> new_pos = possible_moves[random_index];
            set_position(new_pos.first, new_pos.second);
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

void Doodlebug::create_new_doodlebug(World* world) {
    int x = get_x();
    int y = get_y();

    std::vector<std::pair<int, int>> empty_cells = find_empty_cells(x, y, world->get_world_size());

    if (!empty_cells.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, empty_cells.size() - 1);
        int random_index = dis(gen);
        std::pair<int, int> random_empty_cell = empty_cells[random_index];
        world->add_organism(new Doodlebug(random_empty_cell.first, random_empty_cell.second));
    }
}

std::vector<std::pair<int, int>> Doodlebug::get_possible_moves(int x, int y, int world_size) {
    std::vector<std::pair<int, int>> moves;

    for (int i = std::max(0, x - 1); i <= std::min(world_size - 1, x + 1); i++) {
        for (int j = std::max(0, y - 1); j <= std::min(world_size - 1, y + 1); j++) {
            if (i != x || j != y) {
                moves.push_back(std::make_pair(i, j));
            }
        }
    }

    return moves;
}

std::vector<std::pair<int, int>> Doodlebug::find_empty_cells(int x, int y, int world_size) {
    std::vector<std::pair<int, int>> empty_cells;

    for (int i = std::max(0, x - 1); i <= std::min(world_size - 1, x + 1); i++) {
        for (int j = std::max(0, y - 1); j <= std::min(world_size - 1, y + 1); j++) {
            if (i != x || j != y) {
                if (world->is_empty(i, j)) {
                    empty_cells.push_back(std::make_pair(i, j));
                }
            }
        }
    }

    return empty_cells;
}
