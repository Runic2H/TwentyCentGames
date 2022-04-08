#include "pch.hpp"

/**************************************************
*		GLOBAL DEFINITIONS
***************************************************/
AEGfxTexture* ducktex;
AEGfxTexture* duckdrooltex;
//AEGfxTexture* digipenLogo; //matt

extern sys systemsettings;

static float win_w;
static float win_h;

int RGBcounter = 16384000, flagg = 1;
int texcounter{ 0 };
float posX{ -340.0f }, posY{ -70.0f };
int choice{ 0 };
s32 cursorx, cursory;
AEMtx33 scale, rot, trans, buffer;

bool isLogo{ false };
bool isTwentyLogo{ false };

/**************************************************
*		STRUCT / CLASS DEFINITIONS
***************************************************/

GameObjInst digipenLogostruct; 
GameObjInst TwentyCentGamesLogostruct; 
GameObjInst ducklogostruct;
GameObjInst selectionstruct;
GameObjInst gamelogostruct;
item		menustartbutton;
item		menututorialbutton;
item		menucreditsbutton;
item		menuexitbutton;
item		menuoptionbutton;


void Menu_Load() {

	AEToogleFullScreen(systemsettings.fullscreen);
	/*AEGfxSetBackgroundColor(0.0f, 0.1f, 0.2f);*/

	ducklogostruct.pObject = new item;
	selectionstruct.pObject = new item;
	gamelogostruct.pObject = new item;
	TwentyCentGamesLogostruct.pObject = new item;
	digipenLogostruct.pObject = new item;

	gamelogostruct.pObject->pTexture = AEGfxTextureLoad("Images/ducktitle.png");
	AE_ASSERT_MESG(gamelogostruct.pObject->pTexture, "Failed to create gamelogotexture!\n");

	ducktex = AEGfxTextureLoad("Images/duck.png");
	AE_ASSERT_MESG(ducktex, "Failed to create duck texture!\n");

	duckdrooltex = AEGfxTextureLoad("Images/duckdrool.png");
	AE_ASSERT_MESG(duckdrooltex, "Failed to create duckdrool texture!\n");

	digipenLogostruct.pObject->pTexture = AEGfxTextureLoad("Images/digipenLogo.png");
	AE_ASSERT_MESG(digipenLogostruct.pObject->pTexture, "Failed to create digipenLogo texture!\n");

	TwentyCentGamesLogostruct.pObject->pTexture = AEGfxTextureLoad("Images/TwentyCentGamesLogo.png");
	AE_ASSERT_MESG(TwentyCentGamesLogostruct.pObject->pTexture, "Failed to create TwentyCentGamesLogo texture!\n");


	
	//TwentyCentGamesLogo and digipenlogo mesh
	AEGfxMeshStart();

	AEGfxTriAdd(
		-400.0f, 250.0f, 0xFFFF0000, 0.0f, 0.0f,
		-400.0f, -250.0f, 0xFFFF0000, 0.0f, 1.0f,
		400.0f, 250.0f, 0xFFFFFFFF, 1.0f, 0.0f);

	AEGfxTriAdd(
		400.0f, 250.0f, 0xFFFF0000, 1.0f, 0.0f,
		-400.0f, -250.0f, 0xFFFF0000, 0.0f, 1.0f,
		400.0f, -250.0f, 0xFFFFFFFF, 1.0f, 1.0f);

	digipenLogostruct.pObject->pMesh
	= TwentyCentGamesLogostruct.pObject->pMesh
	= AEGfxMeshEnd();
	AE_ASSERT_MESG(TwentyCentGamesLogostruct.pObject->pMesh, "Failed to create TwentyCentGamesLogo!\n");

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

	gamelogostruct.pObject->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(gamelogostruct.pObject->pMesh, "Failed to create gamelogo!\n");


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

	ducklogostruct.pObject->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(ducklogostruct.pObject->pMesh, "Failed to create gamelogo!\n");


	//button mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	menustartbutton.pMesh
		= menututorialbutton.pMesh
		= menucreditsbutton.pMesh
		= menuexitbutton.pMesh
		= menuoptionbutton.pMesh
		= AEGfxMeshEnd();
	AE_ASSERT_MESG(menututorialbutton.pMesh, "Failed to create pause meshes!!\n");

	menustartbutton.pTexture = AEGfxTextureLoad("Images/startbutton.png");
	menututorialbutton.pTexture = AEGfxTextureLoad("Images/tutorialbutton.png");
	menuexitbutton.pTexture = AEGfxTextureLoad("Images/exitbutton.png");
	menucreditsbutton.pTexture = AEGfxTextureLoad("Images/creditsbutton.png");
	menuoptionbutton.pTexture = AEGfxTextureLoad("Images/optionbutton.png");

}

