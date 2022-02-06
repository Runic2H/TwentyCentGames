#include "pch.hpp"

namespace Enemy
{
	AEGfxVertexList* EnemyGridIdle = 0;
	AEGfxVertexList* EnemyGridAttack = 0;
	AEGfxVertexList* EnemyMesh = 0;

	E_StatSheet* EnemyInitialize()
	{
		E_StatSheet* E_Stats = new E_StatSheet;
		E_Stats->health = 100;
		E_Stats->damage = 10;
		E_Stats->EnemyState = IDLE;				//Current Enemy State
		E_Stats->EnemyCD = 5.0f;				//Cooldown till next enemy attack
		E_Stats->positionX = 0.0f;
		E_Stats->positionY = 0.0f;
		E_Stats->is_attacking = false;			//Check for enemy attacking, used for check when player can attack
		E_Stats->AttackCD = 0.55f;				//Delay timer before enemy attack during attack phase
		E_Stats->EnemyGrid = (rand() % 3) + 1;	//Sets the safety grid for next attack
		E_Stats->DamageCD = 0.0f;				//Damage Cooldown after enemy attack phase, for players to not deal phantom damage
		return E_Stats;
	}

	namespace
	{
		void EnemyAttackState(E_StatSheet* Enemy, Character::c_statsheet* Player)
		{
			Player->SAFEGRID = Enemy->EnemyGrid;
			Enemy->EnemyState = ATTACK;
			Enemy->is_attacking = true;
			//Movement to Attack Grid
			if (Enemy->positionX != 150.0f)
			{
				Enemy->positionX += 10.0f;
			}
			if (Enemy->EnemyState == ATTACK && Enemy->is_attacking == true)
			{
				//Delay before enemy attack
				Enemy->AttackCD -= DT;
				if (Enemy->AttackCD <= 0.0f)
				{
					if (Player->positionID != Player->SAFEGRID)
					{
						Player->health -= Enemy->damage;
					}
					//Resets Everything such as Enemy Cooldown while in idle
					//Sets the AttackCD for the next attack phase
					//Sets the next safe grid for next attack
					Enemy->AttackCD = 0.55f;
					Enemy->EnemyCD = AERandFloat() * 7.2f;
					Enemy->EnemyGrid = (rand() % 3) + 1;
					Enemy->DamageCD = 1.2f;
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
		AEGfxMeshFree(EnemyGridIdle);
		AEGfxMeshFree(EnemyGridAttack);
	}


	void RenderEnemy(AEGfxTexture* enemytexture ,AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 1
		AEGfxSetPosition(Enemy->positionX, Enemy->positionY);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// No texture for object 1;
		AEGfxTextureSet(enemytexture, 1.0f, 1.0f);
		AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_TRIANGLES);
	}

	void RenderEnemyHealth(s8 font, Enemy::E_StatSheet* Enemy)
	{
		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Enemy Health:  %d", Enemy->health);

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(font, strBuffer, 0.60, -0.95, 1.0f, 1.f, 1.f, 1.f);
		AEGfxSetBlendMode(AE_GFX_BM_NONE);
	}

}