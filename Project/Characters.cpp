//CHARACTER CPP

#include "pch.hpp"

namespace Characters
{
	/******************************************************
	*
	* PLAYER NAMESPACE
	*
	*******************************************************/
	namespace Character
	{

		AEGfxVertexList* Player1Grid = 0; //ORIGN
		AEGfxVertexList* Player2Grid = 0; //TOP
		AEGfxVertexList* Player3Grid = 0; //BACK
		AEGfxVertexList* Player4Grid = 0; //BOTTOM
		AEGfxVertexList* Player5Grid = 0; //ATTACK
		AEGfxVertexList* PlayerMesh = 0;
		int counter{ 21 };

		c_statsheet* c_initialize()
		{
			c_statsheet* c_stats = new c_statsheet;
			c_stats->PlayerLevel = 1;
			c_stats->PlayerXP = 0;
			c_stats->health = 100;								//health
			c_stats->positionID = 1;							//starting grid
			c_stats->SAFEGRID = 1;								//starting SAFEGRID pos
			c_stats->damage = 10;								//damage
			c_stats->playerCD = 5;								//Cooldown for attack and movement
			c_stats->is_dmgtaken = 0.0f;						//to implement visual animations in future
			c_stats->is_attacking = false;						//for enemy damage checks
			c_stats->positionX = 0.0f;
			c_stats->positionY = 0.0f;
			c_stats->movementdt = 0.0f;
			c_stats->status = NEUTRAL;
			return c_stats;
		}

		void CombatMesh(int RGBcounter)
		{

			FreePlayerMesh();

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -60.0f, RGBcounter, 1.0f, 1.0f);				//PLAYERGRID 4 BOTTOM
			AEGfxVertexAdd(-240.0f, -60.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);

			Player4Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player4Grid, "Failed to create playermesh4!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-250.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-250.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
			AEGfxVertexAdd(-350.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player3Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player3Grid, "Failed to create playermesh3!!");

			// 

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 60.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
			AEGfxVertexAdd(-240.0f, 60.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);

			Player2Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh2!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 1 MIDDLE
			AEGfxVertexAdd(-240.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player1Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player1Grid, "Failed to create playermesh1!!");

			AEGfxMeshStart();

