#include "pch.hpp"

/**************************************************
*		GLOBAL DEFINITIONS
***************************************************/
AEGfxTexture* ducktex;
AEGfxTexture* duckdrooltex;

extern sys systemsettings;

static float win_w;
static float win_h;

int RGBcounter = 16384000, flagg = 1;
int texcounter{ 0 };
float posX{ -340.0f }, posY{ -70.0f };
int choice{ 0 };
static s32 x, y;



/**************************************************
*		STRUCT / CLASS DEFINITIONS
***************************************************/

struct GameObjInst {
	AEGfxVertexList* pMesh;
	AEGfxTexture*	pTexture;
	float			scale;
	AEVec2			posCurr;
	AEMtx33			transform;
};

GameObjInst ducklogostruct;
GameObjInst selectionstruct;
GameObjInst gamelogostruct;



void Menu_Load() {

	AEGfxSetBackgroundColor(0.0f, 0.1f, 0.2f);

	gamelogostruct.pTexture = AEGfxTextureLoad("ducktitle.png");
	AE_ASSERT_MESG(gamelogostruct.pTexture, "Failed to create gamelogotexture!\n");

	ducktex = AEGfxTextureLoad("duck.png");
	AE_ASSERT_MESG(ducktex, "Failed to create duck texture!\n");

	duckdrooltex = AEGfxTextureLoad("duckdrool.png");
	AE_ASSERT_MESG(duckdrooltex, "Failed to create duckdrool texture!\n");


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

	gamelogostruct.pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(gamelogostruct.pMesh, "Failed to create gamelogo!\n");


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

	ducklogostruct.pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(ducklogostruct.pMesh, "Failed to create gamelogo!\n");

}

void Menu_Init() {

}

	static int X, Y;
void Menu_Update() {

		//AEInputGetCursorPosition(&X, &Y);						// for debugging
		//std::cout << "x: " << X << " y: " << Y << std::endl;

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		next = GS_QUIT;
	}

	// FOR TOGGLE FULLSCREEN
	if (AEInputCheckTriggered(AEVK_F11)) {
		if (systemsettings.fullscreen == 0) {
			systemsettings.fullscreen = 1;
			AEToogleFullScreen(systemsettings.fullscreen);
		}

		else if (systemsettings.fullscreen == 1){
			systemsettings.fullscreen = 0;
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}

	RGBcounter >= 16449436 ? flagg = 0 : flagg = flagg;
	RGBcounter <= 16319434 ? flagg = 1 : flagg = flagg;
	flagg == 1 ? RGBcounter += 150 : RGBcounter -= 150;


	if (selectionstruct.pMesh != nullptr) {
		AEGfxMeshFree(selectionstruct.pMesh);
		selectionstruct.pMesh = nullptr;
	}

	AEGfxMeshStart();
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	AEGfxVertexAdd(150.0f, -25.0f, RGBcounter, 1.0f, 1.0f);
	AEGfxVertexAdd(150.0f, 25.0f, RGBcounter, 0.0f, 0.0f);				// SELECTION GRID
	AEGfxVertexAdd(50.0f, 25.0f, RGBcounter, 1.0f, 0.0f);
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	selectionstruct.pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(selectionstruct.pMesh, "failed to create Selection object");

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

	if (AEInputCheckTriggered(AEVK_S)) {
			posX =  195.0f;
			posY = -250.0f;
			choice = 4;
	}

	if (AEInputCheckTriggered(AEVK_W)) {
			posX = -340.0f;
			posY = -70.0f;
			choice = 0;
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
		case 4: 
			systemsettings.fullscreen == 0 ? systemsettings.fullscreen = 1 : systemsettings.fullscreen = 0;
			AEToogleFullScreen(systemsettings.fullscreen);
			break;

		}
	}


	// for mouse input
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		// if cursor is within windowedmode box
		if (x >= 660 && x <= 720 && y >= 543 && y <= 555) {
			systemsettings.fullscreen == 0 ? systemsettings.fullscreen = 1 : systemsettings.fullscreen = 0;
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}
}

void Menu_Draw() {

	char strBuffer[35];
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

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



	if (systemsettings.fullscreen == 0) {
		sprintf_s(strBuffer, "Windowed");
		AEGfxPrint(fontId, strBuffer, 0.65f, -0.85f, 1.14f, 0.1f, 0.7f, 0.6f);
		if (x >= 660 && x <= 720 && y >= 543 && y <= 555) {
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			AEGfxSetPosition(195.0f, -250.0f);
			AEGfxMeshDraw(selectionstruct.pMesh, AE_GFX_MDM_LINES_STRIP);
		} 
	}

	if (systemsettings.fullscreen == 1) {
		sprintf_s(strBuffer, "Full Screen");
		AEGfxPrint(fontId, strBuffer, 0.65f, -0.85f, 1.07f, 0.1f, 0.7f, 0.6f);
		if (x >= 660 && x <= 720 && y >= 543 && y <= 555) {
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			AEGfxSetPosition(195.0f, -250.0f);
			AEGfxMeshDraw(selectionstruct.pMesh, AE_GFX_MDM_LINES_STRIP);
		} 
	}
	
	AEInputGetCursorPosition(&x, &y);
	
	// Selection grid
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(posX, posY);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(selectionstruct.pMesh, AE_GFX_MDM_LINES_STRIP);

	// texture
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 150.0f);
	AEGfxTextureSet(gamelogostruct.pTexture, 0.0f, 0.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(gamelogostruct.pMesh, AE_GFX_MDM_TRIANGLES);


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
	AEGfxMeshDraw(ducklogostruct.pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetPosition(-250.0f, 150.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(ducklogostruct.pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void Menu_Free() {

	if (selectionstruct.pMesh != nullptr) {
		AEGfxMeshFree(selectionstruct.pMesh);
		selectionstruct.pMesh = nullptr;
	}

	if (ducklogostruct.pMesh != nullptr) {
		AEGfxMeshFree(ducklogostruct.pMesh);
		ducklogostruct.pMesh = nullptr;
	}

	if (gamelogostruct.pMesh != nullptr) {
		AEGfxMeshFree(gamelogostruct.pMesh);
		gamelogostruct.pMesh = nullptr;
	}
}

void Menu_Unload() {

	AEGfxTextureUnload(gamelogostruct.pTexture);
	AEGfxTextureUnload(ducktex);
	AEGfxTextureUnload(duckdrooltex);

}
