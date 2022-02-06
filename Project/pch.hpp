#pragma once

#include "AEEngine.h"
#include <math.h>
#include <iostream>
#include "Character.hpp"
#include "Enemy.hpp"

#define DT (f32)AEFrameRateControllerGetFrameTime();

enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK }; //Please use this to decipher which grid player is on