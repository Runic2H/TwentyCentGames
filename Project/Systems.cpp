#include "pch.hpp"


/********************************************************************
			GLOBAL DEFINITIONS
*********************************************************************/
sys systemsettings;			
player_statsheet* playerstats;
enemy_statsheet* enemystats;
GameObjInst* ParticleInstList;
inv* playerinventory;
item* menubutton;
item* exitbutton;
item* resumebutton;
item* pausebackground;
item* yesbutton;
item* nobutton;



/********************************************************************
			SYSTEM LEVEL FUNCTION DEFINITIONS
*********************************************************************/
GameObjInst* particleInstCreate(float scale) {
	
	AEVec2 zero;
	AEVec2Zero(&zero);

	for (unsigned int i{ 0 }; i < 150; ++i) {
		GameObjInst* pInst = ParticleInstList + i;

		if (pInst->flag == 0) {
			pInst->pObject->pMesh = menubutton->pMesh;	//hijacking menubutton's mesh
			pInst->flag = 1;
			pInst->PosCurr.x = playerstats->positionX;
			pInst->PosCurr.y = playerstats->positionY;
			pInst->dirCurr = AERandFloat() * 20;
			pInst->velCurr.x = AERandFloat() * 30;
			pInst->velCurr.y = AERandFloat() * 30;
			pInst->pObject->itemcounter = 1.0f;
			AEMtx33 scaled, rotat;
			AEMtx33Scale(&scaled, scale, scale);
			AEMtx33Rot(&rotat, pInst->dirCurr);
			AEMtx33Concat(&pInst->pObject->transform, &rotat, &scaled);

			return pInst;
		}
	}
	
	return 0;
}

void particleInstDestroy(GameObjInst* pInst) {

	if (pInst->flag == 0) {
		return;
	}

	pInst->flag = 0;
}

void initialise_pausemenu() {

	menubutton = new item;
	exitbutton = new item;
	resumebutton = new item;
	pausebackground = new item;
	yesbutton = new item;
	nobutton = new item;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pausebackground->pMesh
		= menubutton->pMesh
		= exitbutton->pMesh
		= resumebutton->pMesh
		= yesbutton->pMesh
		= nobutton->pMesh
		= AEGfxMeshEnd();
	AE_ASSERT_MESG(menubutton->pMesh, "Failed to create pause meshes!!\n");


	menubutton->pTexture = AEGfxTextureLoad("Images/mainmenubutton.png");
	resumebutton->pTexture = AEGfxTextureLoad("Images/resumebutton.png");
	exitbutton->pTexture = AEGfxTextureLoad("Images/exitbutton.png");
	yesbutton->pTexture = AEGfxTextureLoad("Images/exitbutton.png");
	nobutton->pTexture = AEGfxTextureLoad("Images/resumebutton.png");
}

void LogicExit_Confirmation() {
	
	yesbutton->itemcounter = nobutton->itemcounter = 0.5f;
	AEMtx33 scale, rot, trans, buffer;

	AEInputGetCursorPosition(&cursorx, &cursory);
	//std::cout << "x: " << cursorx << "  y: " << cursory << std::endl;

	AEMtx33Scale(&scale, 150.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	
	AEMtx33Trans(&trans, 100.0f, -120.0f);
	AEMtx33Concat(&yesbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, -100.0f, -120.0f);
	AEMtx33Concat(&nobutton->transform, &trans, &buffer);

	if (cursorx >= 226 && cursorx <= 374 && cursory >= 396 && cursory <= 443) {
		nobutton->itemcounter = 1.0f;
	}

	if (cursorx >= 428 && cursorx <= 575 && cursory >= 396 && cursory <= 443) {
		yesbutton->itemcounter = 1.0f;
	}

		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			if (cursorx >= 226 && cursorx <= 374 && cursory >= 396 && cursory <= 443) {
				systemsettings.paused = 0;
				systemsettings.exit_confirmation = 0;
			}

			if (cursorx >= 428 && cursorx <= 575 && cursory >= 396 && cursory <= 443) {
				next = GS_QUIT;
			}
		}

		if (AEInputCheckTriggered(AEVK_ESCAPE)) {
			systemsettings.paused = 0;
			systemsettings.exit_confirmation = 0;
		}
}

