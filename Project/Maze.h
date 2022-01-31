#pragma once
const int noOfRows = 15, noOfCols = 15; // DO NOT CHANGE MY GRIDS PLZZZZ :((

extern int maze_iswall_isnotwall[noOfRows][noOfCols]; // remove later after finishing maze-gen algo



struct MazeCells
{
	int is_wall;

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

//TESTING
////////////////////////
struct Maze_Struct
{
	MazeCells grid[noOfRows][noOfCols];
	MazeDimensions specifications;
};


//END OF TESTING
///////////////////////

void MAZE_initMazeCell(MazeCells cells[noOfRows][noOfCols]);

//MazeCells* Maze_init(int noOfRows, int noOfCols);

//Creating Meshes
MazeDimensions MAZE_InitMazeDimension(	int Exe_WindowHeight, 
										int Exe_WindowWidth, 
										int noOfRows, 
										int noOfCols
										);

void MAZE_CreateMESH_MazeWindow(AEGfxVertexList*& MazeWindow_Var, MazeDimensions MAZE_DIMESIONS_STRUCT, int colour_HEXA);

void MAZE_CreateMESH_CellOutline(AEGfxVertexList*& CellOutlineMesh_Var, MazeDimensions MAZE_DIMESIONS_STRUCT, int colour_HEX);

void MAZE_CreateSolidCell(AEGfxVertexList*& SolidCellMesh_Var, MazeDimensions MAZE_DIMESIONS_STRUCT, int colour_HEXA);

void MAZE_DrawMazeCellsandCellOutline(AEGfxVertexList*& WALLCellMesh,
									AEGfxVertexList*& PATHCellMesh,
									AEGfxVertexList*& CellOutlineMesh,
									MazeDimensions MazeDimesionsStruct,
									MazeCells cells[noOfRows][noOfCols],
									AEGfxRenderMode RenderMode);

void MAZE_DrawMazeOutline(AEGfxVertexList*& mazeOutlineMesh, MazeDimensions MazeDimesionsStruct, AEGfxMeshDrawMode RenderMode);