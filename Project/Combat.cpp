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

//int const ATTACK{ 5 };

int& x{ switchvalue }, y{};

float movementdt;// time{ 1.0 };

//AEGfxTexture* playertexture;


	E_StatSheet* Enemy = EnemyInitialize();
	c_statsheet* Player = c_initialize();


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Combat_Load()
{
	//std::cout << "Combat:Load" << std::endl;

	//playertexture = AEGfxTextureLoad("ducky.jpg");
	//AE_ASSERT_MESG(playertexture, "cant create duck texture\n");

}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{
	//std::cout << "Combat:Initialize" << std::endl;

	CombatMesh(RGBcounter);
	EnemyCombatMesh();
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update()
{
	//std::cout << "Combat:Update" << std::endl;

	if (AEInputCheckTriggered(AEVK_1)) {
		next = MAZE;
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}

	RGBloop(RGBcounter);
	CombatMesh(RGBcounter);

	if (keypressed == 0) {													//so i cant move whilst cooldown active
		keypressed = PlayerMovement(x, Player);					//character movement	
		flag = keypressed;													//flag for player damage so it only counts once
	}

	movementdt = (f32)AEFrameRateControllerGetFrameTime();					//dt time for counter

	UpdateEnemyState(Enemy, Player);



	if (keypressed == 1) {
		//this is for the delay before popping back to original position
		++counter;

		if (counter > 42) {
			Player->positionX = 0.0f;
			Player->positionY = 0.0f;
			Player->positionID = 1;
			keypressed = 0;
			counter = 0;
		}
	}

}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	//std::cout << "Combat:Draw" << std::endl;

	RenderPlayerGrid(Player1Grid);
	RenderPlayerGrid(Player2Grid);
	RenderPlayerGrid(Player3Grid);
	RenderPlayerGrid(Player4Grid);
	RenderPlayerGrid(Player5Grid);
	playerrender(Player, PlayerMesh);
	RenderEnemyGrid(EnemyGridIdle);
	RenderEnemyGrid(EnemyGridAttack);
	RenderEnemy(EnemyMesh, Enemy);
}


/*
	Cleans game object instances.
*/
void Combat_Free()
{
	//std::cout << "Combat:Free" << std::endl;

	delete Player;
	delete Enemy;
	FreePlayerMesh();
	FreeEnemyMesh();
	//AEGfxTextureUnload(playertexture);
	AESysExit();
}


/*
	Unload game assets. Frees and releases memory
*/
void Combat_Unload()
{
	//std::cout << "Combat:Unload" << std::endl;
}