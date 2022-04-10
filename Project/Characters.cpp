/**************************************************************************
 * 	File name	:	Characters.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Elton Teo Zhe Wei		(PRIMARY AUTHOR - 50%)
 *					Richmond Choo Tze Yong	(PRIMARY AUTHOR - 50%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

/************************************************************
*			GLOBAL DECLARATIONS
************************************************************/


namespace Characters
{
	/******************************************************
	*
	* PLAYER NAMESPACE
	*
	*******************************************************/
	namespace Character
	{
		
		/************************************************************
		*			CHARACTER NAMESPACE DECLARATIONS
		************************************************************/
		item* rightbutton;
		item* leftbutton;
		item* combat_bg;
		
		AEGfxVertexList* Player1Grid = 0;	//ORIGN
		AEGfxVertexList* Player2Grid = 0;	//TOP
		AEGfxVertexList* Player3Grid = 0;	//BACK
		AEGfxVertexList* Player4Grid = 0;	//BOTTOM
		AEGfxVertexList* Player5Grid = 0;	//ATTACK
		AEGfxVertexList* PlayerMesh = 0;

		AEGfxVertexList* playermaxhealth = 0;	//PLAYER HEALTH MESH
		AEGfxVertexList* playercurrhealth = 0;	//PLAYER HEALTH MESH
		AEGfxVertexList* playerstamina = 0;		//PLAYER STAMINA MESH


