#include "pch.hpp"


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Maze_Load()
{
	std::cout << "Maze:Load" << std::endl;
}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Maze_Initialize()
{
	std::cout << "Maze:Initialize" << std::endl;
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Maze_Update()
{
	std::cout << "Maze:Update" << std::endl;

	if (AEInputCheckCurr(AEVK_SPACE)) {
		next = COMBAT;
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}
}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Maze_Draw()
{
	std::cout << "Maze:Draw" << std::endl;
}


/*
	Cleans game object instances.
*/
void Maze_Free()
{
	std::cout << "Maze:Free" << std::endl;
}


/*
	Unload game assets. Frees and releases memory
*/
void Maze_Unload()
{
	std::cout << "Maze:Unload" << std::endl;
}