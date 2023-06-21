#include "organism.h"

Organism::Organism(int x, int y) : x(x), y(y) {}

void Organism::set_x(int new_x) {
    x = new_x;
}

void Organism::set_y(int new_y) {
    y = new_y;
}

int Organism::get_x() const {
    return x;
}

int Organism::get_y() const {
    return y;
}

Organism::~Organism() {}
