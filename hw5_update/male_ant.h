#pragma once
#include "ant.h"

class MaleAnt : public Ant {
public:
    MaleAnt(int x, int y);
    ~MaleAnt();

    // Common methods for ants
    char get_symbol() const override;
};
