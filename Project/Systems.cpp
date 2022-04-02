#include "pch.hpp"


/********************************************************************
			GLOBAL DEFINITIONS
*********************************************************************/
sys systemsettings;			
player_statsheet* playerstats;
enemy_statsheet* enemystats;
inv* playerinventory;



void player_initialise() {

/******************************************************************
*		PLAYER STRUCT DEFINITION
******************************************************************/
	//playerstats->PlayerLevel = 1;
	//playerstats->PlayerXP = 0;
	//playerstats->health = 100;							//health
	//playerstats->maxhealth = 100;
	//playerstats->positionID = 1;						//starting grid
	//playerstats->SAFEGRID = 1;							//starting SAFEGRID pos
	//playerstats->damage = 10;							//damage
	//playerstats->staminaCD = 1.0f;						// Cooldown for attack and movement
	//playerstats->resetCD = playerstats->staminaCD;		// Reset Cooldown for attack and movement
	//playerstats->staminacount = 0;						// Character stamina count
	//playerstats->staminamax = 3;						// Character stamina max
	//playerstats->staminaX = -37.0f;						// X position of stamina
	//playerstats->is_dmgtaken = 0.0f;					//to implement visual animations in future
	//playerstats->is_attacking = false;					//for enemy damage checks
	//playerstats->positionX = 0.0f;
	//playerstats->positionY = 0.0f;
	//playerstats->movementdt = 0.0f;
	//playerstats->status = NEUTRAL;

	std::string str;
	std::ifstream inFile;
	inFile.open("..\\Bin\\GameData\\PlayerData.txt");

	inFile >> str >> playerstats->PlayerLevel;
	inFile >> str >> playerstats->PlayerXP;
	inFile >> str >> playerstats->health;
	inFile >> str >> playerstats->maxhealth;
	inFile >> str >> playerstats->positionID;
	inFile >> str >> playerstats->SAFEGRID;
	inFile >> str >> playerstats->damage;
	inFile >> str >> playerstats->staminaCD;
	inFile >> str >> playerstats->staminacount;
	inFile >> str >> playerstats->staminamax;
	inFile >> str >> playerstats->staminaX;
	inFile >> str >> playerstats->is_dmgtaken;
	inFile >> str >> playerstats->is_attacking;
	inFile >> str >> playerstats->positionX;
	inFile >> str >> playerstats->positionY;
	inFile >> str >> playerstats->movementdt;
	inFile >> str >> playerstats->status;
	playerstats->resetCD = playerstats->staminaCD;		// Reset Cooldown for attack and movement

	inFile.close();
}


void enemy_initialise() {

/******************************************************************
*		ENEMY STRUCT DEFINITION
******************************************************************/
	//enemystats->EnemyType = NORMAL;
	//enemystats->EnemyState = IDLE;					//Current Enemy State
	//enemystats->positionX = 0.0f;
	//enemystats->positionY = 0.0f;
	//enemystats->is_attacking = false;			//Check for enemy attacking, used for check when player can attack
	//enemystats->AttackCD = 0.60f;				//Delay timer before enemy attack during attack phase
	//enemystats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack
	//enemystats->DamageCD = 0.0f;				//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
	//enemystats->EnemyLevel = 1;

	std::string str;
	std::ifstream inFile;
	inFile.open("..\\Bin\\GameData\\EnemyData.txt");

	inFile >> str >> enemystats->EnemyType;
	inFile >> str >> enemystats->EnemyState;
	inFile >> str >> enemystats->positionX;
	inFile >> str >> enemystats->positionY;
	inFile >> str >> enemystats->is_attacking;
	inFile >> str >> enemystats->AttackCD;
	inFile >> str >> enemystats->DamageCD;
	inFile >> str >> enemystats->EnemyLevel;
	
	enemystats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack

	inFile.close();

}


void inventory_initialise() {
	playerinventory->defencepotion.itemcounter = 0.0f;
	playerinventory->healthpotion.itemcounter = 0.0f;
	playerinventory->staminapotion.itemcounter = 0.0f;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		 0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		  playerinventory->defencepotion.pMesh
		= playerinventory->healthpotion.pMesh
		= playerinventory->staminapotion.pMesh
		= AEGfxMeshEnd();
	AE_ASSERT_MESG(playerinventory->defencepotion.pMesh, "cannot create inventorymesh");

	playerinventory->defencepotion.pTexture = AEGfxTextureLoad("defencepotion.png");
	AE_ASSERT_MESG(playerinventory->defencepotion.pTexture, "cant create defencepotion texture\n");

	playerinventory->healthpotion.pTexture = AEGfxTextureLoad("healthpotion.png");
	AE_ASSERT_MESG(playerinventory->healthpotion.pTexture, "cant create healthpotion texture\n");

	playerinventory->staminapotion.pTexture = AEGfxTextureLoad("staminapotioninv.png");
	AE_ASSERT_MESG(playerinventory->staminapotion.pTexture, "cant create staminapotion texture\n");


	// transformation
	AEMtx33 scale, rot, buffer, trans;
	AEMtx33Scale(&scale, 42.0f, 42.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	
	AEMtx33Trans(&trans, -75.0f, -184.0f);
	AEMtx33Concat(&playerinventory->defencepotion.transform, &trans, &buffer);

	AEMtx33Trans(&trans, -5.0f, -184.0f);
	AEMtx33Concat(&playerinventory->healthpotion.transform, & trans, & buffer);

	AEMtx33Trans(&trans,  65.0f, -184.0f);
	AEMtx33Concat(&playerinventory->staminapotion.transform, &trans, &buffer);

}



void System_Initialise() {

/******************************************************************
*		FONTS AND SYSTEM SETTINGS
******************************************************************/
	fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
	fontLarge = AEGfxCreateFont("Roboto-Regular.ttf", 67);
	systemsettings.fullscreen = 0;
	systemsettings.paused = 0;


/******************************************************************
*		PLAYER INVENTORY CONSUMABLES
******************************************************************/
	playerinventory = new inv;
	inventory_initialise();

	playerstats = new player_statsheet;
	player_initialise();

	enemystats = new enemy_statsheet;
	enemy_initialise();

}


void System_Exit() {
	AEGfxDestroyFont(fontId);
	AEGfxDestroyFont(fontLarge);
	AEGfxTextureUnload(playerinventory->defencepotion.pTexture);
	AEGfxTextureUnload(playerinventory->healthpotion.pTexture);
	AEGfxTextureUnload(playerinventory->staminapotion.pTexture);
	AEGfxMeshFree(playerinventory->defencepotion.pMesh);
	delete playerstats;
	delete enemystats;
	delete playerinventory;
}