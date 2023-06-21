#include "male_ant.h"
#include "worker_ant.h"

MaleAnt::MaleAnt(int x, int y) : Ant(x, y) {}

MaleAnt::~MaleAnt() {}

char MaleAnt::get_symbol() const {
    return 'o';
}

WorkerAnt::WorkerAnt(int x, int y) : Ant(x, y) {}

WorkerAnt::~WorkerAnt() {}

char WorkerAnt::get_symbol() const {
    return 'o';
}