void RenderExit_Confirmation() {

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxSetTransform(pausebackground->transform.m);
	AEGfxSetTransparency(0.70f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(pausebackground->pMesh, AE_GFX_MDM_TRIANGLES);


	AEGfxSetTransform(yesbutton->transform.m);
	AEGfxSetTransparency(yesbutton->itemcounter);
	AEGfxTextureSet(yesbutton->pTexture, 0, 0);
	AEGfxMeshDraw(yesbutton->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(nobutton->transform.m);
	AEGfxSetTransparency(nobutton->itemcounter);
	AEGfxTextureSet(nobutton->pTexture, 0, 0);
	AEGfxMeshDraw(nobutton->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);

	char strBuffer[50];

	sprintf_s(strBuffer, "Confirm Exit?");
	AEGfxPrint(fontLarge, strBuffer, -0.19f, 0.07f, 0.35f, 0.7f, 0.6f, 0.6f);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void logicpausemenu() {

	if (AEInputCheckTriggered(AEVK_Q)) {
		next = GS_QUIT;
	}

	menubutton->itemcounter = resumebutton->itemcounter = exitbutton->itemcounter = 0.5f;
	AEMtx33 scale, rot, trans, buffer;

	AEInputGetCursorPosition(&cursorx, &cursory);

	AEMtx33Scale(&scale, 150.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, -250.0f, -100.0f);
	AEMtx33Concat(&menubutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, -100.0f);
	AEMtx33Concat(&resumebutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 250.0f, -100.0f);
	AEMtx33Concat(&exitbutton->transform, &trans, &buffer);

	AEMtx33Scale(&scale, 1000.0f, 1000.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&pausebackground->transform, &trans, &buffer);


	if (cursorx >= 76 && cursorx <= 224 && cursory >= 375 && cursory <= 420) {
		menubutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			systemsettings.paused = 0;
			player_initialise();
			enemy_initialise();
			next = MENU;
		}
	}

	if (cursorx >= 326 && cursorx <= 474 && cursory >= 375 && cursory <= 420) {
		resumebutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			systemsettings.paused = 0;
		}
	}

	if (cursorx >= 577 && cursorx <= 726 && cursory >= 375 && cursory <= 420) {
		exitbutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			systemsettings.paused = 0;
			systemsettings.exit_confirmation = 1;
			//next = GS_QUIT;
		}
	}

	if (AEInputCheckTriggered(AEVK_F11)) {
		systemsettings.fullscreen == 1 ? systemsettings.fullscreen = 0 : systemsettings.fullscreen = 1;
		AEToogleFullScreen(systemsettings.fullscreen);
	}
}