		/**************************************************************
		*	updates the meshes in runtime to update their mesh colours
		***************************************************************/
		void CombatMesh(int RGBcounter)
		{
			FreePlayerMeshOnUpdate();

			AEGfxMeshStart();

			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 1.0f);			//PLAYERGRID 4 BOTTOM
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);


			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);    //1st
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 1.0f);  //2nd          //PLAYERGRID 4 BOTTOM
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 1.0f); //3rd
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f); //4th
			//AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, -60.0f, RGBcounter, 1.0f, 1.0f);			//PLAYERGRID 4 BOTTOM
			//AEGfxVertexAdd(-240.0f, -60.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);

			Player4Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player4Grid, "Failed to create playermesh4!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4375), -(float)(AEGetWindowHeight()/12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3125), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3125), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4375), (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4375), -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);


			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4375), -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3125), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4375), (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3125), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			//AEGfxVertexAdd(-250.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-250.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
			//AEGfxVertexAdd(-350.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			//AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player3Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player3Grid, "Failed to create playermesh3!!");

			// 

			AEGfxMeshStart();

			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() * 4/15), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() * 0.1), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 0.0f, 1.0f);


			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() * 0.1), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() * 0.1), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() * 4 / 15), RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, 160.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, 60.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
			//AEGfxVertexAdd(-240.0f, 60.0f, RGBcounter, 1.0f, 0.0f);
			//AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);

			Player2Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh2!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight()/12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);                //PLAYERGRID 1 MIDDLE
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);


			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);                //PLAYERGRID 1 MIDDLE
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.3), (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.175), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);

			//AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-140.0f, 50.0f, RGBcounter, 0.0f, 0.0f);                //PLAYERGRID 1 MIDDLE
			//AEGfxVertexAdd(-240.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			//AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player1Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player1Grid, "Failed to create playermesh1!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(0.0f, -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth()/8), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() / 8), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
			AEGfxVertexAdd(0.0f, (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(0.0f, -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);


			AEGfxVertexAdd(0.0f, -(float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() / 8), (float)(AEGetWindowHeight() / 12), RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
			AEGfxVertexAdd(0.0f, (float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() / 8), -(float)(AEGetWindowHeight() / 12), RGBcounter, 1.0f, 1.0f);

			//AEGfxVertexAdd(0.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			//AEGfxVertexAdd(-100.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			//AEGfxVertexAdd(-100.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
			//AEGfxVertexAdd(0.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			//AEGfxVertexAdd(0.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player5Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh2!!");
		}


		/**************************************************************
		*	Initialises all the meshes in the init function once in the
		*	whole function
		***************************************************************/
		void MeshInit() {

			rightbutton = new item;
			leftbutton = new item;
			combat_bg = new item;

			// THE MAX PLAYER HEALTH
			AEGfxMeshStart();
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 29/60), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight() * 53/120), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);


			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);

			//AEGfxVertexAdd(-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(-230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(-230.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(-390.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			playermaxhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(playermaxhealth, "Failed to create playerhealth!!");

			//

			AEGfxMeshStart();
			AEGfxTriAdd(
				-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
				0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
				-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
			AEGfxTriAdd(
				0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
				0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
				-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

			rightbutton->pMesh
				= leftbutton->pMesh
				= combat_bg->pMesh
				= AEGfxMeshEnd();
			AE_ASSERT_MESG(rightbutton->pMesh, "Failed to create pause meshes!!\n");

		
			rightbutton->pTexture = AEGfxTextureLoad("Images/rightbutton.png");
			leftbutton->pTexture = AEGfxTextureLoad("Images/leftbutton.png");
			combat_bg->pTexture = AEGfxTextureLoad("Images/combatbackground.png");
	
			//

			//CHARACTER OBJECT
			AEGfxMeshStart();
			AEGfxTriAdd(
				-(float)(AEGetWindowWidth()*0.275), -(float)(AEGetWindowHeight() * 0.05), 0x00FF00FF, 0.0f, 1.0f,
				-(float)(AEGetWindowWidth()*0.2), -(float)(AEGetWindowHeight() * 0.05), 0x00FFFF00, 1.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.275), (float)(AEGetWindowHeight() * 0.05), 0x0000FFFF, 0.0f, 0.0f);
			AEGfxTriAdd(
				-(float)(AEGetWindowWidth() * 0.2), -(float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 1.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.2), (float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 1.0f, 0.0f,
				-(float)(AEGetWindowWidth() * 0.275), (float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 0.0f, 0.0f);

			//AEGfxTriAdd(
			//	-220.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
			//	-160.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
			//	-220.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);
			//AEGfxTriAdd(
			//	-160.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
			//	-160.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
			//	-220.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

			PlayerMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(PlayerMesh, "Failed to create character!!");

			//

			AEGfxMeshStart();
			AEGfxTriAdd(
				-(float)(AEGetWindowHeight()/30), -(float)(AEGetWindowHeight() / 30), 0x00FF00FF, 0.0f, 1.0f,
				(float)(AEGetWindowHeight() / 30), -(float)(AEGetWindowHeight() / 30), 0x00FFFF00, 1.0f, 1.0f,
				(float)(AEGetWindowHeight() / 30), (float)(AEGetWindowHeight() / 30), 0x0000FFFF, 1.0f, 0.0f);

			AEGfxTriAdd(
				-(float)(AEGetWindowHeight() / 30), -(float)(AEGetWindowHeight() / 30), 0x00FFFFFF, 0.0f, 1.0f,
				-(float)(AEGetWindowHeight() / 30), (float)(AEGetWindowHeight() / 30), 0x00FFFFFF, 0.0f, 0.0f,
				(float)(AEGetWindowHeight() / 30), (float)(AEGetWindowHeight() / 30), 0x00FFFFFF, 1.0f, 0.0f);

			playerstamina = AEGfxMeshEnd();
			AE_ASSERT_MESG(playerstamina, "Failed to create stamina mesh!!");
		}
		

		/**************************************************************
		*	The logic for the stamina updates
		***************************************************************/
		void StaminaLogic(int const& keypressed)
		{
			//std::cout << playerstats->staminacount << "\n";
			//static int flagset = 0;

			if (playerstats->staminacount < playerstats->staminamax) {
				playerstats->staminaCD -= DT;

				if (playerstats->staminaCD < 0) {

					if (playerstats->status == FROSTED)
					{
						playerstats->staminaCD = 1.35f;
					}
					else
					{
						playerstats->staminaCD = playerstats->resetCD;	// resets the playerCD
					}
					++playerstats->staminacount;
				}
			}

			if (keypressed == 1) {
				--playerstats->staminacount;
			}
		}


		/**************************************************************
		*	The update function for the background texture
		***************************************************************/
		void Backgroundupdate() {

			AEMtx33 scale, rot, trans, buffer;

			AEMtx33Scale(&scale, 950.0f, 600.0f);
			AEMtx33Rot(&rot, 0.0f);
			AEMtx33Concat(&buffer, &scale, &rot);

			AEMtx33Trans(&trans, 0.0f, 0.0f);
			AEMtx33Concat(&combat_bg->transform, &trans, &buffer);
		}


		/**************************************************************
		*	The draw function to render the background texture
		***************************************************************/
		void Backgroundrender() {

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			AEGfxSetTransform(combat_bg->transform.m);
			AEGfxSetTransparency(0.5f);
			AEGfxTextureSet(combat_bg->pTexture, 0, 0);
			AEGfxMeshDraw(combat_bg->pMesh, AE_GFX_MDM_TRIANGLES);
		}

		/**************************************************************
		*	Transform the meshes for the frozen buttons
		***************************************************************/
		void FROZENbuttonlogic() {

			leftbutton->itemcounter = rightbutton->itemcounter = 0.5f;
			AEMtx33 scale, rot, trans, buffer;

			AEMtx33Scale(&scale, 50.0f, 50.0f);
			AEMtx33Rot(&rot, 0.0f);
			AEMtx33Concat(&buffer, &scale, &rot);

			AEMtx33Trans(&trans, -150.0f, 120.0f);
			AEMtx33Concat(&leftbutton->transform, &trans, &buffer);

			AEMtx33Trans(&trans, 150.0f, 120.0f);
			AEMtx33Concat(&rightbutton->transform, &trans, &buffer);

			if (AEInputCheckTriggered(AEVK_Q)) {
				rightbutton->itemcounter = 1.0f;
			}
			if (AEInputCheckTriggered(AEVK_E)) {
				leftbutton->itemcounter = 1.0f;
			}
		}

		/**************************************************************
		*	Rendering and drawing the frozen buttons
		*	and print texts on the screen
		***************************************************************/
		void FROZENbuttonrender() {

			char str[35];
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			AEGfxSetTransform(leftbutton->transform.m);
			AEGfxSetTransparency(leftbutton->itemcounter);
			AEGfxTextureSet(leftbutton->pTexture, 0, 0);
			AEGfxMeshDraw(leftbutton->pMesh, AE_GFX_MDM_TRIANGLES);

			sprintf_s(str, "Q");
			AEGfxPrint(fontLarge, str, -0.55f, 0.35f, 0.6f, 0.0f, 1.0f, 1.0f);

			AEGfxSetTransform(rightbutton->transform.m);
			AEGfxSetTransparency(rightbutton->itemcounter);
			AEGfxTextureSet(rightbutton->pTexture, 0, 0);
			AEGfxMeshDraw(rightbutton->pMesh, AE_GFX_MDM_TRIANGLES);

			sprintf_s(str, "E");
			AEGfxPrint(fontLarge, str, 0.49f, 0.35f, 0.6f, 0.0f, 1.0f, 1.0f);

			char strBuffer[35];
			char strBufferStatus[35];

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxSetTransparency(1.0f);

			sprintf_s(strBuffer, "FROZEN");
			sprintf_s(strBufferStatus, "%d", playerstats->statuscounter);
			AEGfxPrint(fontLarge, strBuffer, -0.19f, 0.35f, 0.6f, 0.0f, 1.0f, 1.0f);
			AEGfxPrint(fontLarge, strBufferStatus, -0.04f, 0.55f, 0.6f, 0.0f, 1.0f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}


		/**************************************************************
		*	Renders and draws the stamina bar for the player
		***************************************************************/
		void StaminaRender(AEGfxTexture* staminapotion)
		{
			for (int i{ 0 }; i < playerstats->staminacount; ++i) {

				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetPosition(playerstats->staminaX + (i * 30), -(float)(AEGetWindowHeight()*0.45));
				//AEGfxSetPosition(playerstats->staminaX + (i * 30), -270.0f);
				AEGfxTextureSet(staminapotion, 0, 0);
				AEGfxSetTintColor(1, 1, 1, 1);
				AEGfxSetTransparency(1);
				AEGfxMeshDraw(playerstamina, AE_GFX_MDM_TRIANGLES);
			}
		}

		/**************************************************************
		*	The update logic for the inventory system that consumes the
		*	potions currently on the player
		***************************************************************/
		void inventorylogic() {

			if (AEInputCheckTriggered(AEVK_1)) {
				if (playerinventory->defencepotion.itemcounter > 0) {
					--playerinventory->defencepotion.itemcounter;
					enemystats->damage *= 0.7f;
					portion_Audio();
				}
			}

			if (AEInputCheckTriggered(AEVK_2)) {
				if (playerinventory->healthpotion.itemcounter > 0) {
					--playerinventory->healthpotion.itemcounter;
					playerstats->health += 50;

					if (playerstats->health > playerstats->maxhealth) {
						playerstats->health = playerstats->maxhealth;
						}
					portion_Audio();
				}
			}

			if (AEInputCheckTriggered(AEVK_3)) {
				if (playerinventory->staminapotion.itemcounter > 0) {
					--playerinventory->staminapotion.itemcounter;
					playerstats->resetCD *= 0.7f;
					portion_Audio();
				}
			}
		}


		/**************************************************************
		*	Renders and draws the inventory texts and textures in the
		*	combat
		***************************************************************/
		void inventoryrender() {

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(1, 1, 1, 1);
			AEGfxSetTransparency(1);

			AEGfxSetTransform(playerinventory->defencepotion.transform.m);
			AEGfxTextureSet(playerinventory->defencepotion.pTexture, 0, 0);
			AEGfxSetTransparency(1);
			AEGfxMeshDraw(playerinventory->defencepotion.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(playerinventory->healthpotion.transform.m);
			AEGfxTextureSet(playerinventory->healthpotion.pTexture, 0, 0);
			AEGfxSetTransparency(1);
			AEGfxMeshDraw(playerinventory->healthpotion.pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxSetTransform(playerinventory->staminapotion.transform.m);
			AEGfxTextureSet(playerinventory->staminapotion.pTexture, 0, 0);
			AEGfxSetTransparency(1);
			AEGfxMeshDraw(playerinventory->staminapotion.pMesh, AE_GFX_MDM_TRIANGLES);


			char defencestr[20], staminastr[20], healthstr[20];
			sprintf_s(defencestr, "%0.0f", playerinventory->defencepotion.itemcounter);
			sprintf_s(staminastr, "%0.0f", playerinventory->staminapotion.itemcounter);
			sprintf_s(healthstr, "%0.0f", playerinventory->healthpotion.itemcounter);

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);

			
			if (playerinventory->healthpotion.itemcounter == 0) {	// print red when count = 0
				AEGfxPrint(fontId, healthstr, 0.03f, -0.7f, 1.14f, 1.f, 0.f, 0.f);
			}
			else {
				AEGfxPrint(fontId, healthstr, 0.03f, -0.7f, 1.14f, 1.f, 1.f, 1.f);
			}


			if (playerinventory->defencepotion.itemcounter == 0) {	// print red when count = 0
				AEGfxPrint(fontId, defencestr, -0.15f, -0.7f, 1.14f, 1.f, 0.f, 0.f);
			}
			else {
				AEGfxPrint(fontId, defencestr, -0.15f, -0.7f, 1.14f, 1.f, 1.f, 1.f);
			}


			if (playerinventory->staminapotion.itemcounter == 0) {	// print red when count = 0
				AEGfxPrint(fontId, staminastr, 0.2f, -0.7f, 1.14f, 1.f, 0.f, 0.f);
			}
			else {
				AEGfxPrint(fontId, staminastr, 0.2f, -0.7f, 1.14f, 1.f, 1.f, 1.f);
			}

			// reusing char[] tp print out the names
			sprintf_s(defencestr, "1");
			sprintf_s(healthstr, "2");
			sprintf_s(staminastr, "3");
			AEGfxPrint(fontId, defencestr, -0.25f, -0.57f, 0.9f, 1.0f, 1.0f, 1.0f);
			AEGfxPrint(fontId, healthstr, -0.08f, -0.57f, 0.9f, 1.0f, 1.0f, 1.0f);
			AEGfxPrint(fontId, staminastr, 0.09f, -0.57f, 0.9f, 1.0f, 1.0f, 1.0f);

			AEGfxSetBlendMode(AE_GFX_BM_NONE);
			// TO ADD: POTION COUNT
		}


		/**************************************************************
		*	Renders and draws the player grid
		***************************************************************/
		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(PlayerMesh, AE_GFX_MDM_LINES_STRIP);
		}


		/**************************************************************
		*	Frees the player meshes that updates the RGB colours
		*	in every frame
		***************************************************************/
		void FreePlayerMeshOnUpdate() {

			if (Player1Grid != nullptr) {
				AEGfxMeshFree(Player1Grid);
				Player1Grid = nullptr;
			}

			if (Player2Grid != nullptr) {
				AEGfxMeshFree(Player2Grid);
				Player2Grid = nullptr;
			}

			if (Player3Grid != nullptr) {
				AEGfxMeshFree(Player3Grid);
				Player3Grid = nullptr;
			}

			if (Player4Grid != nullptr) {
				AEGfxMeshFree(Player4Grid);
				Player4Grid = nullptr;
			}

			if (Player5Grid != nullptr) {
				AEGfxMeshFree(Player5Grid);
				Player5Grid = nullptr;
			}
		}

		/**************************************************************
		*	Frees all player meshes
		***************************************************************/
		void FreePlayerMesh()
		{
			if (PlayerMesh != nullptr) {
				AEGfxMeshFree(PlayerMesh);
				PlayerMesh = nullptr;
			}

			if (playermaxhealth != nullptr) {
				AEGfxMeshFree(playermaxhealth);
				playermaxhealth = nullptr;
			}

			if (playercurrhealth != nullptr) {
				AEGfxMeshFree(playercurrhealth);
				playercurrhealth = nullptr;
			}

			if (playerstamina != nullptr) {
				AEGfxMeshFree(playerstamina);
				playerstamina = nullptr;
			}

			if (Player1Grid != nullptr) {
				AEGfxMeshFree(Player1Grid);
				Player1Grid = nullptr;
			}

			if (Player2Grid != nullptr) {
				AEGfxMeshFree(Player2Grid);
				Player2Grid = nullptr;
			}

			if (Player3Grid != nullptr) {
				AEGfxMeshFree(Player3Grid);
				Player3Grid = nullptr;
			}

			if (Player4Grid != nullptr) {
				AEGfxMeshFree(Player4Grid);
				Player4Grid = nullptr;
			}

			if (Player5Grid != nullptr) {
				AEGfxMeshFree(Player5Grid);
				Player5Grid = nullptr;
			}

			if (rightbutton->pMesh != nullptr) {
				AEGfxMeshFree(rightbutton->pMesh);
				rightbutton->pMesh = nullptr;
				leftbutton->pMesh = nullptr;
			}
			
		}

		/**************************************************************
		*	A common function to unload textures and pointers
		***************************************************************/
		void unloadtextures() {

			AEGfxTextureUnload(rightbutton->pTexture);
			AEGfxTextureUnload(leftbutton->pTexture);
			AEGfxTextureUnload(combat_bg->pTexture);

			delete rightbutton;
			delete leftbutton;
			delete combat_bg;
		}


		/**************************************************************
		*	the logic for player movement
		***************************************************************/
		void PlayerMovement(int& x, int& keypressed) {

			x = 0;

			if (playerstats->staminacount > 0 && playerstats->status != FROZEN)
			{
				AEInputCheckTriggered(AEVK_W) ? x = TOP : x = x;	//ID Should be 1
				AEInputCheckTriggered(AEVK_A) ? x = BACK : x = x;	//ID Should be 2
				AEInputCheckTriggered(AEVK_S) ? x = DOWN : x = x;	//ID Should be 3
				AEInputCheckTriggered(AEVK_D) ? x = ATTACK : x = x;	//ID Should be 4

				playerstats->movementdt = 0.50f;

				switch (x) {

				case ATTACK:	//ATTACK GRID
					playerstats->positionID = ATTACK;
					playerstats->positionX = 145.0f;
					playerstats->positionY = 0.0f;
					playerstats->is_attacking = true;
					keypressed = 1;
					slashing2_Audio();
					break;

				case TOP:
					playerstats->positionID = TOP;
					playerstats->positionX = 0.0f;
					playerstats->positionY = 110.0f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;

				case BACK:
					playerstats->positionID = BACK;
					playerstats->positionX = -110.0f;
					playerstats->positionY = 0.8f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;

				case DOWN:
					playerstats->positionID = DOWN;
					playerstats->positionX = 0.0f;
					playerstats->positionY = -110.0f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;
				}
			}
			if (playerstats->status == FROZEN)
			{
				if (playerstats->statuscounter == 0)
				{
					playerstats->status = NEUTRAL;
				}
				else
				{
					for (int i{ 0 }; i < 20; ++i) {
						particleInstCreate(AERandFloat() * 10, playerstats->positionX - 190, playerstats->positionY - 20, particleENEMYFROST);
					}

					FROZENbuttonlogic();
					FROZENbuttonrender();

					if (AEInputCheckTriggered(AEVK_Q) || AEInputCheckTriggered(AEVK_E))
					{
						--playerstats->statuscounter;
					}
				}
			}

			if (playerstats->positionX == 0.0f && playerstats->positionY == 0.0f) {
				playerstats->positionID = ORIGIN;
				playerstats->is_attacking = false;
			}
		}

		/**************************************************************
		*	The update for the player debuff states
		***************************************************************/
		void CheckandUpdatePlayerStatus()
		{
			if (playerstats->debuffcounter > 0)
			{
				playerstats->debuffcounter -= DT;
			}
			if (playerstats->status == FROSTED)
			{
				playerstats->statuscounter = 10;
				if (playerstats->debuffcounter <= 0)
				{
					playerstats->status = NEUTRAL;
					playerstats->statuscounter = 0;
				}
			}
			if (playerstats->status == BURNING)
			{
				if (playerstats->debuffcounter <= 0)
				{
					playerstats->status = NEUTRAL;
				}
				else
				{
					if (playerstats->is_dmgtaken <= 0)
					{
						for (int i{ 0 }; i < 14; ++i) {
						particleInstCreate(AERandFloat() * 10, playerstats->positionX - 190, playerstats->positionY - 20, particlePLAYER);
						}
						playerstats->health -= 2;
						playerstats->is_dmgtaken = 0.5f;
						if (playerstats->health < 2)
						{
							playerstats->health = 1;
						}
					}
				}
			}
			if (playerstats->status == FROZEN)
			{
				if (playerstats->statuscounter == 0)
				{
					playerstats->status = NEUTRAL;
				}
			}
		}

		/**************************************************************
		*	A check on whether the player has levelled up or not
		***************************************************************/
		bool PlayerLevelUp()
		{
			if (playerstats->PlayerXP >= playerstats->PlayerXPMax)
			{
				return true;
			}
			return false;
		}


		/**************************************************************
		*	FOR PRESENTATION PURPOSES ONLY:
		*	gives the player a lot of potiosn to be used, when
		*	showcasing the game
		***************************************************************/
		void godmode() {
			if (AEInputCheckCurr(AEVK_G)) {
				playerinventory->defencepotion.itemcounter += 1.0f;
				playerinventory->healthpotion.itemcounter += 1.0f;
				playerinventory->staminapotion.itemcounter += 1.0f;
			}
		}

		/**************************************************************
		*	The logic that cycles through the desired RGB colours
		***************************************************************/
		void RGBloop(int& RGBcounter) {
			if (RGBcounter <= 16777215)
			{
				RGBcounter += 500;
				(RGBcounter > 16766215) ? RGBcounter = 16384000 : RGBcounter = RGBcounter;
			}
		}

		/**************************************************************
		*	Renders the player mesh with its respective x and y
		*	positions
		***************************************************************/
		void playerrender(AEGfxTexture* playertexture, AEGfxVertexList* playermesh) {

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			// Set position for object 1
			AEGfxSetPosition(playerstats->positionX, playerstats->positionY);
			if (playerstats->status == NEUTRAL)
			{
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			if (playerstats->is_dmgtaken >= 0)
			{
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.3f);
			}
			AEGfxTextureSet(playertexture, 1.0f, 1.0f);

			AEGfxMeshDraw(playermesh, AE_GFX_MDM_TRIANGLES);
		}


		/**************************************************************
		*	Chooses the cells that damages you, and renders them
		***************************************************************/
		void GridCheck(bool EnemyAttackState, float timer, int& x) {

			if (EnemyAttackState == true && timer <= 0.60f) {

				switch (x) // Check for the Safety Grids
				{

				case 1:
					//SAFEGRID (TOP SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 2:
					//SAFEGRID (BACK SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 3:
					//SAFEGRID (BOTTOM SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;
				}
				char strBufferWarning[100];
				memset(strBufferWarning, 0, 100 * sizeof(char));
				sprintf_s(strBufferWarning, "D A N G E R !");
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxPrint(fontLarge, strBufferWarning, -0.25f, -0.45f, 0.50f, 1.0f, 0.1f, 0.1f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
			}
		}

		/**************************************************************
		*	Renders the player health with respect to the maxhealth
		*	Decreases with the health
		*	Prints essential texts on screens
		*	Prints which status debuff is currently affecting the player
		***************************************************************/
		void RenderPlayerHealth()
		{
			char strBufferHealth[100];
			char strBuffer[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Player Health:  %d", playerstats->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", playerstats->PlayerLevel);

			char strBufferXPLeft[100];
			memset(strBufferXPLeft, 0, 100 * sizeof(char));
			sprintf_s(strBufferXPLeft, "XP to next level: %d", playerstats->PlayerXPMax - playerstats->PlayerXP);

			char strBufferStatus[100];
			memset(strBufferStatus, 0, 100 * sizeof(char));
			
			switch (playerstats->status)
			{
			case FROSTED:
				sprintf_s(strBufferStatus, "Status: Frosted");
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxPrint(fontId, strBufferStatus, -0.95f, -0.65f, 1.0f, 0.0f, 0.7f, 0.9f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;

			case FROZEN:
				sprintf_s(strBufferStatus, "Status: Frozen");
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxPrint(fontId, strBufferStatus, -0.95f, -0.65f, 1.0f, 0.f, 0.7f, 0.6f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;

			case BURNING:
				sprintf_s(strBufferStatus, "Status: Burning");
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxPrint(fontId, strBufferStatus, -0.95f, -0.65f, 1.0f, 0.7f, 0.0f, 0.2f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;

			case NEUTRAL:
				sprintf_s(strBufferStatus, "Status: Normal");
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_COLOR);
				AEGfxPrint(fontId, strBufferStatus, -0.95f, -0.65f, 1.0f, 1.f, 1.f, 1.f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			}

			if (playercurrhealth != nullptr) {
				AEGfxMeshFree(playercurrhealth);
				playercurrhealth = nullptr;
			}

			float healthscale = (float)playerstats->health / playerstats->maxhealth;

			AEGfxMeshStart();

			AEGfxTriAdd(
				-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight()*29/60), 0xFFFFFFFF, 0.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight()*53/120), 0xFFFFFFFF, 0.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.4875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f);

			AEGfxTriAdd(
				-(float)(AEGetWindowWidth() * 0.4875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.4875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f,
				-(float)(AEGetWindowWidth() * 0.4875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);

			//AEGfxTriAdd(
			//	-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			//	-390.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			//	-390.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			//AEGfxTriAdd(
			//	-390.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			//	-390.0f + 160 * healthscale, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			//	-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			playercurrhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(playercurrhealth, "Failed to create playercurrhealth!!");

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(0.9f, 0.0f, 0.0f, 1.0f);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(playercurrhealth, AE_GFX_MDM_TRIANGLES);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(fontId, strBufferHealth, -0.95f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferLevel, -0.95f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferXPLeft, -0.95f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
			sprintf_s(strBuffer, "Stamina: %d", playerstats->staminacount);
			AEGfxPrint(fontId, strBuffer, -0.10f, -0.80f, 1.14f, 1.0f, 1.0f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);

		}
	}

	/******************************************************
	*
	* ENEMY NAMESPACE
	*
	*******************************************************/
	namespace Enemies
	{

		AEGfxVertexList* EnemyGridIdle = 0;
		AEGfxVertexList* EnemyGridAttack = 0;
		AEGfxVertexList* EnemyMesh = 0;
		AEGfxVertexList* Enemymaxhealth = 0;
		AEGfxVertexList* Enemycurrhealth = 0;


		namespace
		{

			/**************************************************************
			*	checks for enemy type and their respective status effects
			*	on the player
			***************************************************************/
			void EnemyTypeCheckToApplyPlayerDebuff()
			{

				switch (enemystats->EnemyType)
				{
				case ICE:
					++enemystats->DebuffCounter;
					if (playerstats->status != FROZEN)
					{
						playerstats->status = FROSTED;
						playerstats->debuffcounter = 5.0f;
					}
					if (playerstats->status == FROSTED && enemystats->DebuffCounter == 2)
					{
						playerstats->status = FROZEN;
						enemystats->DebuffCounter = 0;
					}
					break;
				case FIRE:
					if (playerstats->status != BURNING)
					{
						playerstats->status = BURNING;
						playerstats->debuffcounter = 3.0f;
					}
					break;
				case ENEMYBOSS:
					playerstats->status = (rand() % 3) + 1;
					playerstats->debuffcounter = 5.0f;
					if (playerstats->status == FROZEN)
					{
						playerstats->statuscounter = 10;
					}
					break;
				case NORMAL:
					break;
				}
			}

			/**************************************************************
			*	logic for player taking damage based on the different flags
			*	and grids the player is currently on
			***************************************************************/
			void EnemyAttackState()
			{
				playerstats->SAFEGRID = enemystats->EnemyGrid;
				enemystats->EnemyState = ATTACKING;
				enemystats->is_attacking = true;

				//Movement to Attack Grid
				if (enemystats->positionX != 150.0f)
				{
					enemystats->positionX += 10.0f;
				}
				if (enemystats->EnemyState == ATTACKING && enemystats->is_attacking == true)
				{
					//Delay before enemy attack
					enemystats->AttackCD -= DT;
					if (enemystats->AttackCD <= 0.0f)
					{
						if (playerstats->positionID != playerstats->SAFEGRID)
						{
							for (int i{ 0 }; i < 20; ++i) {
								particleInstCreate(AERandFloat() * 10, playerstats->positionX - 190, playerstats->positionY - 20, particlePLAYER);
							}
							if (playerstats->health == playerstats->maxhealth)
							{
								if (enemystats->damage >= playerstats->health)
								{
									playerstats->health = 1;
								}
								else
								{
									playerstats->health -= (int)enemystats->damage;
								}
							}
							else
							{
								playerstats->health -= (int)enemystats->damage;
							}

							playerstats->is_dmgtaken = 0.5f;
							EnemyTypeCheckToApplyPlayerDebuff();
						}

						//Resets Everything such as Enemy Cooldown while in idle
						//Sets the AttackCD for the next attack phase
						//Sets the next safe grid for next attack
						enemystats->AttackCD = 0.60f;
						enemystats->EnemyCD = static_cast<float>((rand() % 4) + 1);
						enemystats->EnemyGrid = (rand() % 3) + 1;
						enemystats->DamageCD = 1.0f;
						slashing1_Audio();
					}
				}
			}

			/**************************************************************
			*	resetting the states for the next attack sequence
			***************************************************************/
			void EnemyIdleState()
			{
				//Idle state and reducing of enemyCD to next attack
				//DamageCD is for frames where player cannot attack the enemy as enemy
				//is returning to idle state
				enemystats->EnemyState = IDLE;
				enemystats->is_attacking = false;
				enemystats->positionX = 0.0f;
				enemystats->positionY = 0.0f;
				enemystats->EnemyCD -= DT;
				enemystats->DamageCD -= DT;
				if (enemystats->EnemyState == IDLE && enemystats->is_attacking == false)
				{
					//Check for Player Damage
					if (playerstats->is_attacking == true && enemystats->DamageCD <= 0.0f)
					{
						int type = particleENEMY;
						enemystats->EnemyType == ICE ? type = particleENEMYFROST : type = type;
						enemystats->EnemyType == FIRE ? type = particleENEMYFIRE : type = type;

						for (int i{ 0 }; i < 20; ++i) {
							particleInstCreate(AERandFloat() * 10, enemystats->positionX+100, enemystats->positionY+1, type);
						}
						enemystats->health -= playerstats->damage;
						playerstats->is_attacking = false;
					}
				}
			}
		}


		/**************************************************************
		*	Chooses an enemytype for the player to encounter in the
		*	maze
		***************************************************************/
		void ChoosingEnemyType(float RNG) {

			switch ((int)RNG)
			{
			case NORMAL:
				enemystats->EnemyLevel = playerstats->PlayerLevel + ((rand() % 2));
				enemystats->EnemyType = NORMAL;
				enemystats->health = 40 + (5 * enemystats->EnemyLevel);
				enemystats->maxhealth = 40 + (5 * enemystats->EnemyLevel);
				enemystats->enemytypedamage = (f32)(5 * enemystats->EnemyLevel);
				enemystats->damage = enemystats->enemytypedamage;
				enemystats->EnemyCD = 2.0f;				//Cooldown till next enemy attack
				enemystats->EnemyXP = 20 + (10 * enemystats->EnemyLevel);
				break;

			case ICE:
				enemystats->EnemyLevel = playerstats->PlayerLevel + ((rand() % 2));
				enemystats->EnemyType = ICE;
				enemystats->health = 50 + (5 * enemystats->EnemyLevel);
				enemystats->maxhealth = 50 + (5 * enemystats->EnemyLevel);
				enemystats->enemytypedamage = 15.0f + (f32)(2 * enemystats->EnemyLevel);
				enemystats->damage = enemystats->enemytypedamage;
				enemystats->EnemyCD = 2.0f;				//Cooldown till next enemy attack
				enemystats->DebuffCounter = 0;
				enemystats->EnemyXP = 50 + (10 * enemystats->EnemyLevel);
				break;

			case FIRE:
				enemystats->EnemyLevel = playerstats->PlayerLevel + ((rand() % 2));
				enemystats->EnemyType = FIRE;
				enemystats->health = 50 + (5 * enemystats->EnemyLevel);
				enemystats->maxhealth = 50 + (5 * enemystats->EnemyLevel);
				enemystats->enemytypedamage = 10.0f + (f32)(1 * enemystats->EnemyLevel);
				enemystats->damage = enemystats->enemytypedamage;
				enemystats->EnemyCD = 2.0f;				//Cooldown till next enemy attack
				enemystats->DebuffCounter = 0;
				enemystats->EnemyXP = 50 + (10 * enemystats->EnemyLevel);
				break;
			}
		}


		/**************************************************************
		*	Spawns the boss enemy by setting the relevant details and
		*	flags to the enemy struct
		***************************************************************/
		void SpawnBossEnemy()
		{
			enemystats->EnemyLevel = playerstats->PlayerLevel;
			enemystats->EnemyType = ENEMYBOSS;
			enemystats->health = 70 + (5 * enemystats->EnemyLevel);
			enemystats->maxhealth = 70 + (5 * enemystats->EnemyLevel);
			enemystats->enemytypedamage = 20.0f + (f32)(5 * enemystats->EnemyLevel);
			enemystats->damage = enemystats->enemytypedamage;
			enemystats->EnemyCD = 2.0f;				//Cooldown till next enemy attack
			enemystats->DebuffCounter = 0;
			enemystats->EnemyXP = 65 + (20 * enemystats->EnemyLevel);
		}

		
		/**************************************************************
		*	Chooses the enemy states between idle and attacking
		***************************************************************/
		void UpdateEnemyState()
		{
			if (enemystats->EnemyCD <= 0.0f)
			{
				EnemyAttackState();
			}
			else
			{
				EnemyIdleState();
			}
		}


		/**************************************************************
		*	Loads the enemy meshes
		***************************************************************/
		void EnemyCombatMesh()
		{
			//FreeEnemyMesh();													//deletes old mesh

			AEGfxMeshStart();

			AEGfxVertexAdd((float)(AEGetWindowHeight() / 12), -(float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd((float)(AEGetWindowWidth() * 3 / 16), -(float)(AEGetWindowHeight() / 12), 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd((float)(AEGetWindowWidth() * 3 / 16), (float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID IDLE
			AEGfxVertexAdd((float)(AEGetWindowHeight() / 12), (float)(AEGetWindowHeight() / 12), 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd((float)(AEGetWindowHeight() / 12), -(float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 1.0f);

			//AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			//AEGfxVertexAdd(150.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			//AEGfxVertexAdd(150.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID IDLE
			//AEGfxVertexAdd(50.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			//AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridIdle = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridIdle, "Failed to create enemygrididle!!");


			AEGfxMeshStart();

			AEGfxVertexAdd((float)(AEGetWindowWidth()/4), -(float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd((float)(AEGetWindowWidth()*3/8), -(float)(AEGetWindowHeight() / 12), 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd((float)(AEGetWindowWidth() * 3 / 8), (float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID ATTACK
			AEGfxVertexAdd((float)(AEGetWindowWidth() / 4), (float)(AEGetWindowHeight() / 12), 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd((float)(AEGetWindowWidth() / 4), -(float)(AEGetWindowHeight() / 12), 0xFF0000, 0.0f, 1.0f);

			//AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			//AEGfxVertexAdd(300.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			//AEGfxVertexAdd(300.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID ATTACK
			//AEGfxVertexAdd(200.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			//AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridAttack = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridAttack, "Failed to create enemygridattack!!");

			AEGfxMeshStart();

			AEGfxTriAdd(
				(float)(AEGetWindowWidth() * 0.0875), -(float)(AEGetWindowHeight()*0.05), 0x00FF00FF, 0.0f, 1.0f,
				(float)(AEGetWindowWidth() * 0.1625), -(float)(AEGetWindowHeight() * 0.05), 0x00FFFF00, 1.0f, 1.0f,
				(float)(AEGetWindowWidth() * 0.0875), (float)(AEGetWindowHeight() * 0.05), 0x0000FFFF, 0.0f, 0.0f);
			//x,y,colour,u,v

			AEGfxTriAdd(
				(float)(AEGetWindowWidth() * 0.1625), -(float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 1.0f, 1.0f,
				(float)(AEGetWindowWidth() * 0.1625), (float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 1.0f, 0.0f,
				(float)(AEGetWindowWidth() * 0.0875), (float)(AEGetWindowHeight() * 0.05), 0x00FFFFFF, 0.0f, 0.0f);

			//AEGfxTriAdd(
			//	70.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
			//	130.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
			//	70.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);
			////x,y,colour,u,v

			//AEGfxTriAdd(
			//	130.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
			//	130.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
			//	70.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

			EnemyMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyMesh, "Failed to create enemyMesh!!");
		}


		/**************************************************************
		*	Renders and draws the enemy grids
		***************************************************************/
		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
		}

		/**************************************************************
		*	Frees the enemy meshes
		***************************************************************/
		void FreeEnemyMesh()
		{

			if (EnemyGridIdle != nullptr) {
				AEGfxMeshFree(EnemyGridIdle);
				EnemyGridIdle = nullptr;
			}

			if (EnemyGridAttack != nullptr) {
				AEGfxMeshFree(EnemyGridAttack);
				EnemyGridAttack = nullptr;
			}

			if (EnemyMesh != nullptr) {
				AEGfxMeshFree(EnemyMesh);
				EnemyMesh = nullptr;
			}

			if (Enemycurrhealth != nullptr) {
				AEGfxMeshFree(Enemycurrhealth);
				Enemycurrhealth = nullptr;
			}
		}

		/**************************************************************
		*	Renders and draws the enemy based on their different
		*	textures
		***************************************************************/
		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetPosition(enemystats->positionX, enemystats->positionY);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxTextureSet(enemytexture, 1.0f, 1.0f);
			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_TRIANGLES);
		}

		/**************************************************************
		*	Renders and draws the enemy health bar with respect to its
		*	maxhealth
		*	also prints out texts telling which enemy type it is
		***************************************************************/
		void RenderEnemyHealth()
		{
			char strBufferHealth[100];
			//char strBuffer[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Enemy Health:  %d", enemystats->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", enemystats->EnemyLevel);

			char strBufferType[100];
			memset(strBufferType, 0, 100 * sizeof(char));
			switch (enemystats->EnemyType)
			{
			case NORMAL:
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				sprintf_s(strBufferType, "Enemy Type: Normal");
				AEGfxPrint(fontId, strBufferType, 0.60f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			case ICE:
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				sprintf_s(strBufferType, "Enemy Type: Frost");
				AEGfxPrint(fontId, strBufferType, 0.60f, -0.75f, 1.0f, 0.0f, 0.7f, 0.9f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			case FIRE:
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				sprintf_s(strBufferType, "Enemy Type: Fire");
				AEGfxPrint(fontId, strBufferType, 0.60f, -0.75f, 1.0f, 1.0f, 0.2f, 0.2f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			case ENEMYBOSS:
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				sprintf_s(strBufferType, "Enemy Type: BOSS");
				AEGfxPrint(fontId, strBufferType, 0.60f, -0.75f, 1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetBlendMode(AE_GFX_BM_NONE);
				break;
			}

		float healthscale = (float)enemystats->health / enemystats->maxhealth;


			if (Enemycurrhealth != nullptr) {
				AEGfxMeshFree(Enemycurrhealth);
				Enemycurrhealth = nullptr;
			}

		AEGfxMeshStart();
		AEGfxTriAdd(
			(float)(AEGetWindowWidth()*0.2875), -(float)(AEGetWindowHeight()*29/60), 0xFFFFFFFF, 0.0f, 1.0f,
			(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight()*53/120), 0xFFFFFFFF, 0.0f, 1.0f,
			(float)(AEGetWindowWidth() * 0.2875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f);

		AEGfxTriAdd(
			(float)(AEGetWindowWidth() * 0.2875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 53 / 120), 0xFFFFFFFF, 0.0f, 1.0f,
			(float)(AEGetWindowWidth() * 0.2875) + 160 * healthscale, -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f,
			(float)(AEGetWindowWidth() * 0.2875), -(float)(AEGetWindowHeight() * 29 / 60), 0xFFFFFFFF, 0.0f, 1.0f);

		//AEGfxTriAdd(
		//	230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		//	230.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		//	230.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);

		//AEGfxTriAdd(
		//	230.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		//	230.0f + 160 * healthscale, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
		//	230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			Enemycurrhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(Enemycurrhealth, "Failed to create Enemycurrhealth!!");

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(0.9f, 0.0f, 0.0f, 1.0f);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(Enemycurrhealth, AE_GFX_MDM_TRIANGLES);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
      
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(fontId, strBufferHealth, 0.60f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferLevel, 0.60f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}
	}
}
