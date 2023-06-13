#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "critter.hpp"


int main() {
    std::srand(std::time(nullptr));
    // you can edit grid size
    int gridSize = 100;
    std::vector<std::vector<Critter*>> grid(gridSize, std::vector<Critter*>(gridSize, nullptr));

    // Prompt user for input
    int numDoodlebugs, numWorkerAnts, numMaleAnts, numQueenAnts;
    std::cout << "Enter the number of doodlebugs: ";
    std::cin >> numDoodlebugs;
    std::cout << "Enter the number of worker ants: ";
    std::cin >> numWorkerAnts;
    std::cout << "Enter the number of male ants: ";
    std::cin >> numMaleAnts;
    std::cout << "Enter the number of queen ants: ";
    std::cin >> numQueenAnts;

    // Place doodlebugs
    for (int i = 0; i < numDoodlebugs; i++) {
        int row, col;
        do {
            row = std::rand() % gridSize;
            col = std::rand() % gridSize;
        } while (grid[row][col] != nullptr);

        grid[row][col] = new Doodlebug(row, col);
    }

    // Place worker ants
    for (int i = 0; i < numWorkerAnts; i++) {
        int row, col;
        do {
            row = std::rand() % gridSize;
            col = std::rand() % gridSize;
        } while (grid[row][col] != nullptr);

        grid[row][col] = new Ant(row, col,'W');
    }

    // Place male ants
    for (int i = 0; i < numMaleAnts; i++) {
        int row, col;
        do {
            row = std::rand() % gridSize;
            col = std::rand() % gridSize;
        } while (grid[row][col] != nullptr);

        grid[row][col] = new Ant(row, col,'o');
    }

    // Place queen ants
    for (int i = 0; i < numQueenAnts; i++) {
        int row, col;
        do {
            row = std::rand() % gridSize;
            col = std::rand() % gridSize;
        } while (grid[row][col] != nullptr);

        Ant* ant = new Ant(row, col,'Q');
        
        grid[row][col] = ant;
    }

// Simulation loop
    int steps = 0;
    while (true) {
        // Move and breed doodlebugs
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                Critter* critter = grid[i][j];
                if (critter != nullptr && critter->getType() == CritterType::DOODLEBUG) {
                    critter->move(grid);
                    critter->breed(grid);
                    critter->starve(grid);
                }
            }
        }

        // Move and breed ants
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                Critter* critter = grid[i][j];
                if (critter != nullptr && critter->getType() == CritterType::ANT) {
                    critter->move(grid);
                    critter->breed(grid);
                }
            }
        }

        steps++;

        // Print grid
        std::cout << "Grid after " << steps << " steps:\n";
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                Critter* critter = grid[i][j];
                if (critter == nullptr) {
                    std::cout << ".";
                } else if (critter->getType() == CritterType::ANT) {
                    if (Ant* ant = dynamic_cast<Ant*>(critter))
                        std::cout << ant->anttype;
                } else if (critter->getType() == CritterType::DOODLEBUG) {
                    std::cout << "X";
                }
            }
            std::cout << "\n";
        }

        // Check if the grid is fully occupied
        bool gridFull = true;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j] == nullptr) {
                    gridFull = false;
                    break;
                }
            }
            if (!gridFull) {
                break;
            }
        }

        // Break out of the simulation loop if the grid is fully occupied
        if (gridFull) {
            std::cout << "Grid is fully occupied. Simulation ends.\n";
            break;
        }

        // Prompt for next step or exit
        std::cout << "Press Enter to continue or type 'exit' to quit: ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }
    }

    return 0;
}
