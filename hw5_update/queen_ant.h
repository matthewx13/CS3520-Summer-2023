#pragma once
#include "ant.h"
#include <vector>
#include <algorithm>
#include <random>

class QueenAnt : public Ant { 
public:
  // Constructor
  QueenAnt(int x, int y);
  ~QueenAnt();

  // Common methods for ants
  void move(World* world) override;
  void breed(World* world) override;
  void starve(World* world) override;
  char get_symbol() const override;

private:
  int move_counter;
  bool male_adjacent;
  bool has_mated;
  bool can_move;

  bool is_adjacent_to_male(World* world);
  void create_new_ants(World* world);
  void create_new_queen(World* world);
};
