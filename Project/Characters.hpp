//CHARACTER.HPP

#pragma once

#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include "pch.hpp"

namespace Characters
{

	/******************************************************
	*
	* PLAYER
	*
	*******************************************************/
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

		enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK };

		enum PlayerStatus { NEUTRAL, FROSTED, FROZEN, BURNING };

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
			int playerCD;
			bool is_attacking;
			float is_dmgtaken;
			float movementdt;
			int status;
			int PlayerXP;
			int PlayerLevel;
		};

		void PlayerMovement(int& x, c_statsheet* player, int& keypressed);

		c_statsheet* c_initialize();

		void CombatMesh(int RGBcounter);

		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

		void FreePlayerMesh();

		void FreePlayerMeshOnUpdate();

		void MeshInit();

		void StaminaRender(c_statsheet* Player, AEGfxTexture* staminapotion);

		void StaminaLogic(c_statsheet* Player, int const& keypressed);

		bool PlayerLevelUp(c_statsheet* player);

		void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh);

		void RGBloop(int& RGBcounter);

		void GridCheck(bool EnemyAttackState, float timer, int& x);

		void RenderPlayerHealth(s8 font, Character::c_statsheet* Player);
	}

	/******************************************************
	*
	* ENEMY
	*
	*******************************************************/
	namespace Enemies
	{
		extern AEGfxVertexList* EnemyGridIdle;
		extern AEGfxVertexList* EnemyGridAttack;
		extern AEGfxVertexList* EnemyMesh;
    extern AEGfxVertexList* Enemymaxhealth;
	  extern AEGfxVertexList* Enemycurrhealth;

		enum EnemyPos { IDLE, ATTACKING };

		enum EnemyType { NORMAL, ICE, FIRE };

		struct E_StatSheet
		{
			int EnemyType;
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
			int DebuffCounter;
			int EnemyXP;
			int EnemyLevel;
		};

		E_StatSheet* EnemyInitialize(int EnemyType);

		void EnemyCombatMesh();
  
		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

		void FreeEnemyMesh();

		void UpdateEnemyState(E_StatSheet* Enemy, Character::c_statsheet* Player);

		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy);

		void RenderEnemyHealth(s8 font, E_StatSheet* Enemy);
	}
}

#endif // !PCH_HPP
