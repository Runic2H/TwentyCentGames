#include "pch.hpp"

//	gameover.cpp

// float camX, camY;
AEGfxVertexList* gamemesh = 0;
AEGfxTexture* gameovertex;
extern int level_iter;

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

void GameOver_Init() {
	Audio_Init();
	stop_Audio();	//JN: new code
	lose_screen_background_Audio();
	player_initialise();			// reinitialises the player stats
	enemy_initialise();				// reinitialises the enemy stats
}

void GameOver_Update() {
	Audio_Update();
	increase_bgm_fader();	//JN: new code
	decrease_bgm_fader();	//JN: new code
	increase_sfx_fader();	//JN: new code
	decrease_sfx_fader();	//JN: new code
	mute_master_fader();	//JN: new code
	unmute_master_fader();	//JN: new code

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

	//AEGfxGetCamPosition(&camX, &camY);			// cam position for debugging
	//if (AEInputCheckCurr(AEVK_W))
	//	AEGfxSetCamPosition(camX, camY + 10);
	//else if (AEInputCheckCurr(AEVK_S))
	//	AEGfxSetCamPosition(camX, camY - 10);

	//AEGfxGetCamPosition(&camX, &camY);
	//if (AEInputCheckCurr(AEVK_A))
	//	AEGfxSetCamPosition(camX - 10, camY);
	//else if (AEInputCheckCurr(AEVK_D))
	//	AEGfxSetCamPosition(camX + 10, camY);
}

void GameOver_Draw() {

	float w_ht = (float)AEGetWindowHeight();
	float w_wd = (float)AEGetWindowWidth();

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

void GameOver_Free() {

	if (gamemesh != nullptr) {
		AEGfxMeshFree(gamemesh);
		gamemesh = nullptr;
	}

}

void GameOver_Unload() {

	AEGfxTextureUnload(gameovertex);
}