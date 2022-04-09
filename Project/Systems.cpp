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
item* nofullscreenbutton;
item* nomutebutton;
item* sliderbgm;
item* slidersfx;
item* slidertriangleleftbgm;
item* slidertrianglerightbgm;
item* slidertriangleleftsfx;
item* slidertrianglerightsfx;

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


void slidermeshupdate()
{

	if (sliderbgm->pMesh != nullptr)
	{
		AEGfxMeshFree(sliderbgm->pMesh);
		sliderbgm->pMesh = nullptr;
	}

	if (slidersfx->pMesh != nullptr)
	{
		AEGfxMeshFree(slidersfx->pMesh);
		slidersfx->pMesh = nullptr;
	}

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.2f, 0xFFFFFFFF, 0.0f, 1.0f,
		bgm_volume-0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		bgm_volume-0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		bgm_volume-0.5f, 0.2f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);

	sliderbgm->pMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.2f, 0xFFFFFFFF, 0.0f, 1.0f,
		sfx_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		sfx_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		sfx_volume - 0.5f, 0.2f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);

	slidersfx->pMesh = AEGfxMeshEnd();
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
	nomutebutton = new item;
	nofullscreenbutton = new item;
	sliderbgm = new item;
	slidersfx = new item;
	slidertriangleleftbgm = new item;
	slidertrianglerightbgm = new item;
	slidertriangleleftsfx = new item;
	slidertrianglerightsfx = new item;


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		mutebutton->pMesh
		= fullscreenbutton->pMesh
		= nofullscreenbutton->pMesh
		= nomutebutton->pMesh
		= AEGfxMeshEnd();
	
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.2f, 0xFFFFFFFF, 0.0f, 1.0f,
		bgm_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		bgm_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		bgm_volume - 0.5f, 0.2f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);

	sliderbgm->pMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.2f, 0xFFFFFFFF, 0.0f, 1.0f,
		sfx_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		sfx_volume - 0.5f, -0.2f, 0xFFFFFFFF, 1.0f, 1.0f,
		sfx_volume - 0.5f, 0.2f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.2f, 0xFFFFFFFF, 0.0f, 0.0f);

	slidersfx->pMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		0.1f, -0.1f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.1f, 0.1f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	slidertriangleleftbgm->pMesh = slidertriangleleftsfx->pMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.1f, 0.1f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.1f, -0.1f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.0f, -0.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	slidertrianglerightbgm->pMesh = slidertrianglerightsfx->pMesh = AEGfxMeshEnd();

	fullscreenbutton->pTexture = AEGfxTextureLoad("Images/fullscreenbuttonyes.png");
	AE_ASSERT_MESG(fullscreenbutton->pMesh, "Failed to create option meshes!!\n");

	nofullscreenbutton->pTexture = AEGfxTextureLoad("Images/fullscreenbuttonno.png");
	AE_ASSERT_MESG(nofullscreenbutton->pMesh, "Failed to create option meshes!!\n");

	mutebutton->pTexture = AEGfxTextureLoad("Images/mutebuttonyes.png");
	AE_ASSERT_MESG(mutebutton->pMesh, "Failed to create option meshes!!\n");

	nomutebutton->pTexture = AEGfxTextureLoad("Images/mutebuttonno.png");
	AE_ASSERT_MESG(nomutebutton->pMesh, "Failed to create option meshes!!\n");
}



