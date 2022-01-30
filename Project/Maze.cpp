#include "AEEngine.h"
#include "Maze.h"


	/*
	const int noOfRows = 15, noOfCols = 15;

	MazeCells cells[noOfRows][noOfCols];


	MazeCells* Maze_init(MazeCells cells,int noOfRows, int noOfCols)
	{
		for (int r = 0; r < noOfRows; r++)
		{
			for (int c = 0; c < noOfRows; c++)
			{
				cells[r][c].is_wall = maze_iswall_isnotwall[r][c];
			}
		}
		return cells;
	}
	*/

int maze_iswall_isnotwall[noOfRows][noOfCols] =
{

		1,1,1,1,1, 1,1,0,1,1, 1,1,1,1,1,
		1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,1,1,1, 1,0,1,1,1,
		1,0,1,0,1, 0,0,0,1,0, 1,0,0,0,1,
		1,0,1,1,1, 1,1,0,1,0, 1,1,1,0,1,
		1,0,1,0,0, 0,0,0,1,0, 0,0,1,0,1,
		1,0,1,0,1, 1,1,1,1,1, 1,0,1,1,1,
		1,0,0,0,1, 0,0,0,0,0, 1,0,0,0,1,
		1,0,1,1,1, 0,1,1,1,0, 1,0,1,0,1,
		1,0,1,0,0, 0,1,0,1,0, 0,0,1,0,1,
		1,0,1,0,1, 1,1,0,1,1, 1,1,1,0,1,
		1,0,0,0,1, 0,0,0,1,0, 0,0,1,0,1,
		1,1,1,1,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,1,0,0,0, 1,0,0,0,1,
		1,1,1,1,1, 1,1,0,1,1, 1,1,1,1,1
};

void MAZE_initMazeCell(MazeCells cells[noOfRows][noOfCols])
{
	for (int r = 0; r < noOfRows; r++)
	{
		for (int c = 0; c < noOfRows; c++)
		{
			cells[r][c].is_wall = maze_iswall_isnotwall[r][c];
		}
	}
}

	MazeDimensions MAZE_InitMazeDimension(int Exe_WindowHeight, int Exe_WindowWidth, int noOfRows, int noOfCols)
	{
		MazeDimensions MazeDimesionsStruct;
		MazeDimesionsStruct.noOfRows = noOfRows;
		MazeDimesionsStruct.noOfCols = noOfCols;
		MazeDimesionsStruct.mazeWindowHeight = ((float)Exe_WindowHeight / 6.0f) * 5;
		MazeDimesionsStruct.mazeWindowWidth = (float)Exe_WindowWidth/2.0f;
		MazeDimesionsStruct.cellHeight = MazeDimesionsStruct.mazeWindowHeight / noOfRows;
		MazeDimesionsStruct.cellWidth = MazeDimesionsStruct.mazeWindowWidth / noOfCols;
		MazeDimesionsStruct.MazeWindowStart_X = Exe_WindowWidth / 2.0f / -2;
		MazeDimesionsStruct.MazeWindowStart_Y = (AEGetWindowHeight() / 6.0f * 5 / -2);

		return MazeDimesionsStruct;
	}


	void MAZE_CreateMESH_MazeWindow(AEGfxVertexList* &MazeWindow_Var, MazeDimensions MazeDimesionsStruct,int colour_HEXA)
	{
		AEGfxMeshStart();
		// This shape has 5 vertices
		AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(MazeDimesionsStruct.mazeWindowWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(MazeDimesionsStruct.mazeWindowWidth, MazeDimesionsStruct.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(0.0f, MazeDimesionsStruct.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
		MazeWindow_Var = AEGfxMeshEnd();
	}

	void MAZE_CreateMESH_CellOutline(AEGfxVertexList*& CellOutlineMesh_Var, MazeDimensions MazeDimesionsStruct, int colour_HEXA)
	{
		AEGfxMeshStart();
		AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(MazeDimesionsStruct.cellWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(MazeDimesionsStruct.cellWidth, MazeDimesionsStruct.cellHeight, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(0.0f, MazeDimesionsStruct.cellHeight, colour_HEXA, 0.0f, 0.0f);
		AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
		CellOutlineMesh_Var = AEGfxMeshEnd();
	}

	void MAZE_CreateSolidCell(AEGfxVertexList*& SolidCellMesh_Var, MazeDimensions MazeDimesionsStruct, int colour_HEXA)
	{
		AEGfxMeshStart();
		AEGfxTriAdd(
			0, 0, colour_HEXA, 0.0f, 1.0f,
			0, MazeDimesionsStruct.cellHeight, colour_HEXA, 1.0f, 1.0f,
			MazeDimesionsStruct.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
		AEGfxTriAdd(
			0, MazeDimesionsStruct.cellHeight, colour_HEXA, 1.0f, 1.0f,
			MazeDimesionsStruct.cellWidth, MazeDimesionsStruct.cellHeight, colour_HEXA, 1.0f, 0.0f,
			MazeDimesionsStruct.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
		SolidCellMesh_Var = AEGfxMeshEnd();
	}
