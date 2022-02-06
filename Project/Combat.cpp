#include "pch.hpp"



/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Combat_Load()
{
	std::cout << "Combat:Load" << std::endl;
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
	std::cout << "Combat:Update" << std::endl;

	if (AEInputCheckTriggered(AEVK_1)) {
		next = MAZE;
	}


	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}
}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	std::cout << "Combat:Draw" << std::endl;
}


/*
	Cleans game object instances.
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;
}


/*
	Unload game assets. Frees and releases memory
*/
void Combat_Unload()
{
	std::cout << "Combat:Unload" << std::endl;
}