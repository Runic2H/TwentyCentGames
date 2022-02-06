#include "pch.hpp"



	AEGfxVertexList* Player1Grid = 0;
	AEGfxVertexList* Player2Grid = 0;
	AEGfxVertexList* Player3Grid = 0;
	AEGfxVertexList* Player4Grid = 0;
	AEGfxVertexList* Player5Grid = 0;
	AEGfxVertexList* PlayerMesh = 0;


	AEGfxVertexList* EnemyGridIdle = 0;
	AEGfxVertexList* EnemyGridAttack = 0;
	AEGfxVertexList* EnemyMesh = 0;



		E_StatSheet* EnemyInitialize()
		{
			E_StatSheet* E_Stats = new E_StatSheet;
			E_Stats->health = 100;
			E_Stats->damage = 10;
			E_Stats->EnemyState = IDLE;
			E_Stats->EnemyCD = 5.0f;
			E_Stats->positionX = 0.0f;
			E_Stats->positionY = 0.0f;
			E_Stats->is_attacking = false;
			E_Stats->AttackCD = 0.45f;
			return E_Stats;
		}

		c_statsheet* c_initialize()
	{
		c_statsheet* c_stats = new c_statsheet;
		c_stats->health = 100;								//health
		c_stats->positionID = 1;							//starting grid
		c_stats->SAFEGRID = 1;								//starting SAFEGRID pos
		c_stats->damage = 10;								//damage
		c_stats->playerCD = 5;								//Cooldown for attack and movement
		c_stats->is_dmgtaken = false;						//to implement visual animations in future
		c_stats->is_attacking = false;						//for enemy damage checks
		c_stats->positionX = 0.0f;
		c_stats->positionY = 0.0f;
		return c_stats;
	}



	void CombatMesh(int RGBcounter)
	{

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -60.0f, RGBcounter, 1.0f, 1.0f);				//PLAYERGRID 4 BOTTOM
		AEGfxVertexAdd(-240.0f, -60.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);

		Player4Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player4Grid, "Failed to create playermesh1!!");

		//

		AEGfxMeshStart();

		AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
		AEGfxVertexAdd(-250.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-250.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
		AEGfxVertexAdd(-350.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
		AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

		Player3Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player3Grid, "Failed to create playermesh2!!");

		// 

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 160.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 60.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
		AEGfxVertexAdd(-240.0f, 60.0f, RGBcounter, 1.0f, 0.0f);
		AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);

		Player2Grid = AEGfxMeshEnd();
		AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh3!!");

		//

		AEGfxMeshStart();

		AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
		AEGfxVertexAdd(-140.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 1 MIDDLE
		AEGfxVertexAdd(-240.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
		AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

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

		AEGfxTriAdd(
			-215.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
			-165.0f, -25.0f, 0x00FFFF00, 1.0f, 1.0f,
			-215.0f, 25.0f, 0x0000FFFF, 0.0f, 0.0f);
		//x,y,colour,u,v
																			//CHARACTER OBJECT
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

		AEInputCheckTriggered(AEVK_W) ? x = 2 : x = x;	//ID Should be 1
		AEInputCheckTriggered(AEVK_A) ? x = 3 : x = x;	//ID Should be 2
		AEInputCheckTriggered(AEVK_S) ? x = 4 : x = x;	//ID Should be 3
		AEInputCheckTriggered(AEVK_D) ? x = 5 : x = x;	//ID Should be 4

		//ORIGIN ID should be 0 (My randomizer will be easier to ignore 0 then i can just randomize between 1-3)


		switch (x) {

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


		case 5:	//ATTACK GRID
			player->positionID = 5;
			player->positionX = 145.0f;
			player->positionY = 0.0f;
			player->is_attacking = true;
			keypressed = 1;
			break;
		}

		if (player->positionX == 0.0f && player->positionY == 0.0f) {
			player->positionID = 1;
		}

		return keypressed;
	}



	void playerrender(c_statsheet* player, AEGfxVertexList* playermesh) {

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(player->positionX, player->positionY);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(NULL, 1.0f, 1.0f);

		AEGfxMeshDraw(playermesh, AE_GFX_MDM_TRIANGLES);
	}





	void RGBloop(int& RGBcounter) {
		if (RGBcounter <= 16777215)
		{
			RGBcounter += 500;
			(RGBcounter > 16766215) ? RGBcounter = 16384000 : RGBcounter = RGBcounter;
		}
	}



	void GridCheck(int& counter, int& y, c_statsheet* Player, E_StatSheet* Enemy) {

		++counter;
		//std::cout << counter << "\n";


		if (counter > 100) {

			switch (y)
			{

			case 1:
				//SAFEGRID 1
				RenderPlayerGrid(Player2Grid);
				RenderPlayerGrid(Player3Grid);
				RenderPlayerGrid(Player4Grid);
				Player->SAFEGRID = 1;
				break;

			case 2:
				//SAFEGRID 2
				RenderPlayerGrid(Player1Grid);
				RenderPlayerGrid(Player3Grid);
				RenderPlayerGrid(Player4Grid);
				Player->SAFEGRID = 2;
				break;

			case 3:
				//SAFEGRID 3
				RenderPlayerGrid(Player1Grid);
				RenderPlayerGrid(Player2Grid);
				RenderPlayerGrid(Player4Grid);
				Player->SAFEGRID = 3;
				break;

			case 4:
				//SAFEGRID 4
				RenderPlayerGrid(Player1Grid);
				RenderPlayerGrid(Player2Grid);
				RenderPlayerGrid(Player3Grid);
				Player->SAFEGRID = 4;
				break;
			}

			if (counter > 150 && counter < 152) {
				if (Player->SAFEGRID != Player->positionID) {
					Player->health -= Enemy->damage;
					std::cout << "OUCH!!" << Player->health << "\n";
				}
			}

			else if (counter >= 152) {
				y = (int)((AERandFloat() * 10) / 2);
				counter = 0;

			}
		}
	}



		void EnemyAttackState(E_StatSheet * Enemy, c_statsheet * Player)
		{
			Enemy->EnemyState = ATTACK;
			Enemy->is_attacking = true;
			Player->SAFEGRID = (rand() % 3) + 1;
			if (Enemy->positionX != 150.0f)
			{
				Enemy->positionX += 10.0f;
			}
			if (Enemy->EnemyState == ATTACK && Enemy->is_attacking == true)
			{
				Enemy->AttackCD -= DT;
				if (Enemy->AttackCD <= 0.0f)
				{
					if (Player->positionID != Player->SAFEGRID)
					{
						Player->health -= Enemy->damage;
						std::cout << Player->health << "Player" << "\n";
					}
					Enemy->AttackCD = 0.45f;
					Enemy->EnemyCD = AERandFloat() * 5.0f;
				}
			}
		}

		void EnemyIdleState(E_StatSheet * Enemy, c_statsheet * Player)
		{
			Enemy->EnemyState = IDLE;
			Enemy->is_attacking = false;
			Enemy->positionX = 0.0f;
			Enemy->EnemyCD -= DT;
			if (Enemy->EnemyState == IDLE && Enemy->is_attacking == false)
			{
				if (Player->is_attacking == true)
				{
					Enemy->health -= Player->damage;
					Player->is_attacking = false;
					std::cout << Enemy->health << "\n";
				}
			}
		}

		void UpdateEnemyState(E_StatSheet* Enemy, c_statsheet* Player)
		{
			if (Enemy->EnemyCD <= 0.0f)
			{
				EnemyAttackState(Enemy, Player);
			}
			else
			{
				EnemyIdleState(Enemy, Player);
			}
		}

		void EnemyCombatMesh()
		{
			AEGfxMeshStart();

			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(150.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(150.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID IDLE
			AEGfxVertexAdd(50.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridIdle = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridIdle, "Failed to create enemygrididle!!");

			AEGfxMeshStart();

			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(300.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(300.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID ATTACK
			AEGfxVertexAdd(200.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridAttack = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridAttack, "Failed to create enemygrididle!!");

			AEGfxMeshStart();

			AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(125.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(125.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//ENEMY MESH
			AEGfxVertexAdd(75.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

			EnemyMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyMesh, "Failed to create character!!");
		}

		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			// Set position for object 1
			AEGfxSetPosition(0.0f, 0.0f);
			// No texture for object 1
			AEGfxTextureSet(NULL, 0, 0);

			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
		}

		void FreeEnemyMesh()
		{
			AEGfxMeshFree(EnemyGridIdle);
			AEGfxMeshFree(EnemyGridAttack);
		}


		void RenderEnemy(AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			// Set position for object 1
			AEGfxSetPosition(Enemy->positionX, Enemy->positionY);
			// No texture for object 1
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
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

//int Playerdamage(c_statsheet* Player, int SAFEGRID) {

//	if (Player->positionID != SAFEGRID) {
//		Player->health -= 1;
//		std::cout << "the player's health is: " << Player->health << std::endl;
//		return  1;
//	}
//	else {
//		return 0;
//	}
//}


////NOT NEEDED
//void PlayerAttack(c_statsheet* Player, e_statsheet* Enemy) {

//	if (Player->is_attacking == true && Enemy->is_attacking == false) {
//		Enemy->health -= Player->damage;
//		std::cout << "enemy health: " << Enemy->health << "\n";
//	}
//	Player->is_attacking = false;

//}