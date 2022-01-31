// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Maze.h"



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

	MazeCells cells[noOfRows][noOfCols];
	MAZE_initMazeCell(cells);
	
	///TESTBENCH///
	//Maze_Struct* Maze = new Maze;
	///End of TESTBENCH///


	// Variable declaration end
	///////////////////////////


	//////////////////////////
	
	//End of Mesh Line
	///////////////////////////


	/////////////////
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1920, 1080, 1, 60, true, NULL);

	// Set Background
	AEGfxSetBackgroundColor(0.25f, 0.25f, 1.12f); 

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Init variables that will be used by the mesh drawing funcs
	MazeDimensions MAZE_DIMESIONS_STRUCT = MAZE_InitMazeDimension(AEGetWindowHeight(), AEGetWindowWidth(), noOfRows, noOfCols);

	MAZE_CreateMESH_MazeWindow(pMeshMazeWindow, MAZE_DIMESIONS_STRUCT, 0x8BC736);

	MAZE_CreateMESH_CellOutline(pMeshCellOutline, MAZE_DIMESIONS_STRUCT, 0xFFFFFFFF);	
	
	MAZE_CreateSolidCell(pMeshSolidSquare_WALL, MAZE_DIMESIONS_STRUCT, 0x000000);

	MAZE_CreateSolidCell(pMeshSolidSquare_PATH, MAZE_DIMESIONS_STRUCT, 0x808080);


		
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

		/*
		float MazeWindowStartX = AEGetWindowWidth() / 2 / -2;
		float MazeWindowStartY = (AEGetWindowHeight() / 6 * 5 / -2);
		*/
		
		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw
		MAZE_DrawMazeCellsandCellOutline(	pMeshSolidSquare_WALL,
										pMeshSolidSquare_PATH,
										pMeshCellOutline,
										MAZE_DIMESIONS_STRUCT,
										cells,
										AE_GFX_RM_COLOR	
									);


		MAZE_DrawMazeOutline(pMeshMazeWindow, MAZE_DIMESIONS_STRUCT, AE_GFX_MDM_LINES_STRIP); //AEGFX MeshDrawMode MDM != AEGFX RenderMode RM
		
		/*
		AEGfxSetPosition(MAZE_DIMESIONS_STRUCT.MazeWindowStart_X, MAZE_DIMESIONS_STRUCT.MazeWindowStart_Y);
		AEGfxMeshDraw(pMeshMazeWindow, AE_GFX_MDM_LINES_STRIP);
		*/
		

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
	AESysExit();
} 