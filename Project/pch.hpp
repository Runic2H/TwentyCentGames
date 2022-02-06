#ifndef PCH_H
#define PCH_H


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "AEEngine.h"
#include "Systems.hpp"
#include "Characters.hpp"
//#include "Enemy.hpp"
#include "Maze.hpp"
#include "Combat.hpp"
#include "Input.hpp"
#include "GameStateList.hpp"
#include "GameStateManager.hpp"


#endif	//PCH.H


#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

//struct c_statsheet Player;
//struct E_StatSheet Enemy;

//enum PlayerPos { TOP = 2, ORIGIN = 1, BOTTOM = 4, BACK = 3, ATTACK = 5 }; //Please use this to decipher which grid player is on