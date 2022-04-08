

void System_Initialise();
void System_Exit();

/******************************************************
*		GLOBAL STRUCT DECLARATIONS
******************************************************/
typedef struct sys
{
	int fullscreen;
	int paused;
	int exit_confirmation;
} sys;


typedef struct item {
	AEGfxVertexList* pMesh;
	AEGfxTexture*	 pTexture;
	AEMtx33			 transform;
	float			 itemcounter;
}item;

typedef struct GameObjInst {
	unsigned int flag;
	item* pObject;
	AEVec2 PosCurr;
	AEVec2 velCurr;
	float dirCurr;
}GameObjInst;

typedef struct inv {
	item healthpotion;
	item staminapotion;
	item defencepotion;
}inv;


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