#include <ncurses.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "world.h"

World::World() {
    std::fill_n(&grid[0][0], WORLD_SIZE * WORLD_SIZE, nullptr);
}

World::~World() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            delete grid[i][j];
        }
    }
}

template <typename T>
void World::add_organisms(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, World::get_world_size());

    for (int i = 0; i < count; ++i) {
        int x, y;
        do {
            x = dist(gen);
            y = dist(gen);
        } while (!is_empty(x, y));
        T* organism = new T(x, y);
        add_organism(organism);
    }
}

void World::initialize(int doodlebugs, int queen_ants, int worker_ants, int male_ants) {
    std::cout << "Initializing world..." << std::endl;
    add_organisms<Doodlebug>(doodlebugs);
    add_organisms<QueenAnt>(queen_ants);
    add_organisms<WorkerAnt>(worker_ants);
    add_organisms<MaleAnt>(male_ants);
}

bool World::run_simulation(int steps) {
    initscr(); // Start ncurses
    curs_set(0);
    timeout(100); // 100ms delay
    bool user_stopped = false;

    for (int i = 0; i < steps && !user_stopped; i++) {
        std::cout << "Step " << i << std::endl;
        move_organisms();
        breed_organisms();
        starve_organisms();
        display_world();

        int ch = getch(); // Quit program if 'q' is pressed
        if (tolower(ch) == 'q') {
            user_stopped = true;
        }
    }

    user_stopped = true;
    endwin(); // End ncurses
    return user_stopped;
}

void World::add_organism(Organism* organism) {
    int x = organism->get_x();
    int y = organism->get_y();
    grid[x][y] = organism;

    if (Doodlebug* doodlebug = dynamic_cast<Doodlebug*>(organism)) {
        doodlebugs.push_back(doodlebug);
    } else {
        ants.push_back(organism);
    }
}

void World::remove_organism(Organism* organism) {
    int x = organism->get_x();
    int y = organism->get_y();
    grid[x][y] = nullptr;

    if (Doodlebug* doodlebug = dynamic_cast<Doodlebug*>(organism)) {
        doodlebugs.erase(std::remove(doodlebugs.begin(), doodlebugs.end(), doodlebug), doodlebugs.end());
    } else {
        ants.erase(std::remove(ants.begin(), ants.end(), organism), ants.end());
    }
}

Organism* World::get_organism(int x, int y) {
    return grid[x][y];
}

void World::move_organisms() {
    for (auto it = doodlebugs.begin(); it != doodlebugs.end();) {
        Organism* doodlebug = *it;
        if (doodlebug != nullptr) {
            remove_organism(doodlebug);
            doodlebug->move(this);
            add_organism(doodlebug);
            ++it;
        } else {
            it = doodlebugs.erase(it);
        }
    }

    for (auto it = ants.begin(); it != ants.end();) {
        Organism* ant = *it;
        if (ant != nullptr) {
            remove_organism(ant);
            ant->move(this);
            add_organism(ant);
            ++it;
        } else {
            it = ants.erase(it);
        }
    }
}

void World::breed_organisms() {
    for (Organism* doodlebug : doodlebugs) {
        if (doodlebug != nullptr) {
            doodlebug->breed(this);
        }
    }

    for (Organism* ant : ants) {
        if (ant != nullptr) {
            ant->breed(this);
        }
    }
}

void World::starve_organisms() {
    for (Organism* doodlebug : doodlebugs) {
        if (doodlebug != nullptr) {
            doodlebug->starve(this);
        }
    }

    for (Organism* ant : ants) {
        if (ant != nullptr) {
            ant->starve(this);
        }
    }
}

void World::display_world() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        mvaddch(0, i, '-');
        mvaddch(WORLD_SIZE - 1, i, '-');
        mvaddch(i, 0, '|');
        mvaddch(i, WORLD_SIZE - 1, '|');
    }

    for (int i = 1; i < WORLD_SIZE - 1; i++) {
        for (int j = 1; j < WORLD_SIZE - 1; j++) {
            if (grid[i][j] == nullptr) {
                mvaddch(i, j, ' ');
            } else {
                mvaddch(i, j, grid[i][j]->get_symbol());
            }
        }
    }
    refresh();
}

bool World::is_empty(int x, int y) {
    return grid[x][y] == nullptr;
}
