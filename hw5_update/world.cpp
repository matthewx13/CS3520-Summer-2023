#include <ncurses.h>
#include <iostream>
#include "world.h"

World::World() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

World::~World() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            delete grid[i][j];
        }
    }
}

template <typename T>
void add_organisms(int count, World* world) {
    for (int i = 0; i < count; ++i) {
        int x, y;
        do {
            x = 1 + rand() % (World::get_world_size()) ;
            y = 1 + rand() % (World::get_world_size());
        } while (!world->is_empty(x, y));
        T* organism = new T(x, y);
        world->add_organism(organism);
    }
}

void World::initialize(int doodlebugs, int queen_ants, int worker_ants, int male_ants) {
    std::cout << "Initializing world..." << std::endl;
    // Add initial organisms to the world at random locations
    add_organisms<Doodlebug>(doodlebugs, this);
    add_organisms<QueenAnt>(queen_ants, this);
    add_organisms<WorkerAnt>(worker_ants, this);
    add_organisms<MaleAnt>(male_ants, this);
}

bool World::run_simulation(int steps) {
    initscr(); // Initialize ncurses
    curs_set(0); // Hide the cursor
    timeout(100); // Set getch() to non-blocking with 100ms delay
    bool user_stopped = false;

    for (int i = 0; i < steps && !user_stopped; i++) {
        std::cout << "Step " << i << std::endl;
        move_organisms();
        breed_organisms();
        starve_organisms();
        display_world();
        int ch = getch(); // Wait for a key press or the timeout
        if (tolower(ch) == 'q') {
            user_stopped = true;
        }
    }

    endwin(); // End ncurses
    return user_stopped;
}

void World::add_organism(Organism* organism) {
    int x = organism->get_x();
    int y = organism->get_y();
    grid[x][y] = organism;
    
    if (dynamic_cast<Doodlebug*>(organism)) {
        doodlebugs.push_back(organism);
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
    // Move Doodlebugs
    for (Organism* doodlebug : doodlebugs) {
        if (doodlebug != nullptr) {
            remove_organism(doodlebug);
            doodlebug->move(this);
            add_organism(doodlebug);
        }
    }
    
    // Move Ants
    for (Organism* ant : ants) {
        if (ant != nullptr) {
            remove_organism(ant);
            ant->move(this);
            add_organism(ant);
        }
    }
}

void World::breed_organisms() {    
    // Breed Doodlebugs
    for (Organism* doodlebug : doodlebugs) {
        if (doodlebug != nullptr) {
            doodlebug->breed(this);
        }
    }
    
    // Breed Ants
    for (Organism* ant : ants) {
        if (ant != nullptr) {
            ant->breed(this);
        }
    }
}

void World::starve_organisms() {
    // Starve Doodlebugs
    for (Organism* doodlebug : doodlebugs) {
        if (doodlebug != nullptr) {
            doodlebug->starve(this);
        }
    }

    // Starve Ants
    for (Organism* ant : ants) {
        if (ant != nullptr) {
            ant->starve(this);
        }
    }
}

void World::display_world() {
    // draw a border around the world
    for (int i = 0; i < WORLD_SIZE; i++) {
        mvaddch(0, i, '-');
        mvaddch(WORLD_SIZE - 1, i, '-');
        mvaddch(i, 0, '|');
        mvaddch(i, WORLD_SIZE - 1, '|');
    }

    for (int i = 1; i < WORLD_SIZE - 1; i++) {
        for (int j = 1; j < WORLD_SIZE - 1; j++) {
            // Show space if empty, organism symbol otherwise
            if (grid[i][j] == nullptr) {
                mvaddch(i, j, ' ');
            } else {
                mvaddch(i, j, grid[i][j]->get_symbol());
            }
        }
    }
    refresh(); // Refresh the ncurses window
}

bool World::is_empty(int x, int y) {
    return grid[x][y] == nullptr;
}
