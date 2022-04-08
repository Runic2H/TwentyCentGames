#include "pch.hpp"


s8 fontId = -1;

s8 fontLarge = -1;

Maze_Struct* Maze;

int maze_init_flag = 0;
int curr_X_GRIDposition;
int curr_Y_GRIDposition;
float global_maze_cam_x;
float global_maze_cam_y;
int duck_dir = DD_UP;
bool is_focused;

// test bench
int level_iter;

FMOD::Channel* channel;	//JN: new code