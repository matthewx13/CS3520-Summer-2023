#include <ncurses.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "world.h"

World::World()
{
    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            cell = nullptr;
        }
    }
}

World::~World()
{
    for (auto &row : grid)
    {
        for (auto &cell : row)
        {
            delete cell;
            cell = nullptr;
        }
    }
}

template <typename T>
void add_organisms(int count, World *world)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, World::get_world_size());

    for (int i = 0; i < count; ++i)
    {
        int x, y;
        do
        {
            x = dist(gen);
            y = dist(gen);
        } while (!world->is_empty(x, y));

        auto organism = new T(x, y);
        world->add_organism(organism);
    }
}

void World::initialize(int doodlebugs, int queen_ants, int worker_ants, int male_ants)
{
    std::cout << "Initializing world..." << std::endl;

    add_organisms<Doodlebug>(doodlebugs, this);
    add_organisms<QueenAnt>(queen_ants, this);
    add_organisms<WorkerAnt>(worker_ants, this);
    add_organisms<MaleAnt>(male_ants, this);
}

bool World::run_simulation(int steps)
{
    initscr();   // Start ncurses
    curs_set(0);
    timeout(100); // 100ms delay
    bool user_stopped = false;

    for (int i = 0; i < steps && !user_stopped; i++)
    {
        std::cout << "Step " << i << std::endl;

        move_organisms();
        breed_organisms();
        starve_organisms();
        display_world();

        int ch = getch(); // Quit program if 'q' is pressed
        if (tolower(ch) == 'q')
        {
            user_stopped = true;
        }
    }

    user_stopped = true;
    endwin(); // End ncurses
    return user_stopped;
}

void World::add_organism(Organism *organism)
{
    int x = organism->get_x();
    int y = organism->get_y();
    grid[x][y] = organism;

    if (dynamic_cast<Doodlebug *>(organism))
    {
        doodlebugs.emplace_back(organism);
    }
    else
    {
        ants.emplace_back(organism);
    }
}

void World::remove_organism(Organism *organism)
{
    int x = organism->get_x();
    int y = organism->get_y();
    grid[x][y] = nullptr;

    if (Doodlebug *doodlebug = dynamic_cast<Doodlebug *>(organism))
    {
        doodlebugs.erase(std::remove(doodlebugs.begin(), doodlebugs.end(), doodlebug), doodlebugs.end());
    }
    else
    {
        ants.erase(std::remove(ants.begin(), ants.end(), organism), ants.end());
    }
}

Organism* World::get_organism(int x, int y) {
    return grid[x][y];
}

void World::move_organisms()
{
    // Doodlebug movement
    for (auto it = doodlebugs.begin(); it != doodlebugs.end();)
    {
        auto doodlebug = *it;
        if (doodlebug != nullptr)
        {
            remove_organism(doodlebug);
            doodlebug->move(this);
            add_organism(doodlebug);
            ++it;
        }
        else
        {
            it = doodlebugs.erase(it);
        }
    }

    // Ant movement
    for (auto it = ants.begin(); it != ants.end();)
    {
        auto ant = *it;
        if (ant != nullptr)
        {
            remove_organism(ant);
            ant->move(this);
            add_organism(ant);
            ++it;
        }
        else
        {
            it = ants.erase(it);
        }
    }
}

void World::breed_organisms()
{
    for (auto doodlebug : doodlebugs)
    {
        if (doodlebug != nullptr)
        {
            doodlebug->breed(this);
        }
    }

    for (auto ant : ants)
    {
        if (ant != nullptr)
        {
            ant->breed(this);
        }
    }
}

void World::starve_organisms()
{
    for (auto doodlebug : doodlebugs)
    {
        if (doodlebug != nullptr)
        {
            doodlebug->starve(this);
        }
    }

    for (auto ant : ants)
    {
        if (ant != nullptr)
        {
            ant->starve(this);
        }
    }
}

void World::display_world()
{
    // Draw the map
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        mvaddch(0, i, '-');
        mvaddch(WORLD_SIZE - 1, i, '-');
        mvaddch(i, 0, '|');
        mvaddch(i, WORLD_SIZE - 1, '|');
    }

    for (int i = 1; i < WORLD_SIZE - 1; i++)
    {
        for (int j = 1; j < WORLD_SIZE - 1; j++)
        {
            // Display space if area is empty
            if (grid[i][j] == nullptr)
            {
                mvaddch(i, j, ' ');
            }
            else
            {
                mvaddch(i, j, grid[i][j]->get_symbol());
            }
        }
    }

    refresh(); // Refresh the screen
}

bool World::is_empty(int x, int y)
{
    return grid[x][y] == nullptr;
}
