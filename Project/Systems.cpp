#include "pch.hpp"

sys systemsettings;			//definition, outside scope
player_statsheet* playerstats;
enemy_statsheet* enemystats;


void System_Initialise() {

/******************************************************************
*		FONTS AND SYSTEM SETTINGS
******************************************************************/
	fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
	systemsettings.fullscreen = 0;


/******************************************************************
*		PLAYER STRUCT DEFINITION
******************************************************************/
	playerstats = new player_statsheet;
	playerstats->PlayerLevel = 1;
	playerstats->PlayerXP = 0;
	playerstats->health = 100;							//health
	playerstats->maxhealth = 100;
	playerstats->positionID = 1;						//starting grid
	playerstats->SAFEGRID = 1;							//starting SAFEGRID pos
	playerstats->damage = 10;							//damage
	playerstats->staminaCD = 1.0f;						// Cooldown for attack and movement
	playerstats->staminacount = 3;						// Character stamina count
	playerstats->staminamax = 3;						// Character stamina max
	playerstats->staminaX = -37.0f;						// X position of stamina
	playerstats->playerCD = 5;							//Cooldown for attack and movement
	playerstats->is_dmgtaken = 0.0f;					//to implement visual animations in future
	playerstats->is_attacking = false;					//for enemy damage checks
	playerstats->positionX = 0.0f;
	playerstats->positionY = 0.0f;
	playerstats->movementdt = 0.0f;
	playerstats->status = 0;							// NEUTRAL IS 0
	

	// QUESTION: how do i extern the enums


/******************************************************************
*		ENEMY STRUCT DEFINITION
******************************************************************/
	enemystats = new enemy_statsheet;

	enemystats->EnemyType = 0;
	enemystats->EnemyState = 0;					//Current Enemy State
	enemystats->positionX = 0.0f;
	enemystats->positionY = 0.0f;
	enemystats->is_attacking = false;			//Check for enemy attacking, used for check when player can attack
	enemystats->AttackCD = 0.60f;				//Delay timer before enemy attack during attack phase
	enemystats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack
	enemystats->DamageCD = 0.0f;				//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
	enemystats->EnemyLevel = 1;
}


void System_Exit() {

	AEGfxDestroyFont(fontId);
	delete playerstats;
	delete enemystats;
}