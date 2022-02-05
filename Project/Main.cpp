// ---------------------------------------------------------------------------
// includes

#include "pch.hpp"



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;
	int y{ 0 }, key{ 0 }, flag{ 0 }, counter{ 0 }, SAFEGRID{ 1 }, gridcounter{ 0 }, gr{ 0 }, isdamage{ 0 }, enemyhealth{ 500 };
	int  RGB{ 16384000 };
	int& RGBcounter{ RGB }, keypressed{ key }, showgridcounter{ gridcounter }, choosegrid{gr};
	int const ATTACK{ 1 };
	float movementdt, time{ 1.0 };
	float savedtime = time;
	int& x{ y }, enemy_health{ enemyhealth };
	bool is_enemyattacking;

	AEGfxTexture* playertexture;

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Changing the window title
	AESysSetWindowTitle("Combat system");

	// reset the system modules
	AESysReset();

	//Create the Mesh
	Character::c_statsheet* Player = Character::c_initialize();
	Enemy::E_StatSheet* Enemy = Enemy::EnemyInitialize();
	Enemy::EnemyCombatMesh();

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Creating the objects (Shapes)

	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)
	playertexture = AEGfxTextureLoad("ducky.jpg");
	AE_ASSERT_MESG(playertexture, "cant create duck texture\n");
	// Loading textures (images) end
	//////////////////////////////////



	//////////////////////////////////
	// Creating Fonts	

	// Creating Fonts end
	//////////////////////////////////


	// Game Loop
	while (gGameRunning)
	{

		Character::RGBloop(RGBcounter);
		Character::CombatMesh(RGBcounter);										//init character mesh


		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

			//PlayerMOVEMENT START
		if (keypressed == 0) {													//so i cant move whilst cooldown active
			keypressed = Character::PlayerMovement(x, Player);					//character movement	
			flag = keypressed;													//flag for player damage so it only counts once
		}
		//PlayerMOVEMENT END

		movementdt = (f32)AEFrameRateControllerGetFrameTime();					//dt time for counter


		Enemy::UpdateEnemyState(Enemy, Player);

	///////////////////////
	// Game loop update end


	// Game loop draw
	//////////////////

		Character::RenderPlayerGrid(Character::Player1Grid);
		Character::RenderPlayerGrid(Character::Player2Grid);
		Character::RenderPlayerGrid(Character::Player3Grid);
		Character::RenderPlayerGrid(Character::Player4Grid);
		Character::RenderPlayerGrid(Character::Player5Grid);
		Character::playerrender(playertexture, Player, Character::PlayerMesh);
		Enemy::RenderEnemyGrid(Enemy::EnemyGridIdle);
		Enemy::RenderEnemyGrid(Enemy::EnemyGridAttack);
		Enemy::RenderEnemy(Enemy::EnemyMesh, Enemy);
		/////////////////////
		// Game loop draw end


		//std::cout << (int)((AERandFloat()*10)/2) << "\n";


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



		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	delete Player;
	delete Enemy;
	Character::FreePlayerMesh();
	Enemy::FreeEnemyMesh();
	AEGfxTextureUnload(playertexture);
	AESysExit();
}