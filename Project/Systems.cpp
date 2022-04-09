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
item* optionbutton;
item* mutebutton;
item* fullscreenbutton;
item* yesbutton;
item* nobutton;

/********************************************************************
			SYSTEM LEVEL FUNCTION DEFINITIONS
*********************************************************************/
GameObjInst* particleInstCreate(float scale, float posX, float posY, int type) {

	AEVec2 zero;
	AEVec2Zero(&zero);

	for (unsigned int i{ 0 }; i < 150; ++i) {
		GameObjInst* pInst = ParticleInstList + i;

		if (pInst->flag == 0) {
			pInst->pObject->pMesh = menubutton->pMesh;	//hijacking menubutton's mesh
			pInst->flag = 1;
			pInst->PosCurr.x = posX;
			pInst->PosCurr.y = posY;
			pInst->dirCurr = AERandFloat() * 20;
			pInst->pObject->itemcounter = 1.0f;
			pInst->scale = scale;
			pInst->type = type;

			int count = AERandFloat() * 10;

			if (count >= 0 && count <= 2) {
				pInst->velCurr.x = AERandFloat() * 300;
				pInst->velCurr.y = AERandFloat() * 300;
			}

			else if (count > 2 && count <= 4) {
				pInst->velCurr.x = AERandFloat() * 300;
				pInst->velCurr.y = -(AERandFloat() * 300);
			}

			else if (count > 4 && count <= 7) {
				pInst->velCurr.x = -(AERandFloat() * 300);
				pInst->velCurr.y = -(AERandFloat() * 300);
			}

			else {
				pInst->velCurr.x = -(AERandFloat() * 300);
				pInst->velCurr.y = (AERandFloat() * 300);
			}

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

void initialise_pausemenu() {

	menubutton = new item;
	exitbutton = new item;
	resumebutton = new item;
	pausebackground = new item;
	optionbutton = new item;
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
		= optionbutton->pMesh
		= yesbutton->pMesh
		= nobutton->pMesh
		= AEGfxMeshEnd();
	AE_ASSERT_MESG(menubutton->pMesh, "Failed to create pause meshes!!\n");


	menubutton->pTexture = AEGfxTextureLoad("Images/mainmenubutton.png");
	resumebutton->pTexture = AEGfxTextureLoad("Images/resumebutton.png");
	exitbutton->pTexture = AEGfxTextureLoad("Images/exitbutton.png");
	optionbutton->pTexture = AEGfxTextureLoad("Images/optionbutton.png");
	yesbutton->pTexture = AEGfxTextureLoad("Images/exitbutton.png");
	nobutton->pTexture = AEGfxTextureLoad("Images/resumebutton.png");
}

void initialise_optionmenu()
{
	mutebutton = new item;
	fullscreenbutton = new item;

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
		= mutebutton->pMesh
		= fullscreenbutton->pMesh
		= AEGfxMeshEnd();

	AE_ASSERT_MESG(mutebutton->pMesh, "Failed to create pause meshes!!\n");

	fullscreenbutton->pTexture = AEGfxTextureLoad("Images/mainmenubutton.png");
	mutebutton->pTexture = AEGfxTextureLoad("Images/resumebutton.png");
}

void logicoptionmenu()
{
	fullscreenbutton->itemcounter = mutebutton->itemcounter = 0.5f;
	AEMtx33 scale, rot, trans, buffer;

	AEInputGetCursorPosition(&cursorx, &cursory);

	AEMtx33Scale(&scale, 150.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&fullscreenbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, -100.0f);
	AEMtx33Concat(&mutebutton->transform, &trans, &buffer);

	AEMtx33Scale(&scale, 1000.0f, 1000.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&pausebackground->transform, &trans, &buffer);

	if (cursorx >= 326 && cursorx <= 474 && cursory >= 275 && cursory <= 320) {
		fullscreenbutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) 
		{
			systemsettings.fullscreen == 1 ? systemsettings.fullscreen = 0 : systemsettings.fullscreen = 1;
			click_Audio();
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}

	if (cursorx >= 326 && cursorx <= 474 && cursory >= 375 && cursory <= 420) {
		mutebutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON)) 
		{
			click_Audio();
			std::cout << "Sound Muted" << std::endl;
		}
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		systemsettings.options == 1 ? systemsettings.options = 0 : systemsettings.options = 1;
	}
}

void renderoptionmenu()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxSetTransform(pausebackground->transform.m);
	AEGfxSetTransparency(0.28f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(pausebackground->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(fullscreenbutton->transform.m);
	AEGfxSetTransparency(fullscreenbutton->itemcounter);
	AEGfxTextureSet(fullscreenbutton->pTexture, 0, 0);
	AEGfxMeshDraw(fullscreenbutton->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(mutebutton->transform.m);
	AEGfxSetTransparency(mutebutton->itemcounter);
	AEGfxTextureSet(mutebutton->pTexture, 0, 0);
	AEGfxMeshDraw(mutebutton->pMesh, AE_GFX_MDM_TRIANGLES);

	char strBuffer[35];

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);

	sprintf_s(strBuffer, "OPTIONS");
	AEGfxPrint(fontLarge, strBuffer, -0.34f, 0.35f, 1.0f, 1.0f, 0.0f, 0.0f);

	sprintf_s(strBuffer, "Press [esc] to exit");
	AEGfxPrint(fontLarge, strBuffer, -0.16f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f);
}

void logicpausemenu() {

	//if (AEInputCheckTriggered(AEVK_Q)) {
	//	next = GS_QUIT;
	//}

	menubutton->itemcounter = resumebutton->itemcounter = optionbutton->itemcounter = exitbutton->itemcounter = 0.5f;
	AEMtx33 scale, rot, trans, buffer;

	AEInputGetCursorPosition(&cursorx, &cursory);

	AEMtx33Scale(&scale, 150.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, -250.0f, 0.0f);
	AEMtx33Concat(&resumebutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&optionbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, -100.0f);
	AEMtx33Concat(&exitbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 250.0f, 0.0f);
	AEMtx33Concat(&menubutton->transform, &trans, &buffer);

	AEMtx33Scale(&scale, 1000.0f, 1000.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&pausebackground->transform, &trans, &buffer);

	if (systemsettings.options == 0)
	{
		if (cursorx >= 76 && cursorx <= 224 && cursory >= 275 && cursory <= 320) {
			resumebutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.paused = 0;
				click_Audio();
			}
		}

		if (cursorx >= 326 && cursorx <= 474 && cursory >= 275 && cursory <= 320) {
			optionbutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.options == 0 ? systemsettings.options = 1 : systemsettings.options = 0;
				click_Audio();
			}
		}

		if (cursorx >= 326 && cursorx <= 474 && cursory >= 375 && cursory <= 420) {
			exitbutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.paused = 0;
				click_Audio();
				next = GS_QUIT;
				systemsettings.exit_confirmation = 1;
			}
		}

		if (cursorx >= 577 && cursorx <= 726 && cursory >= 275 && cursory <= 320) {
			menubutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.paused = 0;
				click_Audio();
				player_initialise();
				enemy_initialise();
				next = MENU;
			}
		}
	}
	else
	{
		logicoptionmenu();
	}

	//if (AEInputCheckTriggered(AEVK_F11)) {
	//	systemsettings.fullscreen == 1 ? systemsettings.fullscreen = 0 : systemsettings.fullscreen = 1;
	//	AEToogleFullScreen(systemsettings.fullscreen);
	//}
}

