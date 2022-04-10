/**************************************************************************
 * 	File name	:	gameover.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Richmond Choo Tze Yong	(PRIMARY AUTHOR - 90%)
 *					Louis Mineo				(SECONDARY AUTHOR - 5%)
 *					Hu Jun Ning				(SECONDARY AUTHOR - 5%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

AEGfxVertexList* gamemesh = 0;
AEGfxTexture* gameovertex;
extern int level_iter;

/**************************************************************
*	load function for gameover state
***************************************************************/
void GameOver_Load() {

	AEGfxSetBackgroundColor(0.0f, 0.1f, 0.2f);

	gameovertex = AEGfxTextureLoad("Images/gameover.png");
	AE_ASSERT_MESG(gameovertex, "Failed to create gameover texture!\n");


	AEGfxMeshStart();

	AEGfxTriAdd(
		-(float)AEGetWindowWidth()/2, (float)AEGetWindowHeight()/2, 0xFFFF0000, 0.0f, 0.0f,
		-(float)AEGetWindowWidth()/2, -(float)AEGetWindowHeight()/2, 0xFFFF0000, 0.0f, 1.0f,
		(float)AEGetWindowWidth()/2, (float)AEGetWindowHeight()/2, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		(float)AEGetWindowWidth()/2, (float)AEGetWindowHeight()/2, 0xFFFF0000, 1.0f, 0.0f,
		-(float)AEGetWindowWidth()/2, -(float)AEGetWindowHeight()/2, 0xFFFF0000, 0.0f, 1.0f,
		(float)AEGetWindowWidth()/2, -(float)AEGetWindowHeight()/2, 0xFFFFFFFF, 1.0f, 1.0f);

	gamemesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(gamemesh, "Failed to create gamelogo!\n");
}

/**************************************************************
*	init function for gameover state
***************************************************************/
void GameOver_Init() {
	Audio_Init();
	stop_Audio();
	lose_screen_background_Audio();
	player_initialise();			// reinitialises the player stats
	enemy_initialise();				// reinitialises the enemy stats
}


/**************************************************************
*	update function for gameover state
***************************************************************/
void GameOver_Update() {
	Audio_Update();

	if (AEInputCheckTriggered(AEVK_R)) {
		// QUESTION: is there a maze restart?
		maze_init_flag = 0;
		level_iter = 0;
		next = MAZE;
	}

	if (AEInputCheckTriggered(AEVK_Q)) {
		next = MENU;
		maze_init_flag = 0;
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}

}


/**************************************************************
*	draw function for gameover state
***************************************************************/
void GameOver_Draw() {

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxTextureSet(gameovertex, 0.0f, 0.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(gamemesh, AE_GFX_MDM_TRIANGLES);


	char strbuffer[100];
	AEGfxSetBlendMode(AE_GFX_BM_BLEND); 
	memset(strbuffer, 0, 100 * sizeof(char));		// sets all values to 0

	sprintf_s(strbuffer, "HOTKEYS");
	AEGfxPrint(fontId, strbuffer, -0.1f, -0.4f, 1.21f, 0.6f, 0.4f, 0.2f);

	sprintf_s(strbuffer, "Press Q: Go back to main menu");
	AEGfxPrint(fontId, strbuffer, -0.25f, -0.5f, 1.14f, 0.2f, 0.7f, 0.6f);

	sprintf_s(strbuffer, "Press R: Restart the game");
	AEGfxPrint(fontId, strbuffer, -0.25f, -0.6f, 1.14f, 0.2f, 0.7f, 0.6f);

	sprintf_s(strbuffer, "Press ESC: Quit the game");
	AEGfxPrint(fontId, strbuffer, -0.25f, -0.7f, 1.14f, 0.2f, 0.7f, 0.6f);
	
}

/**************************************************************
*	free function for gameover state
***************************************************************/
void GameOver_Free() {

	if (gamemesh != nullptr) {
		AEGfxMeshFree(gamemesh);
		gamemesh = nullptr;
	}

}


/**************************************************************
*	unload function for gameover state
***************************************************************/
void GameOver_Unload() {

	AEGfxTextureUnload(gameovertex);
}