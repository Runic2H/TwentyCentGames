#include "pch.hpp"



void Combat_Load();

/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize();


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update();


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw();

/*
	Cleans game object instances.
*/
void Combat_Free();


/*
	Unload game assets. Frees and releases memory
*/
void Combat_Unload();

