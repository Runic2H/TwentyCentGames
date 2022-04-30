/**************************************************************************
 * 	File name	:	Systems.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Richmond Choo Tze Yong	(PRIMARY AUTHOR - 98%)
 *					Hu Jun Ning				(SECONDARY AUTHOR - 1%)
 *					Matthew Cheung Jun Yin	(SECONDARY AUTHOR - 1%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/


/**************************************************************
*	Initialises what is needed by the program
***************************************************************/
void System_Initialise();

/**************************************************************
*	Unloads all the meshes and textures and fonts at system
*	exit
***************************************************************/
void System_Exit();

/******************************************************
*		GLOBAL STRUCT DECLARATIONS
******************************************************/
typedef struct sys
{
	int fullscreen;
	int paused;
	int mute;
	int options;
	float digipenTimer;
	float twentycentTimer;
	float fmodTimer;
	int exit_confirmation;
} sys;


typedef struct item {
	AEGfxVertexList* pMesh;
	AEGfxTexture*	 pTexture;
	AEMtx33			 transform;
	float			 itemcounter;
}item;


typedef struct inv {
	item healthpotion;
	item staminapotion;
	item defencepotion;
}inv;

typedef struct GameObjInst {
	unsigned int flag;
	unsigned int type;
	item* pObject;
	AEVec2 PosCurr;
	AEVec2 velCurr;
	float dirCurr;
	float scale;

}GameObjInst;

typedef struct player_statsheet
{
	inv playerinventory;
	float positionX;
	float positionY;
	int positionID;
	int SAFEGRID;
	int health;
	int staminacount;
	int staminamax;
	float staminaCD;
	float resetCD;
	float staminaX;
	int maxhealth;
	int damage;
	bool is_attacking;
	float is_dmgtaken;
	float movementdt;
	int status;
	int PlayerXP;
	int PlayerXPMax;
	int PlayerLevel;
	int statuscounter;
	float debuffcounter;

}player_statsheet;


typedef struct enemy_statsheet
{
	int EnemyType;
	int health;
	int maxhealth;
	float damage;
	float enemytypedamage;
	int EnemyState;
	float EnemyCD;
	float positionX;
	float positionY;
	bool is_attacking;
	float AttackCD;
	int EnemyGrid;
	float DamageCD;
	int DebuffCounter;
	int EnemyXP;
	int EnemyLevel;

}enemy_statsheet;