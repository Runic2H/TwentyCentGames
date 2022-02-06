#pragma once
#include "pch.hpp"

namespace Enemy
{
	extern AEGfxVertexList* EnemyGridIdle;
	extern AEGfxVertexList* EnemyGridAttack;
	extern AEGfxVertexList* EnemyMesh;

	enum EnemyPos { IDLE, ATTACK };

	struct E_StatSheet
	{
		int health;
		int damage;
		int EnemyState;
		float EnemyCD;
		float positionX;
		float positionY;
		bool is_attacking;
		float AttackCD;
	};

	E_StatSheet* EnemyInitialize();

	void EnemyCombatMesh();

	void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

	void FreeEnemyMesh();

	void UpdateEnemyState(E_StatSheet* Enemy, Character::c_statsheet* Player);

	void RenderEnemy(AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy);
}