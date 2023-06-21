#pragma once
#include "ant.h"

class WorkerAnt: public Ant {
public:
    // Constructor
    WorkerAnt(int x, int y);
    ~WorkerAnt();

    // Common methods for ants
    char get_symbol() const override;
};
