#include "pch.hpp"


AEGfxVertexList* Selection = 0;
AEGfxVertexList* gamelogo = 0;
AEGfxVertexList* duck = 0;
AEGfxVertexList* duck1 = 0;
AEGfxTexture* gamelogotex;
AEGfxTexture* ducktex;
AEGfxTexture* duckdrooltex;

int RGBcounter = 16384000, flagg = 1;
int texcounter{ 0 };
float posX{ -340.0f }, posY{ -70.0f };
int choice{ 0 };

void Menu_Load() {

	AEGfxSetBackgroundColor(0.0f, 0.1f, 0.2f);

	gamelogotex = AEGfxTextureLoad("ducktitle.png");
	AE_ASSERT_MESG(gamelogotex, "Failed to create gamelogotexture!\n");

	ducktex = AEGfxTextureLoad("duck.png");
	AE_ASSERT_MESG(ducktex, "Failed to create duck texture!\n");

	duckdrooltex = AEGfxTextureLoad("duckdrool.png");
	AE_ASSERT_MESG(duckdrooltex, "Failed to create duckdrool texture!\n");
}

void Menu_Init() {

	// title mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-150.0f, 50.0f, 0xFFFF0000, 0.0f, 0.0f,
		-150.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		150.0f, 50.0f, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		150.0f, 50.0f, 0xFFFF0000, 1.0f, 0.0f,
		-150.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		150.0f, -50.0f, 0xFFFFFFFF, 1.0f, 1.0f);

	gamelogo = AEGfxMeshEnd();
	AE_ASSERT_MESG(gamelogo, "Failed to create gamelogo!\n");



	// duck mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-50.0f, 50.0f, 0xFFFF0000, 0.0f, 0.0f,
		-50.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		50.0f, 50.0f, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		50.0f, 50.0f, 0xFFFF0000, 1.0f, 0.0f,
		-50.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		50.0f, -50.0f, 0xFFFFFFFF, 1.0f, 1.0f);

	duck = AEGfxMeshEnd();
	AE_ASSERT_MESG(duck, "Failed to create gamelogo!\n");


}

void Menu_Update() {


	RGBcounter >= 16449436 ? flagg = 0 : flagg = flagg;
	RGBcounter <= 16319434 ? flagg = 1 : flagg = flagg;
	flagg == 1 ? RGBcounter += 150 : RGBcounter -= 150;


	if (Selection != nullptr) {
		AEGfxMeshFree(Selection);
		Selection = nullptr;
	}

	AEGfxMeshStart();
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	AEGfxVertexAdd(150.0f, -25.0f, RGBcounter, 1.0f, 1.0f);
	AEGfxVertexAdd(150.0f, 25.0f, RGBcounter, 0.0f, 0.0f);				// SELECTION GRID
	AEGfxVertexAdd(50.0f, 25.0f, RGBcounter, 1.0f, 0.0f);
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	Selection = AEGfxMeshEnd();
	AE_ASSERT_MESG(Selection, "failed to create Selection object");

	if (AEInputCheckTriggered(AEVK_D)) {
		if (!(posX >= 110.0f)) {
			posX += 150.0f;
			++choice;
		}
	}

	if (AEInputCheckTriggered(AEVK_A)) {
		if (!(posX <= -340.0f)) {
			posX -= 150.0f;
			--choice;
		}
	}

	if (AEInputCheckTriggered(AEVK_SPACE)) {

		switch (choice) {
		case 0: next = MAZE;
			break;
		case 1: next = TUTORIAL;
			break;
		case 2: next = CREDITS;
			break;
		case 3: next = GS_QUIT;
			break;
		}
	}
}

void Menu_Draw() {

	char strBuffer[35];
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	memset(strBuffer, 0, 35 * sizeof(char));		// sets all values to 0

	sprintf_s(strBuffer, "START GAME");				// stores the string into strBuffer
	AEGfxPrint(fontId, strBuffer, -0.70f, -0.25f, 1.14f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "TUTORIAL");				// stores the string into strBuffer
	AEGfxPrint(fontId, strBuffer, -0.30f, -0.25f, 1.14f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "CREDITS");				// stores the string into strBuffer
	AEGfxPrint(fontId, strBuffer, 0.08f, -0.25f, 1.14f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "EXIT GAME");				// stores the string into strBuffer
	AEGfxPrint(fontId, strBuffer, 0.43f, -0.25f, 1.14f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press SPACEBAR to select");
	AEGfxPrint(fontId, strBuffer, -0.2f, -0.08f, 1.14f, 1.0f, 0.5f, 0.5f);

	sprintf_s(strBuffer, "WASD for movement");
	AEGfxPrint(fontId, strBuffer, -0.16f, -0.01f, 1.14f, 1.0f, 0.5f, 0.5f);


	// Selection grid
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(posX, posY);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(Selection, AE_GFX_MDM_LINES_STRIP);

	// texture
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 150.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(gamelogotex, 0.0f, 0.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(gamelogo, AE_GFX_MDM_TRIANGLES);


	++texcounter;
	if (texcounter < 120) {
		AEGfxTextureSet(ducktex, 0.0f, 0.0f);
	}
	else if (texcounter < 240) {
		AEGfxTextureSet(duckdrooltex, 0.0f, 0.0f);
	}
	else {
		AEGfxTextureSet(ducktex, 0.0f, 0.0f);
		texcounter = 0;
	}
	AEGfxSetPosition(250.0f, 150.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(duck, AE_GFX_MDM_TRIANGLES);

	AEGfxSetPosition(-250.0f, 150.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(duck, AE_GFX_MDM_TRIANGLES);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void Menu_Free() {

	if (Selection != nullptr) {
		AEGfxMeshFree(Selection);
		Selection = nullptr;
	}

	if (duck != nullptr) {
		AEGfxMeshFree(duck);
		duck = nullptr;
	}

	if (gamelogo != nullptr) {
		AEGfxMeshFree(gamelogo);
	}
}

void Menu_Unload() {

	AEGfxTextureUnload(gamelogotex);
	AEGfxTextureUnload(ducktex);
	AEGfxTextureUnload(duckdrooltex);
}