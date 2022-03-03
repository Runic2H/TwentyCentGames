#include "pch.hpp"

int  RGB{ 16384000 };

int& RGBcounter{ RGB };

int switchvalue{ 0 },
keyvalue{ 0 },
counter{ 0 },
SAFEGRID{ 1 },
gridcounter{ 0 },
gr{ 0 };

int& keypressed{ keyvalue },
showgridcounter{ gridcounter },
choosegrid{ gr };


using namespace Enemies;
using namespace Character;

int& x{ switchvalue }, y{};

float movementdt;

AEGfxTexture* playertexture;
AEGfxTexture* enemytexture;
AEGfxTexture* staminapotion;

E_StatSheet* Enemy;
c_statsheet* Player;

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

	staminapotion = AEGfxTextureLoad("staminapotion.png");
	AE_ASSERT_MESG(staminapotion, "cant create stamina potion texture\n");

	Enemy = EnemyInitialize();			//change name to load
	Player = c_initialize();


}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{
	MeshInit();		// Single init for the meshes that only need to be created once (NON RGB MESHES)
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update()
{
	
	RGBloop(RGBcounter);
	CombatMesh(RGBcounter);
	EnemyCombatMesh();

	movementdt = (f32)AEFrameRateControllerGetFrameTime();					//dt time for counter


	//Character::CombatMesh(RGBcounter);


		if (Enemy->health <= 0)
		{
			std::cout << "You Won!\n";
			next = MAZE;
		}

		else if (Player->health <= 0) {
			std::cout << "You Died!\n";
			next = GS_QUIT;
		}


	if (keypressed == 0) {													// so i cant move whilst cooldown active
		PlayerMovement(x, Player, keypressed);								// character movement	
		StaminaLogic(Player, keypressed);
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
}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	StaminaRender(Player, staminapotion);
	RenderPlayerHealth(fontId, Player);
	RenderEnemyHealth(fontId, Enemy);
	GridCheck(Enemy->is_attacking, Enemy->AttackCD, Player->SAFEGRID);
	playerrender(playertexture, Player, Character::PlayerMesh);
	RenderPlayerGrid(playermaxhealth);


	if (Enemy->AttackCD <= 0.45f)
	{
		RenderEnemyGrid(EnemyGridAttack);
	}
	
	RenderEnemy(enemytexture, EnemyMesh, Enemy);
}


/*
	Cleans game object instances. will be run in restart
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;

}


/*
	Unload game assets. Frees and releases memory, wont be run in restart
*/
void Combat_Unload()
{
	delete Player;
	delete Enemy;
	FreePlayerMesh();
	FreeEnemyMesh();
	AEGfxTextureUnload(playertexture);
	AEGfxTextureUnload(enemytexture);
	AEGfxTextureUnload(staminapotion);
}