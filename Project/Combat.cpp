//COMBAT.CPP

#include "pch.hpp"

/*****************************************************************
				GLOBAL DECLARATIONS
*****************************************************************/

int		RGB{ 16384000 };
int		&RGBcounter{ RGB };

int		switchvalue{ 0 },
		keyvalue{ 0 },
		counter{ 0 },
		SAFEGRID{ 1 },
		gridcounter{ 0 },
		gr{ 0 };

int		&keypressed{ keyvalue },
		showgridcounter{ gridcounter },
		choosegrid{ gr };

int		&x{ switchvalue }, y{};

float	movementdt;

AEGfxTexture* playertexture;
AEGfxTexture* enemytexture;
AEGfxTexture* enemytexturefire;
AEGfxTexture* enemytexturefrost;
AEGfxTexture* enemytextureBoss;
AEGfxTexture* staminapotion;


/*****************************************************************
				USING NAMESPACES
*****************************************************************/
using namespace Characters;
using namespace Characters::Enemies;
using namespace Characters::Character;


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Combat_Load()
{
	std::cout << "Combat:Load" << std::endl;

	playertexture = AEGfxTextureLoad("Images/Fighting duck.png");
	AE_ASSERT_MESG(playertexture, "cant create duck texture\n");

	enemytexture = AEGfxTextureLoad("Images/Angry turtle.png");
	AE_ASSERT_MESG(enemytexture, "cant create turtle texture\n");

	staminapotion = AEGfxTextureLoad("Images/staminapotion.png");
	AE_ASSERT_MESG(staminapotion, "cant create stamina potion texture\n");

	enemytexturefrost = AEGfxTextureLoad("Images/Frost turtle.png");
	AE_ASSERT_MESG(enemytexturefrost, "cant create enemy texture frost\n");

	enemytexturefire = AEGfxTextureLoad("Images/Fire turtle.png");
	AE_ASSERT_MESG(enemytexturefire, "cant create enemy texture fire\n");

	enemytextureBoss = AEGfxTextureLoad("Images/Boss_turtle.png");
	AE_ASSERT_MESG(enemytextureBoss, "cant create enemy texture boss\n");

}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{
	stop_Audio();	//JN: new code
	combat_background_Audio();
	//initialise_pausemenu();
	if (enemystats->EnemyType != ENEMYBOSS)
	{
		ChoosingEnemyType((f32)((rand() % 3) + 0));
	}
	else
	{
		SpawnBossEnemy();
	}
	MeshInit();		// Single init for the meshes that only need to be created once (NON RGB MESHES)
	AEToogleFullScreen(systemsettings.fullscreen); // R: added
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update()
{
	Audio_Update();

	if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 0) {
		systemsettings.paused = 1;
	} 

	else if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 1) {
		systemsettings.paused = 0;
	}

	// if not paused
	if (systemsettings.paused == 0 && systemsettings.exit_confirmation == 0)
	{
		RGBloop(RGBcounter);
		CombatMesh(RGBcounter);
		EnemyCombatMesh();
		inventorylogic();
		CheckandUpdatePlayerStatus();
		Backgroundupdate();
		godmode();

		playerstats->is_dmgtaken -= DT;

		if (enemystats->health <= 0)
		{
			std::cout << "You Won!\n";
			enemystats->health = 0;
			enemystats->EnemyType = 0;
			playerstats->debuffcounter = 0.0f;
			playerstats->PlayerXP += enemystats->EnemyXP;
			if (PlayerLevelUp())
			{
				playerstats->PlayerLevel += 1;
				playerstats->PlayerXP = 0;
				next = LEVELUP;
			}
			else
			{
				next = MAZE;
				maze_init_flag = 1;
				std::cout << "return to maze\n";
			}
		}

		else if (playerstats->health <= 0) {
		  std::cout << "You Died!\n";
		  playerstats->health = 0;
		  next = GAMEOVER;
		  maze_init_flag = 0;
		}
  
		if (keypressed == 0) {											// so i cant move whilst cooldown active
			PlayerMovement(x, keypressed);								// character movement	
			StaminaLogic(keypressed);
		}

		if (keypressed == 1) {
			playerstats->movementdt -= DT;
			if (playerstats->movementdt <= 0.0f) {
				playerstats->positionX = 0.0f;
				playerstats->positionY = 0.0f;
				playerstats->positionID = 1;
				playerstats->is_attacking = false;
				keypressed = 0;
			}
		}

		UpdateEnemyState();
	}

	else if (systemsettings.exit_confirmation == 1) {
		LogicExit_Confirmation();
	}

	// else paused == 1 and exitconf == 0
	else {
		logicpausemenu();
	}


	// particles //
	if (AEInputCheckCurr(AEVK_P)) {
		particleInstCreate(AERandFloat() * 10, playerstats->positionX-190, playerstats->positionY-20, particleENEMY);
	}

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


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	Backgroundrender();
	StaminaRender(staminapotion);
	inventoryrender();
	RenderEnemyHealth();
	RenderPlayerHealth();
	GridCheck(enemystats->is_attacking, enemystats->AttackCD, playerstats->SAFEGRID);
	playerrender(playertexture, Character::PlayerMesh);

	if (enemystats->AttackCD <= 0.60f)
	{
		RenderEnemyGrid(EnemyGridAttack);
	}

	if (enemystats->EnemyType == ICE)
	{
		RenderEnemy(enemytexturefrost, EnemyMesh);
	}
	if (enemystats->EnemyType == FIRE)
	{
		RenderEnemy(enemytexturefire, EnemyMesh);
	}
	if (enemystats->EnemyType == NORMAL) {
		RenderEnemy(enemytexture, EnemyMesh);
	}
	if (enemystats->EnemyType == ENEMYBOSS)
	{
		RenderEnemy(enemytextureBoss, EnemyMesh);
	}

	if (systemsettings.paused == 1) {
		renderpausemenu();
	}
	if (systemsettings.exit_confirmation == 1) {
		RenderExit_Confirmation();
	}

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
			AEGfxSetTintColor(0.9f, 0.6f, 0.04f, 1.0f);
		}
		else if (pInst->type == particleENEMYFIRE) {
			AEGfxSetTintColor(1.0f, 0.1f, 0.1f, 1.0f);
		}
		else if (pInst->type == particleENEMYFROST) {
			AEGfxSetTintColor(0.1f, 0.8f, 1.0f, 1.0f);
		}

		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}


/*
	Cleans game object instances. will be run in restart
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;
	FreePlayerMesh();
	FreeEnemyMesh();
	//unloadpausemenu();
}


/*
	Unload game assets. Frees and releases memory, wont be run in restart
*/
void Combat_Unload()
{
	unloadtextures();
	AEGfxTextureUnload(playertexture);
	AEGfxTextureUnload(enemytexture);
	AEGfxTextureUnload(staminapotion);
	AEGfxTextureUnload(enemytexturefrost);
	AEGfxTextureUnload(enemytexturefire);
	AEGfxTextureUnload(enemytextureBoss);
}