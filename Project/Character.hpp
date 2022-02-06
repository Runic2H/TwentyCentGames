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

	//void CameraShake(float camX, float camY);
}
