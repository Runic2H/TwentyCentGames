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
	extern AEGfxVertexList* playermaxhealth;	//PLAYER HEALTH MESH
	extern AEGfxVertexList* playercurrhealth;

	enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK }; //Please use this to decipher which grid player is on

	struct c_statsheet
	{
		float positionX;
		float positionY;
		int positionID;
		int SAFEGRID;
		int health;
		int staminacount;
		int staminamax;
		float staminaCD;
		float staminaX;
		int maxhealth;
		int damage;
		bool is_attacking;
		bool is_dmgtaken;
		float movementdt;
	};

	c_statsheet* c_initialize();

	void CombatMesh(int RGBcounter);

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

	void FreePlayerMesh();

	void PlayerMovement(int& x, c_statsheet* player, int& keypressed);

	void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh);

	void RGBloop(int& RGBcounter);

	void GridCheck(bool EnemyAttackState, float timer, int& x);

	void RenderPlayerHealth(s8 font, Character::c_statsheet* Player);

	void FreePlayerMeshOnUpdate();

	void MeshInit();

	void StaminaRender(c_statsheet* Player, AEGfxTexture* staminapotion);

	void StaminaLogic(c_statsheet* Player, int const& keypressed);

	//void PlayerAttack(c_statsheet* Player, e_statsheet* Enemy);
	//void CameraShake(float camX, float camY);
	//int Playerdamage(c_statsheet* player, int SAFEGRID);
}









namespace Enemies
{
	extern AEGfxVertexList* EnemyGridIdle;
	extern AEGfxVertexList* EnemyGridAttack;
	extern AEGfxVertexList* EnemyMesh;
	extern AEGfxVertexList* Enemymaxhealth;
	extern AEGfxVertexList* Enemycurrhealth;

	enum EnemyPos { IDLE, ATTACKING };

	struct E_StatSheet
	{
		int health;
		int maxhealth;
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