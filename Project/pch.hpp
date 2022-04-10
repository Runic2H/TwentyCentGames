/**************************************************************************
 * 	File name	:	pch.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Matthew Cheung Jun Yin	(SECONDARY AUTHOR - 20%)
					Hu Jun Ning				(SECONDARY AUTHOR - 20%)
					Elton Teo Zhe Wei		(SECONDARY AUTHOR - 20%)
					Louis Mineo				(SECONDARY AUTHOR - 20%)
					Richmond Choo Tze Yong	(SECONDARY AUTHOR - 20%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#ifndef PCH_H
#define PCH_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <fmod.hpp>
#include <windowsx.h>
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
#include "victoryscreen.hpp"
#include "AudioManager.hpp"


#define GRID_NUM 5;

#define DT (f32)AEFrameRateControllerGetFrameTime();

extern s8 fontId;
extern s8 fontLarge;

extern Maze_Struct* Maze;

extern int maze_init_flag;
extern int curr_X_GRIDposition;
extern int curr_Y_GRIDposition;
extern s32 cursorx, cursory;

extern player_statsheet* playerstats;
extern enemy_statsheet* enemystats;
extern inv* playerinventory;
extern sys systemsettings;
extern bool is_focused;
extern GameObjInst* ParticleInstList;

extern float bgm_volume;					//JN: new code
extern float sfx_volume;					//JN: new code
extern float sfx_volume_max;
extern float bgm_volume_max;


/**************************************************************
*	initialises the meshes and textures for the pausemenu
***************************************************************/
void initialise_pausemenu();

/**************************************************************
*	the exit confirmation update loop
***************************************************************/
void LogicExit_Confirmation();

/**************************************************************
*	renders the exit confirmation
***************************************************************/
void RenderExit_Confirmation();

/**************************************************************
*	the pause menu update loop
***************************************************************/
void logicpausemenu();

/**************************************************************
*	draw pause menu
***************************************************************/
void renderpausemenu();

/**************************************************************
*	unloads the pause menu meshes 
***************************************************************/
void unloadpausemenu();

/**************************************************************
*	initialises the optionmenu
***************************************************************/
void initialise_optionmenu();

/**************************************************************
*	the logic for the options menu
***************************************************************/
void logicoptionmenu();

/**************************************************************
*	draws the options menu
***************************************************************/
void renderoptionmenu();

/**************************************************************
*	unloads the options menu mesh
***************************************************************/
void unloadoptionmenu();

/**************************************************************
*	initialises the player stats from file
***************************************************************/
void player_initialise();

/**************************************************************
*	initialises the enemy stats from file
***************************************************************/
void enemy_initialise();

/**************************************************************
*	creates the particle game object instance
***************************************************************/
GameObjInst* particleInstCreate(float scale, float posX, float posY, int type);

/**************************************************************
*	destroys the particle game object instances
***************************************************************/
void particleInstDestroy(GameObjInst* pInst);


enum consumables { HEALTH, STAMINA, DEFENCE };
enum EnemyPos { IDLE, ATTACKING };
enum ENEMY_TYPE { NORMAL, ICE, FIRE, ENEMYBOSS };
enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK };
enum PlayerStatus { NEUTRAL, FROSTED, FROZEN, BURNING };
enum ParticleTypes {particlePLAYER, particleENEMY, particleENEMYFROST, particleENEMYFIRE};


#endif	//PCH.H

