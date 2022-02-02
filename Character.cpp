#include "pch.hpp"

namespace Character
{

	AEGfxVertexList* Player1Grid = 0;
	AEGfxVertexList* Player2Grid = 0;
	AEGfxVertexList* Player3Grid = 0;
	AEGfxVertexList* Player4Grid = 0;
	AEGfxVertexList* Player5Grid = 0;
	AEGfxVertexList* PlayerMesh = 0;
	
	c_statsheet* c_initialize()
	{
		c_statsheet* c_stats = new c_statsheet;
		c_stats->health = 100;
		c_stats->positionID = 1; //Used for the mesh position?
		c_stats->damage = 10;
		c_stats->playerCD = 5; //Cooldown for attack and movement
		c_stats->is_dmgtaken = false;
		c_stats->positionX = 0.0f;
		c_stats->positionY = 0.0f;
		return c_stats;
	}

	void CombatMesh()
	{

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, -160.0f, 0xFF0000, 0.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -160.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -60.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 4 BOTTOM
		AEGfxVertexAdd(-240.0f, -60.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(-240.0f, -160.0f, 0xFF0000, 0.0f, 1.0f);

		Player4Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player4Grid, "Failed to create playermesh1!!");

		//

		AEGfxMeshStart();

		AEGfxVertexAdd(-350.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
		AEGfxVertexAdd(-250.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(-250.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
		AEGfxVertexAdd(-350.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(-350.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

		Player3Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player3Grid, "Failed to create playermesh2!!");

		// 

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, 160.0f, 0xFF0000, 0.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 160.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 60.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
		AEGfxVertexAdd(-240.0f, 60.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(-240.0f, 160.0f, 0xFF0000, 0.0f, 1.0f);

		Player2Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh3!!");

		//

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, -50.0f, 0x00FF00FF, 0.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -50.0f, 0x00FFFF00, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 50.0f, 0x0000FFFF, 0.0f, 0.0f);				//PLAYERGRID 1 MIDDLE
		AEGfxVertexAdd(-240.0f, 50.0f, 0x00FF00FF, 1.0f, 0.0f);
		AEGfxVertexAdd(-240.0f, -50.0f, 0x00FFF0FF, 0.0f, 1.0f);

		Player1Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player1Grid, "Failed to create playermesh4!!");

		AEGfxMeshStart();

		AEGfxVertexAdd( 0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
		AEGfxVertexAdd( -100.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd( -100.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
		AEGfxVertexAdd( 0.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd( 0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

		Player5Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player5Grid, "Failed to create playermesh5!!");

		AEGfxMeshStart();

		AEGfxVertexAdd(-215.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
		AEGfxVertexAdd(-165.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(-165.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//CHARACTER MESH
		AEGfxVertexAdd(-215.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(-215.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

		PlayerMesh = AEGfxMeshEnd();
		AE_ASSERT_MESG(PlayerMesh, "Failed to create character!!");
	}

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(0.0f, 0.0f);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);

		AEGfxMeshDraw(PlayerMesh, AE_GFX_MDM_LINES_STRIP);
	}

	void FreePlayerMesh()
	{
		AEGfxMeshFree(Player1Grid);
		AEGfxMeshFree(Player2Grid);
		AEGfxMeshFree(Player3Grid);
		AEGfxMeshFree(Player4Grid);
		AEGfxMeshFree(Player5Grid);
		AEGfxMeshFree(PlayerMesh);
	}


	int PlayerMovement(int x, c_statsheet* player) {

		int keypressed = 2;

	switch (x) {

		case 1:
			player->positionID = 1;
			player->positionX = 0.0f;
			player->positionY = 0.0f;
			keypressed = 1;
			break;

		case 2:
			player->positionID = 2;
			player->positionX = 0.0f;
			player->positionY = 110.0f;
			keypressed = 1;
			break;

		case 3:
			player->positionID = 3;
			player->positionX = -110.0f;
			player->positionY = 0.0f;
			keypressed = 1;
			break;

		case 4:
			player->positionID = 4;
			player->positionX = 0.0f;
			player->positionY = -110.0f;
			keypressed = 1;
			break;
	}

		return keypressed;
}




	void playerrender(c_statsheet* player, AEGfxVertexList* playermesh) {

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(player->positionX, player->positionY);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);

		AEGfxMeshDraw(playermesh, AE_GFX_MDM_LINES_STRIP);
	}
}