void renderpausemenu() {

	if (systemsettings.options == 0)
	{
		// draw my buttons and meshes
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);


		AEGfxSetTransform(pausebackground->transform.m);
		AEGfxSetTransparency(0.28f);
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

		AEGfxSetTransform(optionbutton->transform.m);
		AEGfxSetTransparency(optionbutton->itemcounter);
		AEGfxTextureSet(optionbutton->pTexture, 0, 0);
		AEGfxMeshDraw(optionbutton->pMesh, AE_GFX_MDM_TRIANGLES);

		char strBuffer[35];

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetTransparency(1.0f);

		sprintf_s(strBuffer, "PAUSED");
		AEGfxPrint(fontLarge, strBuffer, -0.30f, 0.35f, 1.0f, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		renderoptionmenu();
	}


	//sprintf_s(strBuffer, "Press F11 to toggle fullscreen!");
	//AEGfxPrint(fontId, strBuffer, -0.23f, 0.3f, 1.14f, 0.5f, 0.5f, 0.5f);
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void unloadpausemenu() {
	
	if (menubutton->pMesh != nullptr) {
		AEGfxMeshFree(menubutton->pMesh);			// 1 MESH FREES ALL 3 MESHES
		menubutton->pMesh = nullptr;
	}
}

void unloadoptionmenu() {

	if (mutebutton->pMesh != nullptr) {
		AEGfxMeshFree(mutebutton->pMesh);			// 1 MESH FREES ALL 3 MESHES
		mutebutton->pMesh = nullptr;
	}
}

void player_initialise() {

/******************************************************************
*		PLAYER STRUCT DEFINITION
******************************************************************/
	//playerstats->PlayerLevel = 1;
	//playerstats->PlayerXP = 0;
	//playerstats->health = 100;							//health
	//playerstats->maxhealth = 100;
	//playerstats->positionID = 1;						//starting grid
	//playerstats->SAFEGRID = 1;							//starting SAFEGRID pos
	//playerstats->damage = 10;							//damage
	//playerstats->staminaCD = 1.0f;						// Cooldown for attack and movement
	//playerstats->resetCD = playerstats->staminaCD;		// Reset Cooldown for attack and movement
	//playerstats->staminacount = 0;						// Character stamina count
	//playerstats->staminamax = 3;						// Character stamina max
	//playerstats->staminaX = -37.0f;						// X position of stamina
	//playerstats->is_dmgtaken = 0.0f;					//to implement visual animations in future
	//playerstats->is_attacking = false;					//for enemy damage checks
	//playerstats->positionX = 0.0f;
	//playerstats->positionY = 0.0f;
	//playerstats->movementdt = 0.0f;
	//playerstats->status = NEUTRAL;

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
	//enemystats->EnemyType = NORMAL;
	//enemystats->EnemyState = IDLE;					//Current Enemy State
	//enemystats->positionX = 0.0f;
	//enemystats->positionY = 0.0f;
	//enemystats->is_attacking = false;			//Check for enemy attacking, used for check when player can attack
	//enemystats->AttackCD = 0.60f;				//Delay timer before enemy attack during attack phase
	//enemystats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack
	//enemystats->DamageCD = 0.0f;				//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
	//enemystats->EnemyLevel = 1;

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
	systemsettings.fullscreen = 1;
	systemsettings.paused = 0;
	systemsettings.exit_confirmation = 0;
	systemsettings.mute = 0;
	systemsettings.options = 0;
	systemsettings.digipenTimer = 3.0f;
	systemsettings.twentycentTimer = 3.0f;

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
	initialise_optionmenu();
}


void System_Exit() {
	unloadpausemenu();
	unloadoptionmenu();
	AEGfxDestroyFont(fontId);
	AEGfxDestroyFont(fontLarge);
	AEGfxTextureUnload(playerinventory->defencepotion.pTexture);
	AEGfxTextureUnload(playerinventory->healthpotion.pTexture);
	AEGfxTextureUnload(playerinventory->staminapotion.pTexture);
	AEGfxTextureUnload(menubutton->pTexture);
	AEGfxTextureUnload(exitbutton->pTexture);
	AEGfxTextureUnload(resumebutton->pTexture);
	AEGfxTextureUnload(optionbutton->pTexture);
	AEGfxTextureUnload(fullscreenbutton->pTexture);
	AEGfxTextureUnload(mutebutton->pTexture);
	AEGfxTextureUnload(yesbutton->pTexture);
	AEGfxTextureUnload(nobutton->pTexture);
	AEGfxMeshFree(playerinventory->defencepotion.pMesh);
	delete playerstats;
	delete enemystats;
	delete playerinventory;
	delete menubutton;
	delete exitbutton;
	delete resumebutton;
	delete pausebackground;
	delete optionbutton;
	delete mutebutton;
	delete fullscreenbutton;
	delete yesbutton;
	delete nobutton;

		for (int i{ 0 }; i < 150; ++i) {
			GameObjInst* pInst = ParticleInstList + i;
			delete pInst->pObject;
		}

	free(ParticleInstList);
}