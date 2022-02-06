// ---------------------------------------------------------------------------
// includes

#include "pch.hpp"



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


		// Variable declaration end
		///////////////////////////


		// Initialization
		/////////////////


		// Using custom window procedure
		AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	
		AESysSetWindowTitle("TwentyCentGames!");

		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

		GSM_Initialize(current);

		//System_Initialise();


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
				fpLoad;
			}


			fpInitialize();


			///////////////////
			// Game loop update and draw

			while (current == next) {

				// Informing the system about the loop's start
				AESysFrameStart();

				// Handling Input
				AEInputUpdate();
				
				Input_Handle();								//Handles the input from mouse and keyboard devices
				fpUpdate();									//Within GSM_Update, updates the gamestate according to the current value
				fpDraw();									//Within GSM_Update, draws the current gamestate according to the current value.


				AESysFrameEnd();
			// check if forcing the application to quit
			if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
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
		System_Exit();
		AESysExit();
	}