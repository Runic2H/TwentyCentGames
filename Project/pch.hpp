#ifndef PCH_H
#define PCH_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "AEEngine.h"
#include "Systems.hpp"
#include "Input.hpp"
#include "GameStateList.hpp"
#include "GameStateManager.hpp"
#include "Menu.hpp"
#include "Characters.hpp"
#include "Tutorial.hpp"
#include "Combat.hpp"
#include "Maze.hpp"
#include "Credits.hpp"
#include "gameover.hpp"
#include "LevelUp.hpp"


#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

extern s8 fontId;

extern s8 fontLarge;

extern Maze_Struct* Maze;

extern int maze_init_flag;
extern int curr_X_GRIDposition;
extern int curr_Y_GRIDposition;

extern player_statsheet* playerstats;
extern enemy_statsheet* enemystats;
extern sys systemsettings;


#endif	//PCH.H

