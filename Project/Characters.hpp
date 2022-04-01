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

		//enum PlayerPos { ORIGIN, TOP, BACK, DOWN, ATTACK };
		//enum PlayerStatus { NEUTRAL, FROSTED, FROZEN, BURNING };

		void PlayerMovement(int& x, int& keypressed);

		void CombatMesh(int RGBcounter);

		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

		void FreePlayerMesh();

		void FreePlayerMeshOnUpdate();

		void MeshInit();

		void StaminaRender(AEGfxTexture* staminapotion);

		void StaminaLogic(int const& keypressed);

		void CheckandUpdatePlayerStatus();

		bool PlayerLevelUp();

		void playerrender(AEGfxTexture* playertexture, AEGfxVertexList* playermesh);

		void RGBloop(int& RGBcounter);

		void GridCheck(bool EnemyAttackState, float timer, int& x);

		void RenderPlayerHealth();

		void inventorylogic();

		void inventoryrender();

		void renderpausemenu();

		void logicpausemenu();
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

		void ChoosingEnemyType(float);

		void EnemyCombatMesh();
  
		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

		void FreeEnemyMesh();

		void UpdateEnemyState();

		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh);

		void RenderEnemyHealth();
	}
}

#endif // !PCH_HPP
