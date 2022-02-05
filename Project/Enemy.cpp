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
		E_Stats->EnemyState = IDLE;
		E_Stats->EnemyCD = AERandFloat() * 8.0f;
		E_Stats->positionX = 0.0f;
		E_Stats->positionY = 0.0f;
		E_Stats->is_attacking = false;
		E_Stats->AttackCD = 0.4f;
		return E_Stats;
	}

	namespace
	{
		void EnemyAttackState(E_StatSheet* Enemy, Character::c_statsheet* Player)
		{
			if (Enemy->positionX != 150.0f)
			{
				Enemy->positionX += 10.0f;
			}
			Enemy->EnemyState = ATTACK;
			Enemy->is_attacking = true;
			if (Enemy->EnemyState == ATTACK && Enemy->is_attacking == true)
			{
				Player->SAFEGRID = (rand() % 3) + 1;
				Enemy->AttackCD -= DT;
				if (Enemy->AttackCD <= 0.0f)
				{
					if (Player->positionID != Player->SAFEGRID)
					{
						Player->health -= Enemy->damage;
						std::cout << Player->health << "Player" << "\n";
					}
					Enemy->AttackCD = 0.4f;
					Enemy->EnemyCD = AERandFloat() * 8.0f;
				}
			}
		}

		void EnemyIdleState(E_StatSheet* Enemy, Character::c_statsheet* Player)
		{
			Enemy->EnemyState = IDLE;
			Enemy->is_attacking = false;
			Enemy->positionX = 0.0f;
			Enemy->EnemyCD -= DT;
			if (Enemy->EnemyState == IDLE && Enemy->is_attacking == false)
			{
				if (Player->is_attacking == true)
				{
					Enemy->health -= Player->damage;
					Player->is_attacking = false;
					std::cout << Enemy->health << "\n";  
				}
			}
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

		AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
		AEGfxVertexAdd(125.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(125.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//ENEMY MESH
		AEGfxVertexAdd(75.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

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

	void RenderEnemy(AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(Enemy->positionX, Enemy->positionY);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
	}

}