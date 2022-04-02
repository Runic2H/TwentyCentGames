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
	//playertexture = AEGfxTextureLoad("ducky.jpg");
	playertexture = AEGfxTextureLoad("Fighting duck.png");
	AE_ASSERT_MESG(playertexture, "cant create duck texture\n");

	//enemytexture = AEGfxTextureLoad("Turtle.png");
	enemytexture = AEGfxTextureLoad("Angry turtle.png");
	AE_ASSERT_MESG(enemytexture, "cant create turtle texture\n");


	staminapotion = AEGfxTextureLoad("staminapotion.png");
	AE_ASSERT_MESG(staminapotion, "cant create stamina potion texture\n");

}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{
	ChoosingEnemyType((rand() % 3) + 0);
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
  
	if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 0) {
		systemsettings.paused = 1;
	} 

	else if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 1) {
		systemsettings.paused = 0;
	}

	// if not paused
	if (systemsettings.paused == 0)
	{
    
		RGBloop(RGBcounter);
		CombatMesh(RGBcounter);
		EnemyCombatMesh();
		inventorylogic();
		CheckandUpdatePlayerStatus();

		if (enemystats->health <= 0)
		{
			std::cout << "You Won!\n";
			next = MAZE;
			maze_init_flag = 1;
			std::cout << "return to maze\n";
		}
    else if (playerstats->health <= 0) {
      std::cout << "You Died!\n";
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

		if (enemystats->health <= 0)
		{
			playerstats->PlayerXP += enemystats->EnemyXP;
			if (PlayerLevelUp())
			{
				playerstats->PlayerLevel += 1;
			  playerstats->PlayerXP = 0;
			  next = LEVELUP;
			}
		}
	}

	// else paused
	else {
		//render pause menu here
		logicpausemenu();
		renderpausemenu();
		}	
  
  }


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{

	StaminaRender(staminapotion);
	inventoryrender();
	RenderEnemyHealth();
	RenderPlayerHealth();
	GridCheck(enemystats->is_attacking, enemystats->AttackCD, playerstats->SAFEGRID);
	playerrender(playertexture, Character::PlayerMesh);

	if (enemystats->AttackCD <= 0.40f)
	{
		RenderEnemyGrid(EnemyGridAttack);
	}

	RenderEnemy(enemytexture, EnemyMesh);
}


/*
	Cleans game object instances. will be run in restart
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;
	FreePlayerMesh();
	FreeEnemyMesh();
}


/*
	Unload game assets. Frees and releases memory, wont be run in restart
*/
void Combat_Unload()
{
	AEGfxTextureUnload(playertexture);
	AEGfxTextureUnload(enemytexture);
	AEGfxTextureUnload(staminapotion);

}