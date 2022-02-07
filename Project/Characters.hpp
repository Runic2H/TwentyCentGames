#pragma once
#include "pch.hpp"



namespace Character
{
	extern AEGfxVertexList* Player1Grid;
	extern AEGfxVertexList* Player2Grid;
	extern AEGfxVertexList* Player3Grid;
	extern AEGfxVertexList* Player4Grid;
	extern AEGfxVertexList* Player5Grid;
	extern AEGfxVertexList* PlayerMesh;


	enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK }; //Please use this to decipher which grid player is on

	struct c_statsheet
	{
		float positionX;
		float positionY;
		int positionID;
		int SAFEGRID;
		int health;
		int damage;
		int playerCD;
		bool is_attacking;
		bool is_dmgtaken;
		float movementdt;
	};

	c_statsheet* c_initialize();

	void CombatMesh(int RGBcounter);

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

	void FreePlayerMesh();

	int PlayerMovement(int& x, c_statsheet* player);

	void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh);

	void RGBloop(int& RGBcounter);

	void GridCheck(bool EnemyAttackState, float timer, int& x);

	void RenderPlayerHealth(s8 font, Character::c_statsheet* Player);

	//void PlayerAttack(c_statsheet* Player, e_statsheet* Enemy);
	//void CameraShake(float camX, float camY);
	//int Playerdamage(c_statsheet* player, int SAFEGRID);
}









namespace Enemies
{
	extern AEGfxVertexList* EnemyGridIdle;
	extern AEGfxVertexList* EnemyGridAttack;
	extern AEGfxVertexList* EnemyMesh;

	enum EnemyPos { IDLE, ATTACKING };

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

	void RenderEnemyHealth(s8 font, E_StatSheet* Enemy);
}