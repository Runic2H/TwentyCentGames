#include "pch.hpp"

#pragma once
/*
constexpr int level[4] = {11,15,19,23};
const int noOfRows = level[0],noOfCols = level[0]; // DO NOT CHANGE MY GRIDS PLZZZZ :((

extern int maze_iswall_isnotwall[noOfRows][noOfCols]; 
extern int maze_visibility[noOfRows][noOfCols];
*/

constexpr int level[4] = { 7,15,19,31 };
const int maxRows = level[4 - 1], maxCols = level[4 - 1];

extern int maze_iswall_isnotwall[maxRows][maxCols];
extern int maze_visibility[maxRows][maxCols];



enum MazeCellValue
{
	EMPTY_PATH = 0,
	WALL = 1,
	CHEST = 3,
	ENEMY = 9,
	BOSS = 5

	
};

 
struct MazeCells
{
	int value = 0;
	//int is_PlayerPos;
	bool is_visible = 0;

};

struct MazeDimensions
{
	int noOfRows = 0;
	int noOfCols = 0;
	float mazeWindowHeight = 0;
	float mazeWindowWidth = 0;
	float cellWidth = 0;
	float cellHeight = 0;
	float MazeWindowStart_X = 0;
	float MazeWindowStart_Y = 0;

};


struct Maze_Struct
{
	//MazeCells grid[noOfRows][noOfCols];
	MazeCells grid[maxRows][maxCols];
	MazeDimensions specifications;
};


/* FOR MAZEGEN */
/*==================================================================================*/
void MazeGenAlgo_MakeMaze();
void MazeGenAlgo_ChoosingStartingPos(int& startX, int& startY, int& endX, int& endY, int height, int width);
void MazeGenAlgo_Set_walls();
void MazeGenAlgo_PrintRetrievedInformation();
bool MazeGenAlgo_PostGenCheck();
void MazeGenAlgo_BossSpawn();
void MazeGenAlgo();
/*========================================================================================*/

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

void MAZE_ChestOpened(int curr_X_GRIDposition, int curr_Y_GRIDposition);

void MAZE_StepOntoSpecialCell(int curr_X_GRIDposition, int curr_Y_GRIDposition);

void Maze_CameraAdjustment(int direction);

void MAZE_SaveCellVisibility(Maze_Struct* maze_var);

void MAZE_ReLOADCellVisibility(Maze_Struct* maze_var);

void Maze_Minimap_Draw(float cam_x, float cam_y, float x_offset, float y_offset);

void Maze_Inventory_MeshUpdate(float camX, float camY);

void Maze_Inventory_MeshRender();

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
