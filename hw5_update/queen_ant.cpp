#include "queen_ant.h"
#include "world.h"

QueenAnt::QueenAnt(int x, int y) : Ant(x, y), move_counter(0), male_adjacent(false), has_mated(false), can_move(false) {}

QueenAnt::~QueenAnt() {}

void QueenAnt::move(World* world) {
    if (can_move && has_mated && move_counter >= 10) {
        Ant::move(world);
    } else if (!can_move && has_mated && move_counter >= 10) {
        can_move = true;
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

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (world->is_empty(i, j)) {
                continue;
            }

            Organism* organism = world->get_organism(i, j);
            if (organism->get_symbol() == 'o') {
                return true;
            }
        }
    }

    return false;
}

void QueenAnt::create_new_ants(World* world) {
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

    std::shuffle(empty_cells.begin(), empty_cells.end(), std::default_random_engine());

    int num_new_ants = std::min(10, static_cast<int>(empty_cells.size()));

    for (int i = 0; i < num_new_ants; i++) {
        int x = empty_cells[i].first;
        int y = empty_cells[i].second;
        int type = rand() % 10;

        if (type < 8) {
            world->add_organism(new WorkerAnt(x, y));
        } else {
            world->add_organism(new MaleAnt(x, y));
        }
    }
}

void QueenAnt::create_new_queen(World* world) {
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

    std::shuffle(empty_cells.begin(), empty_cells.end(), std::default_random_engine());

    if (empty_cells.size() > 0) {
        int x = empty_cells[0].first;
        int y = empty_cells[0].second;

        world->add_organism(new QueenAnt(x, y));
    }
}