void logicoptionmenu()
{
	fullscreenbutton->itemcounter = mutebutton->itemcounter = 
	nomutebutton->itemcounter = nofullscreenbutton->itemcounter =
	slidertriangleleftbgm->itemcounter = slidertrianglerightbgm->itemcounter =
	slidertriangleleftsfx->itemcounter = slidertrianglerightsfx->itemcounter = 0.5f;

	AEMtx33 scale, rot, trans, buffer;

	AEInputGetCursorPosition(&cursorx, &cursory);

	AEMtx33Scale(&scale, 150.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&fullscreenbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, -100.0f);
	AEMtx33Concat(&mutebutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&nofullscreenbutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 0.0f, -100.0f);
	AEMtx33Concat(&nomutebutton->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 25.0f, -170.0f);
	AEMtx33Concat(&sliderbgm->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 25.0f, -230.0f);
	AEMtx33Concat(&slidersfx->transform, &trans, &buffer);

	AEMtx33Trans(&trans, -75.0f, -170.0f);
	AEMtx33Concat(&slidertriangleleftbgm->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 50.0f, -170.0f);
	AEMtx33Concat(&slidertrianglerightbgm->transform, &trans, &buffer);

	AEMtx33Trans(&trans, -75.0f, -230.0f);
	AEMtx33Concat(&slidertriangleleftsfx->transform, &trans, &buffer);

	AEMtx33Trans(&trans, 50.0f, -230.0f);
	AEMtx33Concat(&slidertrianglerightsfx->transform, &trans, &buffer);

	AEMtx33Scale(&scale, 1000.0f, 1000.0f);
	AEMtx33Concat(&buffer, &scale, &rot);
	AEMtx33Trans(&trans, 0.0f, 0.0f);
	AEMtx33Concat(&pausebackground->transform, &trans, &buffer);

	if (cursorx >= 326 && cursorx <= 474 && cursory >= 275 && cursory <= 320) {
		fullscreenbutton->itemcounter = 1.0f;
		nofullscreenbutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			systemsettings.fullscreen == 1 ? systemsettings.fullscreen = 0 : systemsettings.fullscreen = 1;
			click_Audio();	//JN: new code
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}

	if (cursorx >= 326 && cursorx <= 474 && cursory >= 375 && cursory <= 420) {
		mutebutton->itemcounter = 1.0f;
		nomutebutton->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			click_Audio();	//JN: new code
			systemsettings.mute == 1 ? systemsettings.mute = 0 : systemsettings.mute = 1;
			if (systemsettings.mute == 1)
			{
				mute_master_fader();
			}
			else if (systemsettings.mute == 0)
			{
				unmute_master_fader();
			}
		}
	}

	if (cursorx >= 325 && cursorx <= 340 && cursory >= 465 && cursory <= 475) {
		slidertriangleleftbgm->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			click_Audio();
			decrease_bgm_fader();
		}
	}

	if (cursorx >= 435 && cursorx <= 450 && cursory >= 465 && cursory <= 475) {
		slidertrianglerightbgm->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			click_Audio();
			increase_bgm_fader();
		}
	}

	if (cursorx >= 325 && cursorx <= 340 && cursory >= 520 && cursory <= 535) {
		slidertriangleleftsfx->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			click_Audio();
			decrease_sfx_fader();
		}
	}

	if (cursorx >= 435 && cursorx <= 450 && cursory >= 520 && cursory <= 535) {
		slidertrianglerightsfx->itemcounter = 1.0f;
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			click_Audio();
			increase_sfx_fader();
		}
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		systemsettings.options == 1 ? systemsettings.options = 0 : systemsettings.options = 1;
	}
}

