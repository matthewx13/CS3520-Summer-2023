#include "male_ant.h"

MaleAnt::MaleAnt(int x, int y) : Ant(x, y) {}

MaleAnt::~MaleAnt() {}

char MaleAnt::get_symbol() const {
    return 'o';
}
