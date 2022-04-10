/**************************************************************************
 * 	File name	:	victoryscreen.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Richmond Choo Tze Yong	(PRIMARY AUTHOR - 100%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

item* coffeebutton;

/**************************************************************
*	load function for victory gamestate
***************************************************************/
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


/**************************************************************
*	init function for victory gamestate
***************************************************************/
void victory_init() {
	stop_Audio();
	win_screen_background_Audio();
}


/**************************************************************
*	update function for victory gamestate
***************************************************************/
void victory_update() {
	Audio_Update();

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

	if (cursorx >= 334 && cursorx <= 448 && cursory >= 201 && cursory <= 397) {
		coffeebutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			systemsettings.paused = 0;
			player_initialise();
			enemy_initialise();
			next = CREDITS;
		}
	}

	// 800 x
	// 600 y
	float particleX{}, particleY{};
	int count{};

	count = AERandFloat() * 10;

	if (count >= 0 && count <= 2) {
		particleX = AERandFloat() * 400;
		particleY = AERandFloat() * 300;
	}

	else if (count > 2 && count <= 5) {
		particleX = -(AERandFloat() * 400);
		particleY = AERandFloat() * 300;
	}

	else if (count > 5 && count <= 8) {
		particleX = AERandFloat() * 400;
		particleY = -(AERandFloat() * 300);
	}

	else if (count > 8 && count <= 10) {
		particleX = -(AERandFloat() * 400);
		particleY = -(AERandFloat() * 300);
	}

		for (int i{}; i < 50; ++i) {
			particleInstCreate(AERandFloat() * 10, particleX, particleY, particlePLAYER);
		}

	for (int i{ 0 }; i < 150; ++i) {

		GameObjInst* pInst = ParticleInstList + i;

		if (0 == (pInst->flag))
			continue;

		float dt = DT;
		pInst->pObject->itemcounter -= (dt * 0.7f);
		if (pInst->pObject->itemcounter <= 0) {
			particleInstDestroy(pInst);
		}

		AEMtx33 trans, rot, scale, mtxbuffer;
		AEVec2 buffer;

		// updating position from velocity //
		float g_dt = DT;
		AEVec2Scale(&buffer, &pInst->velCurr, g_dt);			// vel
		AEVec2Add(&pInst->PosCurr, &buffer, &pInst->PosCurr);	// pos'

		AEMtx33Scale(&scale, pInst->scale, pInst->scale);		// scale
		AEMtx33Rot(&rot, pInst->dirCurr);						// dir
		AEMtx33Concat(&mtxbuffer, &scale, &rot);				// scale x dir

		AEMtx33Trans(&trans, pInst->PosCurr.x, pInst->PosCurr.y);
		AEMtx33Concat(&pInst->pObject->transform, &trans, &mtxbuffer);
	}
}


/**************************************************************
*	draw function for victory gamestate
***************************************************************/
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
	AEGfxPrint(fontLarge, strBuffer, -0.42f, 0.65f, 0.3f, 0.5f, 0.21f, 0.21f);

	sprintf_s(strBuffer, "Click the coffee cup to have a break <3");
	AEGfxPrint(fontId, strBuffer, -0.4f, -0.5f, 1.63f, 0.2f, 0.5f, 0.5f);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);


	for (int i{ 0 }; i < 150; ++i) {
		GameObjInst* pInst = ParticleInstList + i;

		if (0 == (pInst->flag))
			continue;

		AEGfxSetTransform(pInst->pObject->transform.m);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(pInst->pObject->itemcounter);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (pInst->type == particleENEMY) {
			AEGfxSetTintColor(0.0f, 0.7f, 0.7f, 1.0f);
		}
		else if (pInst->type == particlePLAYER) {
			AEGfxSetTintColor(0.9f, 0.7f, 0.04f, 1.0f);
		}

		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}


/**************************************************************
*	free function for victory gamestate
***************************************************************/
void victory_free() {
	AEGfxMeshFree(coffeebutton->pMesh);
}


/**************************************************************
*	unload function for victory gamestate
***************************************************************/
void victory_unload() {
	AEGfxTextureUnload(coffeebutton->pTexture);
	delete coffeebutton;
}