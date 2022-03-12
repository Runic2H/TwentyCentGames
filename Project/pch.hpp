#ifndef PCH_H
#define PCH_H
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "AEEngine.h"
#include "Systems.hpp"
#include "Characters.hpp"
#include "Maze.hpp"
#include "Combat.hpp"
#include "Input.hpp"
#include "GameStateList.hpp"
#include "GameStateManager.hpp"
#include "Menu.hpp"
#include "gameover.hpp";



#endif	//PCH.H

#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

extern s8 fontId;
