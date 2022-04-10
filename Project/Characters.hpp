/**************************************************************************
 * 	File name	:	Characters.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Elton Teo Zhe Wei		(PRIMARY AUTHOR - 50%)
 *					Richmond Choo Tze Yong	(PRIMARY AUTHOR - 50%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

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

		/**************************************************************
		*	the logic for player movement
		***************************************************************/
		void PlayerMovement(int& x, int& keypressed);

		/**************************************************************
		*	updates the meshes in runtime to update their mesh colours
		***************************************************************/
		void CombatMesh(int RGBcounter);

		/**************************************************************
		*	Renders and draws the player grid
		***************************************************************/
		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);


		/**************************************************************
		*	Frees all player meshes
		***************************************************************/	
		void FreePlayerMesh();

		/**************************************************************
		*	Frees the player meshes that updates the RGB colours
		*	in every frame
		***************************************************************/
		void FreePlayerMeshOnUpdate();

		/**************************************************************
		*	Initialises all the meshes in the init function
		***************************************************************/
		void MeshInit();

		/**************************************************************
		*	Renders and draws the stamina bar for the player
		***************************************************************/
		void StaminaRender(AEGfxTexture* staminapotion);

		/**************************************************************
		*	The logic for the stamina updates
		***************************************************************/
		void StaminaLogic(int const& keypressed);

		/**************************************************************
		*	The update for the player debuff states
		***************************************************************/
		void CheckandUpdatePlayerStatus();

		/**************************************************************
		*	A check on whether the player has levelled up or not
		***************************************************************/
		bool PlayerLevelUp();

		/**************************************************************
		*	Renders the player mesh with its respective x and y
		*	positions
		***************************************************************/
		void playerrender(AEGfxTexture* playertexture, AEGfxVertexList* playermesh);

		/**************************************************************
		*	The logic that cycles through the desired RGB colours
		***************************************************************/
		void RGBloop(int& RGBcounter);


		/**************************************************************
		*	Chooses the cells that damages you, and renders them
		***************************************************************/
		void GridCheck(bool EnemyAttackState, float timer, int& x);


		/**************************************************************
		*	Renders the player health with respect to the maxhealth
		*	Decreases with the health
		*	Prints essential texts on screens
		*	Prints which status debuff is currently affecting the player
		***************************************************************/
		void RenderPlayerHealth();


		/**************************************************************
		*	The update logic for the inventory system that consumes the
		*	potions currently on the player
		***************************************************************/
		void inventorylogic();


		/**************************************************************
		*	Renders and draws the inventory texts and textures in the
		*	combat
		***************************************************************/
		void inventoryrender();


		/**************************************************************
		*	FOR PRESENTATION PURPOSES ONLY:
		*	gives the player a lot of potiosn to be used, when
		*	showcasing the game
		***************************************************************/
		void godmode();

		/**************************************************************
		*	Transform the meshes for the frozen buttons
		***************************************************************/
		void FROZENbuttonlogic();

		/**************************************************************
		*	Rendering and drawing the frozen buttons
		*	and print texts on the screen
		***************************************************************/
		void FROZENbuttonrender();

		/**************************************************************
		*	A common function to unload textures and pointers
		***************************************************************/
		void unloadtextures();

		/**************************************************************
		*	The update function for the background texture
		***************************************************************/
		void Backgroundupdate();

		/**************************************************************
		*	The draw function to render the background texture
		***************************************************************/
		void Backgroundrender();
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

		/**************************************************************
		*	Chooses an enemytype for the player to encounter in the
		*	maze
		***************************************************************/
		void ChoosingEnemyType(float);

		/**************************************************************
		*	Loads the enemy meshes
		***************************************************************/
		void EnemyCombatMesh();
  
		/**************************************************************
		*	Renders and draws the enemy grids
		***************************************************************/
		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

		/**************************************************************
		*	Frees the enemy meshes
		***************************************************************/
		void FreeEnemyMesh();

		/**************************************************************
		*	Chooses the enemy states between idle and attacking
		***************************************************************/
		void UpdateEnemyState();

		/**************************************************************
		*	Renders and draws the enemy based on their different
		*	textures
		***************************************************************/
		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh);

		/**************************************************************
		*	Renders and draws the enemy health bar with respect to its
		*	maxhealth
		*	also prints out texts telling which enemy type it is
		***************************************************************/
		void RenderEnemyHealth();

		/**************************************************************
		*	Spawns the boss enemy by setting the relevant details and
		*	flags to the enemy struct
		***************************************************************/
		void SpawnBossEnemy();

		namespace {

			/**************************************************************
			*	checks for enemy type and their respective status effects
			*	on the player
			***************************************************************/
			void EnemyTypeCheckToApplyPlayerDebuff();

			/**************************************************************
			*	logic for player taking damage based on the different flags
			*	and grids the player is currently on
			***************************************************************/
			void EnemyAttackState();


			/**************************************************************
			*	resetting the states for the next attack sequence
			***************************************************************/
			void EnemyIdleState();
		}
	}
}

#endif // !PCH_HPP
