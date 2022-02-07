#ifndef PCH_H
#define PCH_H


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



#endif	//PCH.H


//#define ORIGIN 0;
//#define TOP 1;
//#define BACK 2;
//#define DOWN 3;
//#define ATTACK 4;

#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();


//enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK }; //Please use this to decipher which grid player is on

//enum EnemyPos { IDLE, ATTACKING };