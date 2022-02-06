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
		int EnemyGrid;
		float DamageCD;
	};

	E_StatSheet* EnemyInitialize();

	void EnemyCombatMesh();

	void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

	void FreeEnemyMesh();

	void UpdateEnemyState(E_StatSheet* Enemy, Character::c_statsheet* Player);

	void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy);

	void RenderEnemyHealth(s8 font, Enemy::E_StatSheet* Enemy);
}