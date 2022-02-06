// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Maze.h"
#include "Movement_Logic.h"
#include <iostream>



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;

	AEGfxVertexList* pMeshCellOutline = 0;
	AEGfxVertexList* pMeshMazeWindow = 0;
	AEGfxVertexList* pMeshSolidSquare_PATH = 0;
	AEGfxVertexList* pMeshSolidSquare_WALL = 0;

	float MC_positionX;
	float MC_positionY;
	AEGfxVertexList* pMesh_MainCharacter = 0;
	int starting_Xposition = 7;
	int starting_Yposition = 0;



	// Variable declaration end
	///////////////////////////


	//////////////////////////

	//End of Mesh Line
	///////////////////////////


	/////////////////
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1280, 720, 1, 60, true, NULL);

	// Set Background
	AEGfxSetBackgroundColor(0.25f, 0.25f, 1.12f);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	// Initialization end
	/////////////////////




	Maze_Struct* Maze = CreateMaze(AEGetWindowHeight(), AEGetWindowWidth(), noOfRows, noOfCols);
	////////////////////////////////
	// Init variables that will be used by the mesh drawing funcs


	//MAZE_CreateMESH_MazeWindow(pMeshMazeWindow, MAZE_DIMESIONS_STRUCT, 0x8BC736);
	MAZE_CreateMESH_MazeWindow2(pMeshMazeWindow, Maze, 0xFF0000);

	//MAZE_CreateMESH_CellOutline(pMeshCellOutline, MAZE_DIMESIONS_STRUCT, 0xFFFFFFFF);	
	MAZE_CreateMESH_CellOutline2(pMeshCellOutline, Maze, 0xFFFFFFFF);

	//MAZE_CreateSolidCell(pMeshSolidSquare_WALL, MAZE_DIMESIONS_STRUCT, 0x000000);
	MAZE_CreateSolidCell2(pMeshSolidSquare_WALL, Maze, 0x000000);

	//MAZE_CreateSolidCell(pMeshSolidSquare_PATH, MAZE_DIMESIONS_STRUCT, 0x808080);
	MAZE_CreateSolidCell2(pMeshSolidSquare_PATH, Maze, 0x808080);

	MAZE_CreateMainCharacter(pMesh_MainCharacter, Maze->specifications.cellHeight, Maze->specifications.cellWidth);

	//code needs to be after creating the maze
	//MC_positionX = Maze->specifications.MazeWindowStart_X + (Maze->specifications.cellWidth / 2) + (7 * Maze->specifications.cellWidth);
	MC_positionX = Maze->specifications.MazeWindowStart_X + (Maze->specifications.cellWidth / 2) + (starting_Xposition *Maze->specifications.cellWidth);
	
	MC_positionY = Maze->specifications.MazeWindowStart_Y + (Maze->specifications.cellHeight / 2)+ (starting_Yposition * Maze->specifications.cellHeight); ;
	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)

	// Loading textures (images) end
	//////////////////////////////////

	//////////////////////////////////
	// Creating Fonts	

	// Creating Fonts end
	//////////////////////////////////



	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

		////not working
		//for (size_t i = 0; i < noOfCols; i++)
		//{
		//	for (size_t j = 0; j < noOfRows; j++)
		//	{
		//		if (Maze->grid[i][j].is_wall != 1)
		//		{
		//			if (AEInputCheckTriggered(AEVK_UP))
		//			{

		//				MC_positionY += Maze->specifications.cellHeight;
		//				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY << "\n";
		//			}
		//		}

		//	}
		//}

		//std::cout << Maze->grid[0][7].is_wall << "\n";

		// main character will move if these buttons are pressed
		if (AEInputCheckTriggered(AEVK_UP))
		{
			if (MAZE_CharMoveCHECK_NEXT_POS(1,Maze,starting_Xposition,starting_Yposition) == 1)
			{
				MC_positionY += Maze->specifications.cellHeight;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
			}
		}

		 if (AEInputCheckTriggered(AEVK_DOWN))
		{
			if (MAZE_CharMoveCHECK_NEXT_POS(3, Maze, starting_Xposition, starting_Yposition) == 1)
			{
				MC_positionY -= Maze->specifications.cellHeight;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
			}
		}


		 if (AEInputCheckTriggered(AEVK_LEFT))
		{
			if (MAZE_CharMoveCHECK_NEXT_POS(2, Maze, starting_Xposition, starting_Yposition) == 1)
			{

				MC_positionX -= Maze->specifications.cellWidth;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";

			}
		}

		 if (AEInputCheckTriggered(AEVK_RIGHT))
		{
			if (MAZE_CharMoveCHECK_NEXT_POS(4, Maze, starting_Xposition, starting_Yposition) == 1)
			{

				MC_positionX += Maze->specifications.cellWidth;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << starting_Xposition << "\t\t" << starting_Yposition << "\n";
			}
		}


		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw

		MAZE_DrawMazeCellsandCellOutline2(pMeshSolidSquare_WALL,
			pMeshSolidSquare_PATH,
			pMeshCellOutline,
			Maze,
			AE_GFX_RM_COLOR
		);



		MAZE_DrawMazeOutline2(pMeshMazeWindow, Maze, AE_GFX_MDM_LINES_STRIP); //AEGFX MeshDrawMode MDM != AEGFX RenderMode RM

		//Draw mc
		MAZE_DrawingMainCharacter(pMesh_MainCharacter, MC_positionX, MC_positionY);


		// Game loop draw end
		/////////////////////


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	AEGfxMeshFree(pMeshCellOutline);
	AEGfxMeshFree(pMeshMazeWindow);
	AEGfxMeshFree(pMeshSolidSquare_PATH);
	AEGfxMeshFree(pMeshSolidSquare_WALL);
	AEGfxMeshFree(pMesh_MainCharacter);


	delete(Maze);
	AESysExit();
}