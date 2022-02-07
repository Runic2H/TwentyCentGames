#include "pch.hpp"

int  RGB{ 16384000 };

int& RGBcounter{ RGB };

int switchvalue{ 1 },
keyvalue{ 0 },
flag{ 0 },
counter{ 0 },
SAFEGRID{ 1 },
gridcounter{ 0 },
gr{ 0 };

int& keypressed{ keyvalue },
showgridcounter{ gridcounter },
choosegrid{ gr };
//s8 fontId = 0;


using namespace Enemies;
using namespace Character;

int& x{ switchvalue }, y{};

float movementdt;// time{ 1.0 };

AEGfxTexture* playertexture;
AEGfxTexture* enemytexture;


E_StatSheet* Enemy = EnemyInitialize();
c_statsheet* Player = c_initialize();


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Combat_Load()
{
	std::cout << "Combat:Load" << std::endl;
	playertexture = AEGfxTextureLoad("ducky.jpg");
	AE_ASSERT_MESG(playertexture, "cant create duck texture\n");

	enemytexture = AEGfxTextureLoad("Turtle.png");
	AE_ASSERT_MESG(enemytexture, "cant create turtle texture\n");

	//fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);


}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{


	std::cout << "Combat:Initialize" << std::endl;

}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update()
{

	//std::cout << "Combat:Update" << std::endl;

	Character::RGBloop(RGBcounter);
	CombatMesh(RGBcounter);
	EnemyCombatMesh();

	movementdt = (f32)AEFrameRateControllerGetFrameTime();					//dt time for counter


	//Character::CombatMesh(RGBcounter);


	if (Enemy->health <= 0 || Player->health <= 0)
	{
		std::cout << "Something Died.";
		next = GS_QUIT;
	}


	if (keypressed == 0) {													//so i cant move whilst cooldown active
		keypressed = Character::PlayerMovement(x, Player);								//character movement	
		flag = keypressed;													//flag for player damage so it only counts once
	}

	if (keypressed == 1) {
		Player->movementdt -= DT;
		if (Player->movementdt <= 0.0f) {
			Player->positionX = 0.0f;
			Player->positionY = 0.0f;
			Player->positionID = 1;
			Player->is_attacking = false;
			keypressed = 0;
		}
	}

	UpdateEnemyState(Enemy, Player);
	flag = (x == ATTACK) ? 1 : 0;
	
	std::cout << "Player Health: " << Player->health << "| Enemy Health: " << Enemy->health << "\n";
}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	//std::cout << "Combat:Draw" << std::endl;

	//Character::RenderPlayerHealth(fontId, Player);
	//RenderEnemyHealth(fontId, Enemy);
	GridCheck(Enemy->is_attacking, Enemy->AttackCD, Player->SAFEGRID);
	playerrender(playertexture, Player, Character::PlayerMesh);
	
	if (Enemy->AttackCD <= 0.45f)
	{
		RenderEnemyGrid(EnemyGridAttack);
	}
	
	RenderEnemy(enemytexture, EnemyMesh, Enemy);
}


/*
	Cleans game object instances.
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;

	delete Player;
	delete Enemy;
	FreePlayerMesh();
	FreeEnemyMesh();
	//AEGfxDestroyFont(fontId);
	AEGfxTextureUnload(playertexture);
	AEGfxTextureUnload(enemytexture);
	AESysExit();
}


/*
	Unload game assets. Frees and releases memory
*/
void Combat_Unload()
{
	std::cout << "Combat:Unload" << std::endl;
}