void renderoptionmenu()
{
	slidermeshupdate();

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTransform(sliderbgm->transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(sliderbgm->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(slidersfx->transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(slidersfx->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(slidertriangleleftbgm->transform.m);
	AEGfxSetTransparency(slidertriangleleftbgm->itemcounter);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(slidertriangleleftbgm->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(slidertrianglerightbgm->transform.m);
	AEGfxSetTransparency(slidertrianglerightbgm->itemcounter);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(slidertrianglerightbgm->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(slidertriangleleftsfx->transform.m);
	AEGfxSetTransparency(slidertriangleleftsfx->itemcounter);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(slidertriangleleftsfx->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(slidertrianglerightsfx->transform.m);
	AEGfxSetTransparency(slidertrianglerightsfx->itemcounter);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(slidertrianglerightsfx->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	AEGfxSetTransform(pausebackground->transform.m);
	AEGfxSetTransparency(0.28f);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxMeshDraw(pausebackground->pMesh, AE_GFX_MDM_TRIANGLES);

	if (systemsettings.fullscreen == 1)
	{
		AEGfxSetTransform(fullscreenbutton->transform.m);
		AEGfxSetTransparency(fullscreenbutton->itemcounter);
		AEGfxTextureSet(fullscreenbutton->pTexture, 0, 0);
		AEGfxMeshDraw(fullscreenbutton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	else
	{
		AEGfxSetTransform(nofullscreenbutton->transform.m);
		AEGfxSetTransparency(nofullscreenbutton->itemcounter);
		AEGfxTextureSet(nofullscreenbutton->pTexture, 0, 0);
		AEGfxMeshDraw(nofullscreenbutton->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	if (systemsettings.mute == 1)
	{
		AEGfxSetTransform(mutebutton->transform.m);
		AEGfxSetTransparency(mutebutton->itemcounter);
		AEGfxTextureSet(mutebutton->pTexture, 0, 0);
		AEGfxMeshDraw(mutebutton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	else
	{
		AEGfxSetTransform(nomutebutton->transform.m);
		AEGfxSetTransparency(nomutebutton->itemcounter);
		AEGfxTextureSet(nomutebutton->pTexture, 0, 0);
		AEGfxMeshDraw(nomutebutton->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	char strBuffer[35];

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);

	sprintf_s(strBuffer, "OPTIONS");
	AEGfxPrint(fontLarge, strBuffer, -0.34f, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Press [esc] to exit");
	AEGfxPrint(fontLarge, strBuffer, -0.16f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "BGM");
	AEGfxPrint(fontLarge, strBuffer, -0.12f, -0.52f, 0.25f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "SFX");
	AEGfxPrint(fontLarge, strBuffer, -0.12f, -0.72f, 0.25f, 1.0f, 1.0f, 1.0f);
}

void logicpausemenu() {

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
				click_Audio();	//JN: new code
			}
		}

		if (cursorx >= 326 && cursorx <= 474 && cursory >= 275 && cursory <= 320) {
			optionbutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.options == 0 ? systemsettings.options = 1 : systemsettings.options = 0;
				click_Audio();	//JN: new code
			}
		}

		if (cursorx >= 326 && cursorx <= 474 && cursory >= 375 && cursory <= 420) {
			exitbutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.paused = 0;
				click_Audio();	//JN: new code
				systemsettings.exit_confirmation = 1;
			}
		}

		if (cursorx >= 577 && cursorx <= 726 && cursory >= 275 && cursory <= 320) {
			menubutton->itemcounter = 1.0f;
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				systemsettings.paused = 0;
				click_Audio();	//JN: new code
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

	if (slidertriangleleftbgm->pMesh != nullptr)
	{
		AEGfxMeshFree(slidertriangleleftbgm->pMesh);			// 1 MESH FREES ALL 3 MESHES
		slidertriangleleftbgm->pMesh = nullptr;
	}

	if (slidertrianglerightbgm->pMesh != nullptr)
	{
		AEGfxMeshFree(slidertrianglerightbgm->pMesh);			// 1 MESH FREES ALL 3 MESHES
		slidertrianglerightbgm->pMesh = nullptr;
	}

	if (sliderbgm->pMesh != nullptr)
	{
		AEGfxMeshFree(sliderbgm->pMesh);
		sliderbgm->pMesh = nullptr;
	}

	if (slidersfx->pMesh != nullptr)
	{
		AEGfxMeshFree(slidersfx->pMesh);
		slidersfx->pMesh = nullptr;
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
	inFile >> str >> playerstats->positionID;		//starting grid
	inFile >> str >> playerstats->SAFEGRID;			//starting SAFEGRID pos
	inFile >> str >> playerstats->damage;
	inFile >> str >> playerstats->staminaCD;		// Cooldown for attack and movement
	inFile >> str >> playerstats->staminacount;		// Character stamina count
	inFile >> str >> playerstats->staminamax;		// Character stamina max
	inFile >> str >> playerstats->staminaX;			// X position of stamina
	inFile >> str >> playerstats->is_dmgtaken;		// CD for player damage
	inFile >> str >> playerstats->is_attacking;		//for enemy damage checks
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

	inFile >> str >> enemystats->EnemyType;			//Enemy Type
	inFile >> str >> enemystats->EnemyState;		//State of the enemy
	inFile >> str >> enemystats->positionX;
	inFile >> str >> enemystats->positionY;
	inFile >> str >> enemystats->is_attacking;		//Check for enemy attacking, used for check when player can attack
	inFile >> str >> enemystats->AttackCD;			//Delay timer before enemy attack during attack phase
	inFile >> str >> enemystats->DamageCD;			//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
	
	enemystats->EnemyGrid = (rand() % 3) + 1;		//Sets the safety grid for next attack

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
	AEGfxTextureUnload(nomutebutton->pTexture);
	AEGfxTextureUnload(nofullscreenbutton->pTexture);
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
	delete nomutebutton;
	delete nofullscreenbutton;
	delete yesbutton;
	delete nobutton;
	delete sliderbgm;
	delete slidersfx;
	delete slidertriangleleftbgm;
	delete slidertrianglerightbgm;
	delete slidertriangleleftsfx;
	delete slidertrianglerightsfx;

		for (int i{ 0 }; i < 150; ++i) {
			GameObjInst* pInst = ParticleInstList + i;
			delete pInst->pObject;
		}

	free(ParticleInstList);
}