			AEGfxVertexAdd(0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(-100.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(-100.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
			AEGfxVertexAdd(0.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			Player5Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player5Grid, "Failed to create playermesh5!!");



			AEGfxMeshStart();

			AEGfxTriAdd(
				-215.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
				-165.0f, -25.0f, 0x00FFFF00, 1.0f, 1.0f,
				-215.0f, 25.0f, 0x0000FFFF, 0.0f, 0.0f);
			//x,y,colour,u,v
																				//CHARACTER OBJECT
			AEGfxTriAdd(
				-165.0f, -25.0f, 0x00FFFFFF, 1.0f, 1.0f,
				-165.0f, 25.0f, 0x00FFFFFF, 1.0f, 0.0f,
				-215.0f, 25.0f, 0x00FFFFFF, 0.0f, 0.0f);


			PlayerMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(PlayerMesh, "Failed to create character!!");
		}


		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			// Set position for object 1
			AEGfxSetPosition(0.0f, 0.0f);
			// No texture for object 1
			AEGfxTextureSet(NULL, 0, 0);

			AEGfxMeshDraw(PlayerMesh, AE_GFX_MDM_LINES_STRIP);
		}


		void FreePlayerMesh()
		{


			if (Player1Grid != nullptr) {
				AEGfxMeshFree(Player1Grid);
				Player1Grid = nullptr;
			}

			if (Player2Grid != nullptr) {
				AEGfxMeshFree(Player2Grid);
				Player2Grid = nullptr;
			}

			if (Player3Grid != nullptr) {
				AEGfxMeshFree(Player3Grid);
				Player3Grid = nullptr;
			}

			if (Player4Grid != nullptr) {
				AEGfxMeshFree(Player4Grid);
				Player4Grid = nullptr;
			}

			if (Player5Grid != nullptr) {
				AEGfxMeshFree(Player5Grid);
				Player5Grid = nullptr;
			}

			if (PlayerMesh != nullptr) {
				AEGfxMeshFree(PlayerMesh);
				PlayerMesh = nullptr;
			}

		}


		bool PlayerLevelUp(c_statsheet* player)
		{
			if (player->PlayerXP >= 100)
			{
				return true;
			}
			return false;
		}

		int PlayerMovement(int& x, c_statsheet* player) {

			int keypressed = 0;
			if (player->status != FROZEN)
			{
				x = 0;

				AEInputCheckTriggered(AEVK_W) ? x = TOP : x = x;	//ID Should be 1
				AEInputCheckTriggered(AEVK_A) ? x = BACK : x = x;	//ID Should be 2
				AEInputCheckTriggered(AEVK_S) ? x = DOWN : x = x;	//ID Should be 3
				AEInputCheckTriggered(AEVK_D) ? x = ATTACK : x = x;	//ID Should be 4

				player->movementdt = 0.5f;

				switch (x) {

				case ATTACK:	//ATTACK GRID
					player->positionID = ATTACK;
					player->positionX = 145.0f;
					player->positionY = 0.0f;
					keypressed = 1;
					player->is_attacking = true;
					break;

				case TOP:
					player->positionID = TOP;
					player->positionX = 0.0f;
					player->positionY = 110.0f;
					player->is_attacking = false;
					keypressed = 1;
					break;

				case BACK:
					player->positionID = BACK;
					player->positionX = -110.0f;
					player->positionY = 0.8f;
					player->is_attacking = false;
					keypressed = 1;
					break;

				case DOWN:
					player->positionID = DOWN;
					player->positionX = 0.0f;
					player->positionY = -110.0f;
					player->is_attacking = false;
					keypressed = 1;
					break;


				case 5:	//ATTACK GRID
					player->positionID = 5;
					player->positionX = 145.0f;
					player->positionY = 0.0f;
					player->is_attacking = true;
					keypressed = 1;
					break;
				}

				if (player->positionX == 0.0f && player->positionY == 0.0f) {
					player->positionID = ORIGIN;
					player->is_attacking = false;
				}
			}
			if (player->status == FROZEN)
			{
				if (counter == 0)
				{
					player->status = NEUTRAL;
				}
				else
				{
					if (AEInputCheckTriggered(AEVK_LEFT) || AEInputCheckTriggered(AEVK_RIGHT))
					{
						--counter;
						std::cout << counter << "\n";
					}
				}
			}

			return keypressed;
		}

		void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh) {

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			// Set position for object 1
			AEGfxSetPosition(player->positionX, player->positionY);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxTextureSet(playertexture, 1.0f, 1.0f);

			AEGfxMeshDraw(playermesh, AE_GFX_MDM_TRIANGLES);
		}


		void RGBloop(int& RGBcounter) {
			if (RGBcounter <= 16777215)
			{
				RGBcounter += 500;
				(RGBcounter > 16766215) ? RGBcounter = 16384000 : RGBcounter = RGBcounter;
			}
		}


		void GridCheck(bool EnemyAttackState, float timer, int& x) {

			if (EnemyAttackState == true && timer <= 0.60f) {

				switch (x) // Check for the Safety Grids
				{

				case 1:
					//SAFEGRID (TOP SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 2:
					//SAFEGRID (BACK SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 3:
					//SAFEGRID (BOTTOM SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;
				}
			}
		}

