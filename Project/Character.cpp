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
		c_stats->is_attacking = false;
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

		AEGfxVertexAdd(0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
		AEGfxVertexAdd(-100.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
		AEGfxVertexAdd(-100.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
		AEGfxVertexAdd(0.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
		AEGfxVertexAdd(0.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

		Player5Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player5Grid, "Failed to create playermesh5!!");

		AEGfxMeshStart();

		//AEGfxVertexAdd(-215.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
		//AEGfxVertexAdd(-165.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
		//AEGfxVertexAdd(-165.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//CHARACTER MESH
		//AEGfxVertexAdd(-215.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
		//AEGfxVertexAdd(-215.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

		//AEGfxTriAdd(
		//	-215.0f, 25.0f, 0x00FF00FF, 0.0f, 1.0f,
		//	-215.0f, -25.0f, 0x00FFFF00, 0.0f, 1.0f,
		//	-165.0f, -25.0f, 0x0000FFFF, 1.0f, 0.0f);

		//AEGfxTriAdd(
		//	-215.0f, 25.0f, 0x00FF00FF, 1.0f, 1.0f,
		//	-165.0f, 25.0f, 0x00FFFF00, 1.0f, 0.0f,
		//	-165.0f, -25.0f, 0x00FFFFFF, 0.0f, 1.0f);


		AEGfxTriAdd(
			-215.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
			-165.0f, -25.0f, 0x00FFFF00, 1.0f, 1.0f,
			-215.0f, 25.0f, 0x0000FFFF, 0.0f, 0.0f);
		//x,y,colour,u,v


		AEGfxTriAdd(
			-165.0f, -25.0f, 0x00FFFFFF, 1.0f, 1.0f,
			-165.0f, 25.0f, 0x00FFFFFF, 1.0f, 0.0f,
			-215.0f, 25.0f, 0x00FFFFFF, 0.0f, 0.0f);


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


	int PlayerMovement(int& x, c_statsheet* player) {

		int keypressed = 0;
		x = 0;

		AEInputCheckTriggered(AEVK_D) ? x = 1 : x = x;
		AEInputCheckTriggered(AEVK_W) ? x = 2 : x = x;
		AEInputCheckTriggered(AEVK_A) ? x = 3 : x = x;
		AEInputCheckTriggered(AEVK_S) ? x = 4 : x = x;


		switch (x) {

		case 1:	//ATTACK GRID
			player->positionID = 1;
			player->positionX = 145.0f;
			player->positionY = 0.0f;
			keypressed = 1;
			player->is_attacking = true;
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



	void playerrender(AEGfxTexture* playertexture, c_statsheet* player, AEGfxVertexList* playermesh) {

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 1
		AEGfxSetPosition(player->positionX, player->positionY);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(playertexture, 1.0f, 1.0f);

		AEGfxMeshDraw(playermesh, AE_GFX_MDM_TRIANGLES);
	}



	int Playerdamage(c_statsheet* Player, int SAFEGRID) {
		if (Player->positionID != SAFEGRID) {
			Player->health -= 1;
			std::cout << "the player's health is: " << Player->health << std::endl;
			return  1;
		}
		else {
			return 0;
		}
	}


	void PlayerAttack(c_statsheet* Player, bool enemy_isattacking, int& enemyhealth) {

		if (Player->is_attacking == true && enemy_isattacking == false) {
			enemyhealth -= Player->damage;
			std::cout << "enemy health: " << enemyhealth << "\n";
		}

		Player->is_attacking = false;
	}


	//void CameraShake(float camX, float camY) {

	//	//AEGfxGetCamPosition(&camX, &camY);

	//	//for (int i = 0; i < 10; ++i) {

	//		//if (i % 2 == 0) {
	//			AEGfxSetCamPosition(camX + 2, camY + 2);
	//		//}
	//		//else {
	//			AEGfxSetCamPosition(camX - 2, camY - 2);
	//		//}
	//	//}
	//	
	//	/*AEGfxSetCamPosition(camX - 2, camY - 2);
	//	AEGfxSetCamPosition(camX + 2, camY + 2);*/
	//}

}