#include "male_female_ant.h"

MaleAnt::MaleAnt(int x, int y) : Ant(x, y) {}

MaleAnt::~MaleAnt() {}

char MaleAnt::get_symbol() const {
    return 'o';
}

WorkerAnt::WorkerAnt(int x, int y) : Ant(x, y) {}

WorkerAnt::~WorkerAnt() {}

char WorkerAnt::get_symbol() const {
    return 'w';
}