		void RenderPlayerHealth(s8 font, Character::c_statsheet* Player)
		{
			char strBufferHealth[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Player Health:  %d", Player->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", Player->PlayerLevel);

			char strBufferStatus[100];
			memset(strBufferStatus, 0, 100 * sizeof(char));
			switch (Player->status)
			{
			case FROSTED:
				sprintf_s(strBufferStatus, "Status: Frosted");
				break;
			case FROZEN:
				sprintf_s(strBufferStatus, "Status: Frozen");
				break;
			case NEUTRAL:
				sprintf_s(strBufferStatus, "Status: Normal");
				break;
			}

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(font, strBufferHealth, -0.95f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(font, strBufferLevel, -0.95f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(font, strBufferStatus, -0.95f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}


	}


	/******************************************************
	*
	* ENEMY NAMESPACE
	*
	*******************************************************/
	namespace Enemies
	{
		AEGfxVertexList* EnemyGridIdle = 0;
		AEGfxVertexList* EnemyGridAttack = 0;
		AEGfxVertexList* EnemyMesh = 0;

		E_StatSheet* EnemyInitialize(int EnemyType)
		{
			E_StatSheet* E_Stats = new E_StatSheet;

			E_Stats->EnemyType = EnemyType;
			E_Stats->EnemyState = IDLE;				//Current Enemy State
			E_Stats->positionX = 0.0f;
			E_Stats->positionY = 0.0f;
			E_Stats->is_attacking = false;			//Check for enemy attacking, used for check when player can attack
			E_Stats->AttackCD = 0.60f;				//Delay timer before enemy attack during attack phase
			E_Stats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack
			E_Stats->DamageCD = 0.0f;				//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
			E_Stats->EnemyLevel = 1;

			switch (EnemyType)
			{
			case NORMAL:
				E_Stats->health = 50;
				E_Stats->damage = 10;
				E_Stats->EnemyCD = 3.0f;				//Cooldown till next enemy attack
				E_Stats->EnemyXP = 20;
				break;
			case ICE:
				E_Stats->health = 100;
				E_Stats->damage = 20;
				E_Stats->EnemyCD = 3.0f;				//Cooldown till next enemy attack
				E_Stats->DebuffCounter = 0;
				E_Stats->EnemyXP = 100;
				break;
			}
			return E_Stats;
		}

		namespace
		{
			void EnemyTypeCheckToApplyPlayerDebuff(E_StatSheet* Enemy, Character::c_statsheet* Player)
			{

				switch (Enemy->EnemyType)
				{
				case ICE:
					++Enemy->DebuffCounter;
					if (Player->status != Character::FROZEN)
					{
						Player->status = Character::FROSTED;
						//To implement stamina slowdown
					}
					if (Enemy->DebuffCounter == 3 && Player->status == Character::FROSTED)
					{
						Player->status = Character::FROZEN;
						Character::counter = 21;
						Enemy->DebuffCounter = 0;
					}
					break;
				case NORMAL:
					break;
				}
			}

			void EnemyAttackState(E_StatSheet* Enemy, Character::c_statsheet* Player)
			{
				Player->SAFEGRID = Enemy->EnemyGrid;
				Enemy->EnemyState = ATTACKING;
				Enemy->is_attacking = true;

				//Movement to Attack Grid
				if (Enemy->positionX != 150.0f)
				{
					Enemy->positionX += 10.0f;
				}
				if (Enemy->EnemyState == ATTACKING && Enemy->is_attacking == true)
				{
					//Delay before enemy attack
					Enemy->AttackCD -= DT;
					if (Enemy->AttackCD <= 0.0f)
					{
						if (Player->positionID != Player->SAFEGRID)
						{
							Player->health -= Enemy->damage;
							EnemyTypeCheckToApplyPlayerDebuff(Enemy, Player);
						}

						//Resets Everything such as Enemy Cooldown while in idle
						//Sets the AttackCD for the next attack phase
						//Sets the next safe grid for next attack
						Enemy->AttackCD = 0.60f;
						Enemy->EnemyCD = static_cast<float>((rand() % 4) + 1);
						Enemy->EnemyGrid = (rand() % 3) + 1;
						Enemy->DamageCD = 1.0f;
					}
				}
			}

			void EnemyIdleState(E_StatSheet* Enemy, Character::c_statsheet* Player)
			{
				//Idle state and reducing of enemyCD to next attack
				//DamageCD is for frames where player cannot attack the enemy as enemy
				//is returning to idle state
				Enemy->EnemyState = IDLE;
				Enemy->is_attacking = false;
				Enemy->positionX = 0.0f;
				Enemy->positionY = 0.0f;
				Enemy->EnemyCD -= DT;
				Enemy->DamageCD -= DT;
				if (Enemy->EnemyState == IDLE && Enemy->is_attacking == false)
				{
					//Check for Player Damage
					if (Player->is_attacking == true && Enemy->DamageCD <= 0.0f)
					{
						Enemy->health -= Player->damage;
						Player->is_attacking = false;
					}
				}
			}
		}

		//Main Update loop for Idle and Attack States of Enemy
		void UpdateEnemyState(E_StatSheet* Enemy, Character::c_statsheet* Player)
		{
			if (Enemy->EnemyCD <= 0.0f)
			{
				EnemyAttackState(Enemy, Player);
			}
			else
			{
				EnemyIdleState(Enemy, Player);
			}
		}

		void EnemyCombatMesh()
		{
			FreeEnemyMesh();													//deletes old mesh

			AEGfxMeshStart();

			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(150.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(150.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID IDLE
			AEGfxVertexAdd(50.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridIdle = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridIdle, "Failed to create enemygrididle!!");


			AEGfxMeshStart();

			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(300.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(300.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID ATTACK
			AEGfxVertexAdd(200.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridAttack = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridAttack, "Failed to create enemygrididle!!");


			AEGfxMeshStart();

			//AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(125.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
			//AEGfxVertexAdd(125.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//ENEMY MESH
			//AEGfxVertexAdd(75.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
			//AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

			AEGfxTriAdd(
				75.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
				125.0f, -25.0f, 0x00FFFF00, 1.0f, 1.0f,
				75.0f, 25.0f, 0x0000FFFF, 0.0f, 0.0f);
			//x,y,colour,u,v

			AEGfxTriAdd(
				125.0f, -25.0f, 0x00FFFFFF, 1.0f, 1.0f,
				125.0f, 25.0f, 0x00FFFFFF, 1.0f, 0.0f,
				75.0f, 25.0f, 0x00FFFFFF, 0.0f, 0.0f);

			EnemyMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyMesh, "Failed to create character!!");
		}

		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			// Set position for object 1
			AEGfxSetPosition(0.0f, 0.0f);
			// No texture for object 1
			AEGfxTextureSet(NULL, 0, 0);

			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
		}

		void FreeEnemyMesh()
		{

			if (EnemyGridIdle != nullptr) {
				AEGfxMeshFree(EnemyGridIdle);
				EnemyGridIdle = nullptr;
			}

			if (EnemyGridAttack != nullptr) {
				AEGfxMeshFree(EnemyGridAttack);
				EnemyGridAttack = nullptr;
			}

			if (EnemyMesh != nullptr) {
				AEGfxMeshFree(EnemyMesh);
				EnemyMesh = nullptr;
			}
		}


		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			// Set position for object 1
			AEGfxSetPosition(Enemy->positionX, Enemy->positionY);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			// No texture for object 1;
			AEGfxTextureSet(enemytexture, 1.0f, 1.0f);
			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_TRIANGLES);
		}

		void RenderEnemyHealth(s8 font, E_StatSheet* Enemy)
		{
			char strBufferHealth[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Enemy Health:  %d", Enemy->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", Enemy->EnemyLevel);

			char strBufferType[100];
			memset(strBufferType, 0, 100 * sizeof(char));
			switch (Enemy->EnemyType)
			{
			case NORMAL:
				sprintf_s(strBufferType, "Enemy Type: Normal");
				break;
			case ICE:
				sprintf_s(strBufferType, "Enemy Type: Frost");
				break;
			}

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(font, strBufferHealth, 0.60f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(font, strBufferLevel, 0.60f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(font, strBufferType, 0.60f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}
	}
}