#include <iostream>
#include "world.h"

int main() {
    int simulation_steps;
    std::cout << "Enter the number of simulation steps: ";
    std::cin >> simulation_steps;

    // ask user for specs
    int doodlebugs;
    std::cout << "Please enter desired num of doodlebugs: ";
    std::cin >> doodlebugs;

    int queen_ants;
    std::cout << "Please enter desired num of queen ants: ";
    std::cin >> queen_ants;

    int worker_ants;
    std::cout << "Please enter desired num of worker ants (female ants): ";
    std::cin >> worker_ants;

    int male_ants;
    std::cout << "Please enter desired num of male ants: ";
    std::cin >> male_ants;
    
    World world;
    world.initialize(doodlebugs, queen_ants, worker_ants, male_ants);

    bool user_stopped = false;
    while (!user_stopped) {
        user_stopped = world.run_simulation(1000); //run sim 1000 times or until user stops it
    }

    return 0;
}
