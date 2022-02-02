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
	int x{ 0 }, keypressed{ 0 }, flag{ 0 };
	float movementdt, time{ 1.0 };
	float savedtime = time;


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
	Character::c_statsheet *Player = Character::c_initialize();

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Creating the objects (Shapes)

	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)

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

	//PLAYER MOVEMENT
		AEInputCheckTriggered(AEVK_D) ? x = 1 : x = x;
		AEInputCheckTriggered(AEVK_W) ? x = 2 : x = x;
		AEInputCheckTriggered(AEVK_A) ? x = 3 : x = x;
		AEInputCheckTriggered(AEVK_S) ? x = 4 : x = x;

		movementdt = (f32)AEFrameRateControllerGetFrameTime();		//dt time for counter

		keypressed = Character::PlayerMovement(x, Player);	
			x = 0;
			flag = keypressed;


			//logic for player taking damage
			//player wont take damange if he stays in the initial grid (for testing only)
		if (flag == 1 && Player->positionID != 1) {								
		Player->health -= 1;
		std::cout << "the player's health is: " << Player->health << std::endl;
		}

		flag = 0;

	//PLAYER MOVEMENT END

		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw
		Character::RenderPlayerGrid(Character::Player1Grid);
		Character::RenderPlayerGrid(Character::Player2Grid);
		Character::RenderPlayerGrid(Character::Player3Grid);
		Character::RenderPlayerGrid(Character::Player4Grid);
		Character::RenderPlayerGrid(Character::Player5Grid);
		Character::playerrender(Player,Character::PlayerMesh);


		//this is for the delay before popping back to original position
		if (keypressed == 1) {

			if (time >= 0) {
				//std::cout << time << "\n";
				time -= movementdt;
			}
			else {
				Player->positionX = 0.0f;
				Player->positionY = 0.0f;
				Player->positionID = 1;
				time = savedtime;
				keypressed = 0;
			}
		}

		// Game loop draw end
		/////////////////////


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	Character::FreePlayerMesh();
	AESysExit();
}