void Menu_Init() {
	Audio_Init();	//JN: new code
	menu_background_Audio();	//JN: new code

}

void Menu_Update() {
	Audio_Update();		//JN: new code
	increase_master_fader();		//JN: new code
	decrease_master_fader();		//JN: new code

	AEInputGetCursorPosition(&cursorx, &cursory);

	//std::cout << cursorx << "  " << cursory << std::endl;

	menustartbutton.itemcounter
		= menututorialbutton.itemcounter
		= menuexitbutton.itemcounter
		= menucreditsbutton.itemcounter
		= menuoptionbutton.itemcounter
		= 0.5f;

	RGBcounter >= 16449436 ? flagg = 0 : flagg = flagg;
	RGBcounter <= 16319434 ? flagg = 1 : flagg = flagg;
	flagg == 1 ? RGBcounter += 150 : RGBcounter -= 150;
	

	//if (selectionstruct.pMesh != nullptr) {
	//	AEGfxMeshFree(selectionstruct.pMesh);
	//	selectionstruct.pMesh = nullptr;
	//}

	AEGfxMeshStart();
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	AEGfxVertexAdd(150.0f, -25.0f, RGBcounter, 1.0f, 1.0f);
	AEGfxVertexAdd(150.0f, 25.0f, RGBcounter, 0.0f, 0.0f);				// for RGB
	AEGfxVertexAdd(50.0f, 25.0f, RGBcounter, 1.0f, 0.0f);
	AEGfxVertexAdd(50.0f, -25.0f, RGBcounter, 0.0f, 1.0f);
	selectionstruct.pObject->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(selectionstruct.pObject->pMesh, "failed to create Selection object");

	// to skip loading page
	if (AEInputCheckTriggered(AEVK_LCTRL)) {
		systemsettings.digipenTimer = 0;
		systemsettings.twentycentTimer = 0;
		isLogo = false;
		isTwentyLogo = false;
	}


	if (isLogo == false && isTwentyLogo == false){ 

		 if (systemsettings.options == 0 && systemsettings.exit_confirmation == 0){
			systemupdate();
		 }

		 else if (systemsettings.exit_confirmation == 1) {
			 LogicExit_Confirmation();
		 }

		else if (systemsettings.options == 1) {
		  logicoptionmenu();
		}
	}

	AEMtx33Scale(&scale, 105.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, -241.0f, -70.0f);
	AEMtx33Concat(&menustartbutton.transform, &trans, &buffer);

	AEMtx33Trans(&trans, -91.0f, -70.0f);
	AEMtx33Concat(&menututorialbutton.transform, &trans, &buffer);

	AEMtx33Trans(&trans,  59.0f, -70.0f);
	AEMtx33Concat(&menucreditsbutton.transform, &trans, &buffer);

	AEMtx33Trans(&trans,  209.0f, -70.0f);
	AEMtx33Concat(&menuexitbutton.transform, &trans, &buffer);

	AEMtx33Trans(&trans, 295.0f, -250.0f);
	AEMtx33Concat(&menuoptionbutton.transform, &trans, &buffer);

	systemsettings.digipenTimer -= DT;
	if (systemsettings.digipenTimer > 0)
	{
		isLogo = true;
	}
	else
	{
		isLogo = false;
		
		systemsettings.twentycentTimer -= DT;
		
		if (systemsettings.twentycentTimer > 0)
		{
			isTwentyLogo = true;
		}
		else
		{
			isTwentyLogo = false;
		}
	}

	// particles //

	AEInputGetCursorPosition(&cursorx, &cursory);
	particleInstCreate(AERandFloat() * 10, (f32)(cursorx-400), (f32)-(cursory-300), particlePLAYER);
	

	// particles update //
	for (int i{ 0 }; i < 150; ++i) {

		GameObjInst* pInst = ParticleInstList + i;

		if (0 == (pInst->flag))
			continue;

		pInst->pObject->itemcounter -= DT;
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

void Menu_Draw() {

	if (isLogo == false && isTwentyLogo == false)
	{
		if (systemsettings.options == 0 && systemsettings.exit_confirmation == 0)
		{
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(1, 1, 1, 1);
			AEGfxSetTransparency(1);

			AEGfxSetTransform(menustartbutton.transform.m);
			AEGfxSetTransparency(menustartbutton.itemcounter);
			AEGfxTextureSet(menustartbutton.pTexture, 0, 0);
			AEGfxMeshDraw(menustartbutton.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(menututorialbutton.transform.m);
			AEGfxSetTransparency(menututorialbutton.itemcounter);
			AEGfxTextureSet(menututorialbutton.pTexture, 0, 0);
			AEGfxMeshDraw(menututorialbutton.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(menucreditsbutton.transform.m);
			AEGfxSetTransparency(menucreditsbutton.itemcounter);
			AEGfxTextureSet(menucreditsbutton.pTexture, 0, 0);
			AEGfxMeshDraw(menucreditsbutton.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(menuexitbutton.transform.m);
			AEGfxSetTransparency(menuexitbutton.itemcounter);
			AEGfxTextureSet(menuexitbutton.pTexture, 0, 0);
			AEGfxMeshDraw(menuexitbutton.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(menuoptionbutton.transform.m);
			AEGfxSetTransparency(menuoptionbutton.itemcounter);
			AEGfxTextureSet(menuoptionbutton.pTexture, 0, 0);
			AEGfxMeshDraw(menuoptionbutton.pMesh, AE_GFX_MDM_TRIANGLES);

			char strBuffer[35];
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);

			sprintf_s(strBuffer, "Press [SPACEBAR] to select");
			AEGfxPrint(fontLarge, strBuffer, -0.25f, 0.08f, 0.25f, 1.0f, 0.5f, 0.5f);

			sprintf_s(strBuffer, "[WASD] for movement");
			AEGfxPrint(fontLarge, strBuffer, -0.20f, 0.01f, 0.25f, 1.0f, 0.5f, 0.5f);

			// Selection grid
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(posX, posY);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(selectionstruct.pObject->pMesh, AE_GFX_MDM_LINES_STRIP);

			// texture
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetPosition(0.0f, 150.0f);
			AEGfxTextureSet(gamelogostruct.pObject->pTexture, 0.0f, 0.0f);
			AEGfxSetTintColor(1, 1, 1, 1);
			AEGfxSetTransparency(1);
			AEGfxMeshDraw(gamelogostruct.pObject->pMesh, AE_GFX_MDM_TRIANGLES);

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
			AEGfxMeshDraw(ducklogostruct.pObject->pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetPosition(-250.0f, 150.0f);
			AEGfxSetTintColor(1, 1, 1, 1);
			AEGfxSetTransparency(1);
			AEGfxMeshDraw(ducklogostruct.pObject->pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}

		else if (systemsettings.exit_confirmation == 1) {
			RenderExit_Confirmation();
		}

		else {
			renderoptionmenu();
		}
	}
  
	else if(isLogo == true && isTwentyLogo == false)
	{
		//digipenLogo
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(-20.0f, 0.0f);
		AEGfxTextureSet(digipenLogostruct.pObject->pTexture, 0.0f, 0.0f);
		AEGfxSetTintColor(1, 1, 1, 1);
		AEGfxSetTransparency(systemsettings.digipenTimer);
		AEGfxMeshDraw(digipenLogostruct.pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	else if (isLogo == false && isTwentyLogo == true)
	{
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(-20.0f, 0.0f);
		AEGfxTextureSet(TwentyCentGamesLogostruct.pObject->pTexture, 0.0f, 0.0f);
		AEGfxSetTintColor(1, 1, 1, 1);
		AEGfxSetTransparency(systemsettings.twentycentTimer);
		AEGfxMeshDraw(TwentyCentGamesLogostruct.pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	AEGfxMeshFree(selectionstruct.pObject->pMesh);

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

void Menu_Free() {

	/*if (selectionstruct.pMesh != nullptr) {
		AEGfxMeshFree(selectionstruct.pMesh);
		selectionstruct.pMesh = nullptr;
	}*/

	if (ducklogostruct.pObject->pMesh != nullptr) {
		AEGfxMeshFree(ducklogostruct.pObject->pMesh);
		ducklogostruct.pObject->pMesh = nullptr;
	}

	if (gamelogostruct.pObject->pMesh != nullptr) {
		AEGfxMeshFree(gamelogostruct.pObject->pMesh);
		gamelogostruct.pObject->pMesh = nullptr;
	}

	if (menustartbutton.pMesh != nullptr) {
		AEGfxMeshFree(menustartbutton.pMesh);
		menustartbutton.pMesh = nullptr;
	}

	if (digipenLogostruct.pObject->pMesh != nullptr) {
		AEGfxMeshFree(digipenLogostruct.pObject->pMesh);
		digipenLogostruct.pObject->pMesh = nullptr;
	}
}

void Menu_Unload() {

	AEGfxTextureUnload(gamelogostruct.pObject->pTexture);
	AEGfxTextureUnload(ducktex);
	AEGfxTextureUnload(duckdrooltex);
	AEGfxTextureUnload(menustartbutton.pTexture);
	AEGfxTextureUnload(menucreditsbutton.pTexture);
	AEGfxTextureUnload(menututorialbutton.pTexture);
	AEGfxTextureUnload(menuexitbutton.pTexture);
	AEGfxTextureUnload(digipenLogostruct.pObject->pTexture);
	AEGfxTextureUnload(TwentyCentGamesLogostruct.pObject->pTexture);
	AEGfxTextureUnload(menuoptionbutton.pTexture);
	Audio_Unload();		//JN: new code

	delete gamelogostruct.pObject;
	delete selectionstruct.pObject;
	delete ducklogostruct.pObject;
	delete TwentyCentGamesLogostruct.pObject;
	delete digipenLogostruct.pObject;
}


void systemupdate() {

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		systemsettings.exit_confirmation = 1;
	}

	if (cursorx >= 106 && cursorx <= 210 && cursory >= 344 && cursory <= 391) {
		menustartbutton.itemcounter = 1.0f;
	}
	else if (cursorx >= 256 && cursorx <= 360 && cursory >= 344 && cursory <= 391) {
		menututorialbutton.itemcounter = 1.0f;
	}
	else if (cursorx >= 405 && cursorx <= 509 && cursory >= 344 && cursory <= 391) {
		menucreditsbutton.itemcounter = 1.0f;
	}
	else if (cursorx >= 557 && cursorx <= 661 && cursory >= 344 && cursory <= 391) {
		menuexitbutton.itemcounter = 1.0f;
	}
	else if (cursorx >= 643 && cursorx <= 747 && cursory >= 527 && cursory <= 574) {
		menuoptionbutton.itemcounter = 1.0f;
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		if (cursorx >= 106 && cursorx <= 210 && cursory >= 344 && cursory <= 391) {
			next = MAZE;
		}
		else if (cursorx >= 256 && cursorx <= 360 && cursory >= 344 && cursory <= 391) {
			next = TUTORIAL;
		}
		else if (cursorx >= 405 && cursorx <= 509 && cursory >= 344 && cursory <= 391) {
			next = CREDITS;
		}
		else if (cursorx >= 557 && cursorx <= 661 && cursory >= 344 && cursory <= 391) {
			systemsettings.exit_confirmation = 1;
		}
		else if (cursorx >= 643 && cursorx <= 747 && cursory >= 527 && cursory <= 574) {
			systemsettings.options == 0 ? systemsettings.options = 1 : systemsettings.options = 0;
		}
	}

	if (choice != 4)
	{
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
	}

	if (AEInputCheckTriggered(AEVK_S)) {
		posX = 195.0f;
		posY = -250.0f;
		choice = 4;
	}

	if (AEInputCheckTriggered(AEVK_W)) {
		posX = -340.0f;
		posY = -70.0f;
		choice = 0;
	}

	switch (choice) {
	case 0: menustartbutton.itemcounter = 1.0f;
		break;
	case 1: menututorialbutton.itemcounter = 1.0f;
		break;
	case 2: menucreditsbutton.itemcounter = 1.0f;
		break;
	case 3: menuexitbutton.itemcounter = 1.0f;
		break;
	case 4: menuoptionbutton.itemcounter = 1.0f;
		break;
	}

	if (AEInputCheckTriggered(AEVK_SPACE)) {

		switch (choice) {
		case 0: next = MAZE;
			break;
		case 1: next = TUTORIAL;
			break;
		case 2: next = CREDITS;
			break;
		case 3: systemsettings.exit_confirmation = 1;
			break;
		case 4:
			systemsettings.options == 0 ? systemsettings.options = 1 : systemsettings.options = 0;
			break;
		}
	}
}