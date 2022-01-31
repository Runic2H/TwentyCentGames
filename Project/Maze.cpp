#include "AEEngine.h"
#include "Maze.h"


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


Maze_Struct* CreateMaze(int Exe_WindowHeight, int Exe_WindowWidth, int noOfRows, int noOfCols)
{
	Maze_Struct* Maze = new Maze_Struct;


	//INITIALIZING THE DIMENSIONS STRUCT
	Maze->specifications.noOfRows = noOfRows;
	Maze->specifications.noOfCols = noOfCols;
	Maze->specifications.mazeWindowHeight = ((float)Exe_WindowHeight / 6.0f) * 5;
	Maze->specifications.mazeWindowWidth = (float)Exe_WindowWidth / 2.0f;
	Maze->specifications.cellHeight = Maze->specifications.mazeWindowHeight / noOfRows;
	Maze->specifications.cellWidth = Maze->specifications.mazeWindowWidth / noOfCols;
	Maze->specifications.MazeWindowStart_X = Exe_WindowWidth / 2.0f / -2;
	Maze->specifications.MazeWindowStart_Y = (Exe_WindowHeight / 6.0f * 5 / -2);

	// Init the grid cells
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{
			
			Maze->grid[r][c].is_wall = maze_iswall_isnotwall[r][c];

		}
	}


	return Maze;
}

void MAZE_CreateMESH_MazeWindow2(AEGfxVertexList*& MazeWindow_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	// This shape has 5 vertices
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	MazeWindow_Var = AEGfxMeshEnd();
}

void MAZE_CreateMESH_CellOutline2(AEGfxVertexList*& CellOutlineMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	CellOutlineMesh_Var = AEGfxMeshEnd();
}

void MAZE_CreateSolidCell2(AEGfxVertexList*& SolidCellMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, colour_HEXA, 0.0f, 1.0f,
		0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
	AEGfxTriAdd(
		0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 0.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
	SolidCellMesh_Var = AEGfxMeshEnd();
}


void MAZE_DrawMazeCellsandCellOutline2(AEGfxVertexList*& WALLCellMesh,
	AEGfxVertexList*& PATHCellMesh,
	AEGfxVertexList*& CellOutlineMesh,
	Maze_Struct* Maze,
	AEGfxRenderMode RenderMode)
{
	AEGfxSetRenderMode(RenderMode);
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{
			AEGfxSetPosition(
				(Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth)),
				(Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight))
			);
			if (Maze->grid[c][r].is_wall == 1) // is wall
			{
				AEGfxMeshDraw(WALLCellMesh, AE_GFX_MDM_TRIANGLES);
			}
			else
			{
				AEGfxMeshDraw(PATHCellMesh, AE_GFX_MDM_TRIANGLES);
			}

			AEGfxSetPosition(
				Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth),
				Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight)
			);
			AEGfxMeshDraw(CellOutlineMesh, AE_GFX_MDM_LINES_STRIP);

		}
	}
}

void MAZE_DrawMazeOutline2(AEGfxVertexList*& mazeOutlineMesh, Maze_Struct* Maze, AEGfxMeshDrawMode RenderMode)
{
	AEGfxSetPosition(Maze->specifications.MazeWindowStart_X, Maze->specifications.MazeWindowStart_Y);
	AEGfxMeshDraw(mazeOutlineMesh, RenderMode);
}
