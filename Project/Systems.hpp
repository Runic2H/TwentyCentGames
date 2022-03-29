

void System_Initialise();
void System_Exit();

/******************************************************
*		GLOBAL STRUCT DECLARATIONS
******************************************************/
typedef struct sys
{
	int fullscreen;
} sys;

typedef struct player_statsheet
{
	float positionX;
	float positionY;
	int positionID;
	int SAFEGRID;
	int health;
	int staminacount;
	int staminamax;
	float staminaCD;
	float staminaX;
	int maxhealth;
	int damage;
	int playerCD;
	bool is_attacking;
	float is_dmgtaken;
	float movementdt;
	int status;
	int PlayerXP;
	int PlayerLevel;
}player_statsheet;


typedef struct enemy_statsheet
{
	int EnemyType;
	int health;
	int maxhealth;
	int damage;
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