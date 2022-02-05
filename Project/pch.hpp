#pragma once

#include "AEEngine.h"
#include <math.h>
#include <iostream>
#include "Character.hpp"
#include "Enemy.hpp"

#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

enum PlayerPos { TOP = 2, ORIGIN = 1, BOTTOM = 4, BACK = 3, ATTACK = 5 }; //Please use this to decipher which grid player is on