void renderpausemenu() {

	// draw my buttons and meshes
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);


	AEGfxSetTransform(pausebackground->transform.m);
	AEGfxSetTransparency(0.70f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(pausebackground->pMesh, AE_GFX_MDM_TRIANGLES);
	
	AEGfxSetTransform(menubutton->transform.m);
	AEGfxSetTransparency(menubutton->itemcounter);
	AEGfxTextureSet(menubutton->pTexture, 0, 0);
	AEGfxMeshDraw(menubutton->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(resumebutton->transform.m);
	AEGfxSetTransparency(resumebutton->itemcounter);
	AEGfxTextureSet(resumebutton->pTexture, 0, 0);
	AEGfxMeshDraw(resumebutton->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(exitbutton->transform.m);
	AEGfxSetTransparency(exitbutton->itemcounter);
	AEGfxTextureSet(exitbutton->pTexture, 0, 0);
	AEGfxMeshDraw(exitbutton->pMesh, AE_GFX_MDM_TRIANGLES);

	char strBuffer[35];

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);

	sprintf_s(strBuffer, "PAUSED");
	AEGfxPrint(fontId, strBuffer, -0.12f, 0.35f, 2.0f, 1.0f, 0.0f, 0.0f);

	sprintf_s(strBuffer, "Press F11 to toggle fullscreen!");
	AEGfxPrint(fontId, strBuffer, -0.23f, 0.3f, 1.14f, 0.5f, 0.5f, 0.5f);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void unloadpausemenu() {
	
	if (menubutton->pMesh != nullptr) {
		AEGfxMeshFree(menubutton->pMesh);			// 1 MESH FREES ALL 3 MESHES
		menubutton->pMesh = nullptr;
	}
}

void player_initialise() {

/******************************************************************
*		PLAYER STRUCT DEFINITION
******************************************************************/

	std::string str;
	std::ifstream inFile;
	inFile.open("..\\Bin\\GameData\\PlayerData.txt");

	inFile >> str >> playerstats->PlayerLevel;
	inFile >> str >> playerstats->PlayerXP;
	inFile >> str >> playerstats->health;
	inFile >> str >> playerstats->maxhealth;
	inFile >> str >> playerstats->positionID;
	inFile >> str >> playerstats->SAFEGRID;
	inFile >> str >> playerstats->damage;
	inFile >> str >> playerstats->staminaCD;
	inFile >> str >> playerstats->staminacount;
	inFile >> str >> playerstats->staminamax;
	inFile >> str >> playerstats->staminaX;
	inFile >> str >> playerstats->is_dmgtaken;
	inFile >> str >> playerstats->is_attacking;
	inFile >> str >> playerstats->positionX;
	inFile >> str >> playerstats->positionY;
	inFile >> str >> playerstats->movementdt;
	inFile >> str >> playerstats->status;
	inFile >> str >> playerstats->statuscounter;
	inFile >> str >> playerstats->debuffcounter;
	playerstats->resetCD = playerstats->staminaCD;		// Reset Cooldown for attack and movement
	playerstats->PlayerXPMax = 100 + (25 * playerstats->PlayerLevel);
	inFile.close();
}


void enemy_initialise() {

/******************************************************************
*		ENEMY STRUCT DEFINITION
******************************************************************/

	std::string str;
	std::ifstream inFile;
	inFile.open("..\\Bin\\GameData\\EnemyData.txt");

	inFile >> str >> enemystats->EnemyType;
	inFile >> str >> enemystats->EnemyState;
	inFile >> str >> enemystats->positionX;
	inFile >> str >> enemystats->positionY;
	inFile >> str >> enemystats->is_attacking;
	inFile >> str >> enemystats->AttackCD;
	inFile >> str >> enemystats->DamageCD;
	
	enemystats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack

	inFile.close();
}


void inventory_initialise() {
	playerinventory->defencepotion.itemcounter = 0.0f;
	playerinventory->healthpotion.itemcounter = 0.0f;
	playerinventory->staminapotion.itemcounter = 0.0f;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		 0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		 0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		  playerinventory->defencepotion.pMesh
		= playerinventory->healthpotion.pMesh
		= playerinventory->staminapotion.pMesh
		= AEGfxMeshEnd();
	AE_ASSERT_MESG(playerinventory->defencepotion.pMesh, "cannot create inventorymesh");

	playerinventory->defencepotion.pTexture = AEGfxTextureLoad("Images/defencepotion.png");
	AE_ASSERT_MESG(playerinventory->defencepotion.pTexture, "cant create defencepotion texture\n");

	playerinventory->healthpotion.pTexture = AEGfxTextureLoad("Images/healthpotion.png");
	AE_ASSERT_MESG(playerinventory->healthpotion.pTexture, "cant create healthpotion texture\n");

	playerinventory->staminapotion.pTexture = AEGfxTextureLoad("Images/staminapotioninv.png");
	AE_ASSERT_MESG(playerinventory->staminapotion.pTexture, "cant create staminapotion texture\n");


	// transformation
	AEMtx33 scale, rot, buffer, trans;
	AEMtx33Scale(&scale, 42.0f, 42.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	
	AEMtx33Trans(&trans, -75.0f, -184.0f);
	AEMtx33Concat(&playerinventory->defencepotion.transform, &trans, &buffer);

	AEMtx33Trans(&trans, -5.0f, -184.0f);
	AEMtx33Concat(&playerinventory->healthpotion.transform, & trans, & buffer);

	AEMtx33Trans(&trans,  65.0f, -184.0f);
	AEMtx33Concat(&playerinventory->staminapotion.transform, &trans, &buffer);

}



void System_Initialise() {

/******************************************************************
*		FONTS AND SYSTEM SETTINGS
******************************************************************/
	ParticleInstList = (GameObjInst*)calloc(150, sizeof(GameObjInst));

	fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
	fontLarge = AEGfxCreateFont("Roboto-Regular.ttf", 67);
	systemsettings.fullscreen = 0;
	systemsettings.paused = 0;
	systemsettings.exit_confirmation = 0;

	for (int i{ 0 }; i < 150; ++i) {
		GameObjInst* pInst = ParticleInstList + i;
		pInst->pObject = new item;
	}
/******************************************************************
*		PLAYER INVENTORY CONSUMABLES
******************************************************************/
	playerinventory = new inv;
	inventory_initialise();

	playerstats = new player_statsheet;
	player_initialise();

	enemystats = new enemy_statsheet;
	enemy_initialise();

	initialise_pausemenu();
}


void System_Exit() {
	unloadpausemenu();
	AEGfxDestroyFont(fontId);
	AEGfxDestroyFont(fontLarge);
	AEGfxTextureUnload(playerinventory->defencepotion.pTexture);
	AEGfxTextureUnload(playerinventory->healthpotion.pTexture);
	AEGfxTextureUnload(playerinventory->staminapotion.pTexture);
	AEGfxTextureUnload(yesbutton->pTexture);
	AEGfxTextureUnload(nobutton->pTexture);
	AEGfxTextureUnload(menubutton->pTexture);
	AEGfxTextureUnload(exitbutton->pTexture);
	AEGfxTextureUnload(resumebutton->pTexture);
	AEGfxMeshFree(playerinventory->defencepotion.pMesh);
	delete playerstats;
	delete enemystats;
	delete playerinventory;
	delete menubutton;
	delete exitbutton;
	delete resumebutton;
	delete pausebackground;
	delete yesbutton;
	delete nobutton;

	for (int i{ 0 }; i < 150; ++i) {
		GameObjInst* pInst = ParticleInstList + i;
		delete pInst->pObject;
	}
	free(ParticleInstList);
}