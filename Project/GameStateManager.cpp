#include "pch.hpp"



int current = 0, previous = 0, next = 0;

FP fpLoad = nullptr, fpInitialize = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;
//function pointers

/*
	Initializes GSM, sets all the states to the same.
*/
void GSM_Initialize(int startingState)	//sets the previous, current and next indicators to the same val
{
	current = previous = next = startingState;
}

/*
	Updates GSM, contains the different states and their respective functions. (Levels, restart, quit)
*/
void GSM_Update()	//only runs once when switched
{
	switch (current)
	{
		case MENU:
			fpLoad = Menu_Load;
			fpInitialize = Menu_Init;
			fpUpdate = Menu_Update;
			fpDraw = Menu_Draw;
			fpFree = Menu_Free;
			fpUnload = Menu_Unload;
			break;

		case TUTORIAL:
			fpLoad = Tutorial_Load;
			fpInitialize = Tutorial_Init;
			fpUpdate = Tutorial_Update;
			fpDraw = Tutorial_Draw;
			fpFree = Tutorial_Free;
			fpUnload = Tutorial_Unload;
			break;

		case CREDITS:
			fpLoad = Credits_Load;
			fpInitialize = Credits_Init;
			fpUpdate = Credits_Update;
			fpDraw = Credits_Draw;
			fpFree = Credits_Free;
			fpUnload = Credits_Unload;
			break;

		case MAZE:
			fpLoad = Maze_Load;
			fpInitialize = Maze_Initialize;
			fpUpdate = Maze_Update;
			fpDraw = Maze_Draw;
			fpFree = Maze_Free;
			fpUnload = Maze_Unload;
			break;
      
	case COMBAT:
			fpLoad = Combat_Load;
			fpInitialize = Combat_Initialize;
			fpUpdate = Combat_Update;
			fpDraw = Combat_Draw;
			fpFree = Combat_Free;
			fpUnload = Combat_Unload;
			break;

	case GAMEOVER:
			fpLoad = GameOver_Load;
			fpInitialize = GameOver_Init;
			fpUpdate = GameOver_Update;
			fpDraw = GameOver_Draw;
			fpFree = GameOver_Free;
			fpUnload = GameOver_Unload;
			break;

	case LEVELUP:
			fpLoad = LevelUp_Load;
			fpInitialize = LevelUp_Init;
			fpUpdate = LevelUp_Update;
			fpDraw = LevelUp_Draw;
			fpFree = LevelUp_Free;
			fpUnload = LevelUp_Unload;
			break;

	case VICTORY:
			fpLoad = victory_load;
			fpInitialize = victory_init;
			fpUpdate = victory_update;
			fpDraw = victory_draw;
			fpFree = victory_free;
			fpUnload = victory_unload;
			break;

	case GS_RESTART:
		break;

	case GS_QUIT:
		break;

	default:
		break;
	}

}