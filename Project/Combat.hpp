/**************************************************************************
 * 	File name	:	Combat.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Richmond Choo Tze Yong	(PRIMARY AUTHOR - 45%)
 *					Elton Teo Zhe Wei		(PRIMARY AUTHOR - 45%)
 *					Louis Mineo				(SECONDARY AUTHOR - 5%)
 *					Hu Jun Ning				(SECONDARY AUTHOR - 5%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

/*
	Load function for the combat gamestate
*/
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

