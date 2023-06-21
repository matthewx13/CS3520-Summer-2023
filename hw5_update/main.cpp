#include <iostream>
#include "world.h"

int main() {
    int simulation_steps;
    std::cout << "Enter the number of simulation steps: ";
    std::cin >> simulation_steps;

    // Prompt the user to specify how many doodlebugs, queen ants, male and female ants your simulation would start with.
    int doodlebugs;
    std::cout << "Enter the number of doodlebugs: ";
    std::cin >> doodlebugs;
    int queen_ants;
    std::cout << "Enter the number of queen ants: ";
    std::cin >> queen_ants;
    int worker_ants;
    std::cout << "Enter the number of worker ants: ";
    std::cin >> worker_ants;
    int male_ants;
    std::cout << "Enter the number of male ants: ";
    std::cin >> male_ants;
    
    World world;
    world.initialize(doodlebugs, queen_ants, worker_ants, male_ants);

    bool user_stopped = false;
    while (!user_stopped) {
        user_stopped = world.run_simulation(1000); // Run the simulation for 1000 steps or until the user stops it
    }

    return 0;
}
