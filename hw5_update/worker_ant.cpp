#include "worker_ant.h"

WorkerAnt::WorkerAnt(int x, int y) : Ant(x, y) {}

WorkerAnt::~WorkerAnt() {}

char WorkerAnt::get_symbol() const {
    return 'w';
}
