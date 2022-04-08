#include "pch.hpp"

item* coffeebutton;

void victory_load() {

	coffeebutton = new item;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	coffeebutton->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(coffeebutton->pMesh, "cannot create coffeebutton mesh!");


	coffeebutton->pTexture = AEGfxTextureLoad("Images/coffeemug.png");
	AE_ASSERT_MESG(coffeebutton->pTexture, "cannot create coffeebutton texture!");
}

void victory_init() {
	stop_Audio();	//JN: new code
	win_screen_background_Audio();
}

void victory_update() {
	Audio_Update();
	increase_bgm_fader();	//JN: new code
	decrease_bgm_fader();	//JN: new code
	increase_sfx_fader();	//JN: new code
	decrease_sfx_fader();	//JN: new code
	mute_master_fader();	//JN: new code
	unmute_master_fader();	//JN: new code

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}

	coffeebutton->itemcounter = 0.5f;

	AEMtx33 scale, rot, trans, buffer;

	AEMtx33Scale(&scale, 300.0f, 300.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&coffeebutton->transform, &trans, &buffer);

	AEInputGetCursorPosition(&cursorx, &cursory);
	//std::cout << cursorx << " " << cursory << std::endl;

	if (cursorx >= 334 && cursorx <= 448 && cursory >= 201 && cursory <= 397) {
		coffeebutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			systemsettings.paused = 0;
			player_initialise();
			enemy_initialise();
			next = MENU;
		}
	}
}

void victory_draw() {
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);


	AEGfxSetTransform(coffeebutton->transform.m);
	AEGfxSetTransparency(coffeebutton->itemcounter);
	AEGfxTextureSet(coffeebutton->pTexture, 0, 0);
	AEGfxMeshDraw(coffeebutton->pMesh, AE_GFX_MDM_TRIANGLES);


	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	char strBuffer[100];
	sprintf_s(strBuffer, "CONGRATULATIONS!");
	AEGfxPrint(fontLarge, strBuffer, -0.6f, 0.8f, 0.8f, 0.9f, 0.21f, 0.21f);

	sprintf_s(strBuffer, "You have managed to escape the maze");
	AEGfxPrint(fontLarge, strBuffer, -0.2f, 0.65f, 0.3f, 0.5f, 0.21f, 0.21f);

	sprintf_s(strBuffer, "You can finally rest");
	AEGfxPrint(fontId, strBuffer, -0.12f, -0.5f, 1.63f, 0.2f, 0.5f, 0.5f);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void victory_free() {
	AEGfxMeshFree(coffeebutton->pMesh);
}

void victory_unload() {
	AEGfxTextureUnload(coffeebutton->pTexture);
	delete coffeebutton;
}