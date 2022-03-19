#include "pch.hpp"


s8 fontId = -1;

Maze_Struct* Maze;

int maze_init_flag = 0;
int curr_X_GRIDposition;
int curr_Y_GRIDposition;

Characters::Character::c_statsheet* Player = Characters::Character::c_initialize();
