#include "pch.hpp"

#pragma once
const int noOfRows = 15, noOfCols = 15; // DO NOT CHANGE MY GRIDS PLZZZZ :((

extern int maze_iswall_isnotwall[noOfRows][noOfCols]; // remove later after finishing maze-gen algo



struct MazeCells
{
	int is_wall;
	//int is_PlayerPos;

};

struct MazeDimensions
{
	int noOfRows;
	int noOfCols;
	float mazeWindowHeight;
	float mazeWindowWidth;
	float cellWidth;
	float cellHeight;
	float MazeWindowStart_X;
	float MazeWindowStart_Y;

};


struct Maze_Struct
{
	MazeCells grid[noOfRows][noOfCols];
	MazeDimensions specifications;
};

Maze_Struct* CreateMaze(int Exe_WindowHeight, int Exe_WindowWidth, int noOfRows, int noOfCols);

void MAZE_CreateMESH_MazeWindow2(AEGfxVertexList*& MazeWindow_Var, Maze_Struct* Maze, int colour_HEXA);

void MAZE_CreateMESH_CellOutline2(AEGfxVertexList*& CellOutlineMesh_Var, Maze_Struct* Maze, int colour_HEX);

void MAZE_CreateSolidCell2(AEGfxVertexList*& SolidCellMesh_Var, Maze_Struct* Maze, int colour_HEXA);

void MAZE_DrawMazeCellsandCellOutline2(AEGfxVertexList*& WALLCellMesh,

	AEGfxVertexList*& PATHCellMesh,
	AEGfxVertexList*& CellOutlineMesh,
	Maze_Struct* Maze);

void MAZE_DrawMazeOutline2(AEGfxVertexList*& mazeOutlineMesh, Maze_Struct* Maze);

void MAZE_DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY);

void MAZE_CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width);

int MAZE_CharMoveCHECK_NEXT_POS(int UpDownLeftRight, Maze_Struct* Maze, int& Char_Pos_X, int& Char_Pos_Y);


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Maze_Load();



/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Maze_Initialize();


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Maze_Update();



/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Maze_Draw();


/*
	Cleans game object instances.
*/
void Maze_Free();



/*
	Unload game assets. Frees and releases memory
*/
void Maze_Unload();
