#pragma once
#include "pch.h"

namespace Character
{
	AEGfxVertexList* GridStart = 0;
	//AEGfxVertexList* GridTop = 0;
	//AEGfxVertexList* GridBottom = 0;
	//AEGfxVertexList* GridBack = 0;
	//AEGfxVertexList* GridFront = 0;

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

	void renderGrid();

	//void renderPlayer();
}
