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
	};

	struct e_statsheet {
		int health;
		int damage;
		bool is_attacking;
	};

	c_statsheet* c_initialize();

	void CombatMesh(int RGBcounter);

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

	void FreePlayerMesh();

	int PlayerMovement(int& x, c_statsheet* player);

	void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh);

	int Playerdamage(c_statsheet* player, int SAFEGRID);

	void PlayerAttack(c_statsheet* Player, e_statsheet* Enemy);

	void RGBloop(int& RGBcounter);

	void GridCheck(int& counter, int& x, c_statsheet* Player, e_statsheet* Enemy);

	//void CameraShake(float camX, float camY);
}
