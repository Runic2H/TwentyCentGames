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

		case GAMEOVER:
			fpLoad = GameOver_Load;
			fpInitialize = GameOver_Init;
			fpUpdate = GameOver_Update;
			fpDraw = GameOver_Draw;
			fpFree = GameOver_Free;
			fpUnload = GameOver_Unload;
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

		case GS_RESTART:
			break;

		case GS_QUIT:
			break;

		default:
			break;
		}

	}