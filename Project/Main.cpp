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
	int y{ 0 }, keypressed{ 0 }, flag{ 0 }, counter{ 0 }, SAFEGRID{ 1 }, isdamage{ 0 }, enemyhealth{ 500 };
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
	Character::CombatMesh();
	Character::c_statsheet* Player = Character::c_initialize();

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
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

			//PlayerMOVEMENT START
		if (keypressed == 0) {										//so i cant move whilst cooldown active
			keypressed = Character::PlayerMovement(x, Player);		//character movement	
			flag = keypressed;										//flag for player damage so it only counts once
		}
		//PlayerMOVEMENT END

		movementdt = (f32)AEFrameRateControllerGetFrameTime();		//dt time for counter



			//logic for player taking damage
			//player wont take damange if he stays in the initial grid (to replace with randomly generated grids)
		if (flag == 1) {
			isdamage = Character::Playerdamage(Player, SAFEGRID);				//should the player take damage?
			flag = 0;
		}



		//PlayerATTACK START
		is_enemyattacking = false;								//PLACEHOLDER.
		flag = (x == ATTACK) ? 1 : 0;

		if (flag == 1 && Player->is_attacking == true) {
			Character::PlayerAttack(Player, is_enemyattacking, enemyhealth);
			x = 0;
			flag = 0;
		}
		//PlayerATTACK END


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
		/////////////////////
		// Game loop draw end



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
	Character::FreePlayerMesh();
	AEGfxTextureUnload(playertexture);
	AESysExit();
}