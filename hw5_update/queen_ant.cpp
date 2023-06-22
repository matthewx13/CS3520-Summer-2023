#include "queen_ant.h"
#include "world.h"

QueenAnt::QueenAnt(int x, int y) : Ant(x, y), move_counter(0), male_adjacent(false), has_mated(false), can_move(false) {}

QueenAnt::~QueenAnt() {}

void QueenAnt::move(World* world) {
    if (can_move) {
        Ant::move(world);
    } else {
        if (has_mated && move_counter >= 10) {
            can_move = true;
        }
    }

    male_adjacent = is_adjacent_to_male(world);
    move_counter++;
}

void QueenAnt::breed(World* world) {
    if (has_mated) {
        if (move_counter >= 10) {
            create_new_queen(world);
            move_counter = 0;
            has_mated = false;
        }
    } else {
        if (move_counter >= 25 && male_adjacent) {
            create_new_ants(world);
            move_counter = 0;
            male_adjacent = false;
            has_mated = true;
        }
    }

    if (move_counter >= 60) {
        world->remove_organism(this);
    }
}

void QueenAnt::starve(World* world) {
    // Do nothing, queen ants don't starve
    return;
}

char QueenAnt::get_symbol() const {
    return 'Q';
}

bool QueenAnt::is_adjacent_to_male(World* world) {
    int x = get_x();
    int y = get_y();

    const int adjacent_positions[][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };

    for (const auto& pos : adjacent_positions) {
        int new_x = x + pos[0];
        int new_y = y + pos[1];

        if (world->is_occupied_by_male_ant(new_x, new_y)) {
            return true;
        }
    }

    return false;
}

void QueenAnt::create_new_ants(World* world) {
    int x = get_x();
    int y = get_y();
    const int breeding_range = 2;

    std::vector<std::pair<int, int>> empty_cells;
    for (int i = x - breeding_range; i <= x + breeding_range; i++) {
        for (int j = y - breeding_range; j <= y + breeding_range; j++) {
            if (world->is_empty(i, j)) {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }

    std::shuffle(empty_cells.begin(), empty_cells.end(), std::default_random_engine());

    int num_new_ants = std::min(static_cast<int>(empty_cells.size()), 10);

    for (int i = 0; i < num_new_ants; i++) {
        int new_x = empty_cells[i].first;
        int new_y = empty_cells[i].second;
        bool is_worker_ant = (rand() % 10) < 8;

        if (is_worker_ant) {
            world->add_organism(new WorkerAnt(new_x, new_y));
        } else {
            world->add_organism(new MaleAnt(new_x, new_y));
        }
    }
}

void QueenAnt::create_new_queen(World* world) {
    int x = get_x();
    int y = get_y();
    const int breeding_range = 2;

    std::vector<std::pair<int, int>> empty_cells;
    for (int i = x - breeding_range; i <= x + breeding_range; i++) {
        for (int j = y - breeding_range; j <= y + breeding_range; j++) {
            if (world->is_empty(i, j)) {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }

    std::shuffle(empty_cells.begin(), empty_cells.end(), std::default_random_engine());

    if (!empty_cells.empty()) {
        int new_x = empty_cells[0].first;
        int new_y = empty_cells[0].second;
        world->add_organism(new QueenAnt(new_x, new_y));
    }
}
