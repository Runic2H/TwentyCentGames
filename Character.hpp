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


	struct c_statsheet
	{
		int positionID;
		float positionX;
		float positionY;
		int health;
		int damage;
		bool is_dmgtaken;
		int playerCD;
	};

	struct c_movegrid
	{
		bool is_attacking;
		bool is_player;
		bool enemy_attakcing;
	};

	c_statsheet* c_initialize();

	void CombatMesh();

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

	void FreePlayerMesh();

	int PlayerMovement(int x, c_statsheet* player);

	void playerrender(c_statsheet* player, AEGfxVertexList* playermesh);
}
