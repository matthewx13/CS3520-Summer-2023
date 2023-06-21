#pragma once
#include "ant.h"

class MaleAnt : public Ant {
public:
    MaleAnt(int x, int y);
    ~MaleAnt();

    // Common methods for ants
    char get_symbol() const override;
};

class WorkerAnt : public Ant {
public:
    WorkerAnt(int x, int y);
    ~WorkerAnt();

    // Common methods for ants
    char get_symbol() const override;
};
