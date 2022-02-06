#include "AEEngine.h"
#include "Maze.h"

#include <iostream>


int maze_iswall_isnotwall[noOfRows][noOfCols] =
{
		/*
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
		*/

		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
		1,0,1,1,1, 1,1,0,1,1, 1,0,1,0,1,
		1,0,0,0,1, 0,0,0,1,0, 0,0,1,0,1,
		1,1,1,1,1, 0,1,1,1,0, 1,1,1,0,1,
		1,0,0,0,1, 0,1,0,0,0, 1,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,1, 1,0,1,1,1,
		0,0,1,0,0, 0,1,0,1,0, 0,0,0,0,0,
		1,0,1,1,1, 1,1,0,1,1, 1,1,1,0,1,
		1,0,1,0,0, 0,1,0,0,0, 1,0,0,0,1,
		1,0,1,1,1, 0,1,1,1,0, 1,0,1,1,1,
		1,0,0,0,1, 0,0,0,0,0, 1,0,0,0,1,
		1,0,1,0,1, 1,1,0,1,1, 1,1,1,0,1,
		1,0,1,0,0, 0,1,0,0,0, 0,0,0,0,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1

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
			//Maze->grid[r][c].is_PlayerPos = 0;

		}
	}

	//Maze->grid[0][7].is_PlayerPos = 1;


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
			if (Maze->grid[r][c].is_wall == 1) // is wall
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


void MAZE_CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create main character!!");
}

void MAZE_DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

int MAZE_CharMoveCHECK_NEXT_POS(int UpDownLeftRight,Maze_Struct* Maze,int &Char_Pos_X, int &Char_Pos_Y)
{
	switch (UpDownLeftRight)//1 is up, 2 is left, 3 is down, 3 is right
	{
	case 1: // move up aka y+1 
		if (Maze->grid[Char_Pos_X][Char_Pos_Y+1].is_wall != 1 && (Char_Pos_Y +1)<Maze->specifications.noOfRows)
		{
			std::cout << "Can move up" << "\n";
			Char_Pos_Y++;
			return 1;
		}
		else
		{
			std::cout << "Cant move up to :" << Char_Pos_X<<"-"<< Char_Pos_Y+1
				<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y + 1].is_wall << "\n";
		}
		break;
	case 2: // move left aka x-1
		if (Maze->grid[Char_Pos_X-1][Char_Pos_Y].is_wall != 1 && (Char_Pos_X - 1) >= 0)
		{
			std::cout << "Can move left" << "\n";
			Char_Pos_X--;
			return 1;
		}
		else
		{
			std::cout << "Cant move left to :" << Char_Pos_X -1 << "-" << Char_Pos_Y 
				<< "because :" << Maze->grid[Char_Pos_X-1][Char_Pos_Y].is_wall << "\n";
		}
		break;
	case 3: // move down aka y-1
		if (Maze->grid[Char_Pos_X][Char_Pos_Y-1].is_wall != 1 && (Char_Pos_Y - 1) >= 0)
		{
			std::cout << "Can move down" << "\n";
			Char_Pos_Y--;
			return 1;
		}
		else
		{
			std::cout << "Cant move down to :" << Char_Pos_X << "-" << Char_Pos_Y-1 
				<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y - 1].is_wall<< "\n";
		}
		break;
	case 4: // move right aka x+1
		if (Maze->grid[Char_Pos_X+1][Char_Pos_Y].is_wall != 1 && (Char_Pos_X + 1) < Maze->specifications.noOfCols)
		{
			std::cout << "Can move right" << "\n";
			Char_Pos_X++;
			return 1;
		}
		else
		{
			std::cout << "Cant move right to :" << Char_Pos_X+1 << "-" << Char_Pos_Y 
				<< "because :"<< Maze->grid[Char_Pos_X + 1][Char_Pos_Y].is_wall <<"\n";
		}
		break;
	}

}
