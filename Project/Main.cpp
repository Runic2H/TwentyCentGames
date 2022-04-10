/**************************************************************************
 * 	File name	:	Main.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Elton Teo Zhe Wei		(PRIMARY CONTRIBUTOR - 20%)
 *					Louis Mineo				(PRIMARY CONTRIBUTOR - 20%)
 *					Richmond Choo Tze Yong	(PRIMARY CONTRIBUTOR - 20%)
 *					Hu Jun Ning				(PRIMARY CONTRIBUTOR - 20%)
 *					Matthew Cheung Jun Yin	(PRIMARY CONTRIBUTOR - 20%)
 *
 * All content � 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/



#include "pch.hpp"



// ---------------------------------------------------------------------------
// main


	int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow)
	{


		// Enable run-time memory check for debug builds //
		#if defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(1094);
		#endif

		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		///////////////////////
		// Variable declaration


		// Variable declaration end
		///////////////////////////


		// Initialization
		/////////////////


		// Using custom window procedure
		AESysInit(hInstance, SW_HIDE, 800, 600, 1, 60, true, NULL);
	
		AESysSetWindowTitle("TwentyCentGames!");

		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

		System_Initialise();

		GSM_Initialize(current);

		Audio_Init();
		

		// Game Loop
		while (current != GS_QUIT) {

		// reset the system modules
		AESysReset();

			if (current == GS_RESTART) {
				current = previous;
				next = previous;
			}
			else {
				GSM_Update();
				fpLoad();
			}


			fpInitialize();


			///////////////////
			// Game loop update and draw

			ShowWindow(AESysGetWindowHandle(), SW_SHOW);
			while (current == next) {

				
				AESysFrameStart();							// Informing the system about the loop's start
				AEInputUpdate();							// Handling Input
				Input_Handle();								//Handles the input from mouse and keyboard devices
				fpUpdate();									//Within GSM_Update, updates the gamestate according to the current value
				fpDraw();									//Within GSM_Update, draws the current gamestate according to the current value.
															// Press 2 to switch to combat gamestate, ESC to quit
				AESysFrameEnd();

			if (0 == AESysDoesWindowExist())	// check if forcing the application to quit
				next = GS_QUIT;

			}

			// Game loop update end
			///////////////////////

			fpFree();										//Within GSM_Update, frees the current gamestate according to the current value.

			

	// Informing the system about the loop's end
			
			if (next == GS_RESTART) {
				previous = current;
				current = next;
			}

			else {
				fpUnload();
				previous = current;
				current = next;
			}

		}


		// free the system
		Audio_Unload();
		System_Exit();
		AESysExit();
	}