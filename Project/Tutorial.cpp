/**************************************************************************
 * 	File name	:	Tutorial.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Matthew Cheung Jun Yin	(PRIMARY AUTHOR - 90%)
					Hu Jun Ning				(SECONDARY AUTHOR - 10%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

//variables
/* Define */
int page{ 1 };
enum pages { page_1 = 1, page_2, page_3, page_4, page_5, page_6, page_7, page_8 };

extern sys systemsettings;

/* Objects */
AEGfxVertexList* fake_window_box;
AEGfxVertexList* button_box;
AEGfxVertexList* large_button_box;
AEGfxVertexList* Mesh_maze_overview;
//AEGfxVertexList* line;

AEGfxTexture* maze_screenshot;
AEGfxTexture* Whirlpool;
AEGfxTexture* dodging_attack;
AEGfxTexture* Chest;
AEGfxTexture* defence_potion;
AEGfxTexture* health_potion;
AEGfxTexture* stamina_potion;
AEGfxTexture* tutorialcombat1;
AEGfxTexture* normal_turtle;
AEGfxTexture* fire_turtle;
AEGfxTexture* frost_turtle;
AEGfxTexture* tutorial_tab_map;
AEGfxTexture* tutorial_potions;
AEGfxTexture* ducktitle;
AEGfxTexture* fightingduck;
AEGfxTexture* LevelUpPic;


void page_one_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth()*2 / 4, (float)AEGetWindowHeight()); //drawing ducktitle
	DrawingTextureOnMesh(Mesh_maze_overview, ducktitle, 0.0f, 30.0f); 

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth() / 3, (float)AEGetWindowHeight() / 3); //drawing fighting duck
	DrawingTextureOnMesh(Mesh_maze_overview, fightingduck, -220.0f, 20.0f);

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth() / 3, (float)AEGetWindowHeight() / 3); //drawing angry turtle
	DrawingTextureOnMesh(Mesh_maze_overview, normal_turtle, 220.0f, 20.0f);

	//drawing next page button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);


	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);
	
	AEGfxSetBlendMode(AE_GFX_BM_NONE);

}

void page_two_code()
{
	char strBuffer[1000];

	//draw W
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 15 / 60), (float)(AEGetWindowHeight() / 32));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);
	
	//draw A
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowWidth() * 4 / 32), -(float)(AEGetWindowHeight() * 2 / 36));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);
	
	//draw S
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 15 / 60), -(float)(AEGetWindowHeight() * 2 / 36));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	//draw D
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.335), -(float)(AEGetWindowHeight() * 2 / 36));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing next page button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth() * 5 / 9, (float)AEGetWindowHeight() * 5 / 9);
	DrawingTextureOnMesh(Mesh_maze_overview, maze_screenshot, -160.0f, -60.0f); //drawing maze screenshot

	//drawing previous page box (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);
	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	
	sprintf_s(strBuffer, "Explore");
	AEGfxPrint(fontLarge, strBuffer, -0.55f, 0.40f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Navigate the maze and battle enemies");
	AEGfxPrint(fontId, strBuffer, -0.65f, 0.20f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Movement");
	AEGfxPrint(fontLarge, strBuffer, 0.18f, 0.40f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "W");
	AEGfxPrint(fontId, strBuffer, 0.36f, 0.045f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "A");
	AEGfxPrint(fontId, strBuffer, 0.24f, -0.13f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "S");
	AEGfxPrint(fontId, strBuffer, 0.365f, -0.13f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "D");
	AEGfxPrint(fontId, strBuffer, 0.490f, -0.13f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Move Up");
	AEGfxPrint(fontId, strBuffer, 0.32f, 0.20f, 1.0f, 1.f, 1.f, 1.f); // "move up" text

	sprintf_s(strBuffer, "Move Left");
	AEGfxPrint(fontId, strBuffer, 0.025f, -0.13f, 1.0f, 1.f, 1.f, 1.f); // "move left" text

	sprintf_s(strBuffer, "Move Down");
	AEGfxPrint(fontId, strBuffer, 0.30f, -0.28f, 1.0f, 1.f, 1.f, 1.f); // "move down" text

	sprintf_s(strBuffer, "Attack");
	AEGfxPrint(fontId, strBuffer, 0.60f, -0.13f, 1.0f, 1.f, 1.f, 1.f); // "move right" text

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);
	
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_three_code()
{
	char strBuffer[1500];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 9, (float)AEGetWindowHeight() * 5 / 9);
	DrawingTextureOnMesh(Mesh_maze_overview, Whirlpool, -160.0f, -45.0f); //Drawing whirlpool Image

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth() * 5 / 14, (float)AEGetWindowHeight() * 5 / 14);
	DrawingTextureOnMesh(Mesh_maze_overview, Chest, 130.0f, 30.0f); //Drawing Chest Image

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18);
	DrawingTextureOnMesh(Mesh_maze_overview, defence_potion, 40.0f, -90.0f); //Drawing defence potion Image

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18);
	DrawingTextureOnMesh(Mesh_maze_overview, health_potion, 130.0f, -90.0f); //Drawing health potion Image

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18);
	DrawingTextureOnMesh(Mesh_maze_overview, stamina_potion, 220.0f, -90.0f); //Drawing stamina potion Image
	meshfree();

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing previous page box (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Objective");
	AEGfxPrint(fontLarge, strBuffer, -0.58f, 0.45f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Chests");
	AEGfxPrint(fontLarge, strBuffer, 0.20f, 0.45f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Find the exit of the maze to escape!");
	AEGfxPrint(fontId, strBuffer, -0.65f, 0.31f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Find chests to get items that can help you");
	AEGfxPrint(fontId, strBuffer, 0.05f, 0.31f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Defence");
	AEGfxPrint(fontId, strBuffer, 0.05f, -0.15f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press 1");
	AEGfxPrint(fontId, strBuffer, 0.0440f, -0.50f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Reduces damage");
	AEGfxPrint(fontId, strBuffer, -0.020f, -0.55f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "taken by 30%%");
	AEGfxPrint(fontId, strBuffer, 0.010f, -0.60f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Health");
	AEGfxPrint(fontId, strBuffer, 0.28f, -0.15f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press 2");
	AEGfxPrint(fontId, strBuffer, 0.275f, -0.50f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Recovers");
	AEGfxPrint(fontId, strBuffer, 0.265f, -0.55f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "50 hp");
	AEGfxPrint(fontId, strBuffer, 0.285f, -0.60f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Stamina");
	AEGfxPrint(fontId, strBuffer, 0.485f, -0.15f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press 3");
	AEGfxPrint(fontId, strBuffer, 0.50f, -0.50f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Increases stamina");
	AEGfxPrint(fontId, strBuffer, 0.43f, -0.55f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "recovery");
	AEGfxPrint(fontId, strBuffer, 0.49f, -0.60f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);
	
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_four_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 0.9f, (float)AEGetWindowWidth() * 0.9f); //drawing tutorial tab map
	DrawingTextureOnMesh(Mesh_maze_overview, tutorial_tab_map, 80.0f, -40.0f);

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowWidth() * 0.7f, (float)AEGetWindowHeight() * 0.7f); //drawing tutorial potions
	DrawingTextureOnMesh(Mesh_maze_overview, tutorial_potions, -200.0f, -40.0f);

	//drawing next page button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing previous page box (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Inventory Tab");
	AEGfxPrint(fontLarge, strBuffer, -0.25f, 0.50f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Hold tab to access the minimap and your item inventory");
	AEGfxPrint(fontId, strBuffer, -0.35f, 0.40f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);
	
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_five_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight(), (float)AEGetWindowWidth() * 1.35f);
	DrawingTextureOnMesh(Mesh_maze_overview, tutorialcombat1, 18.0f, -20.0f); //Drawing tutorial combat Image

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing button boxes (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);
	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Combat");
	AEGfxPrint(fontLarge, strBuffer, -0.17f, 0.45f, 0.50f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Move up, down or left to avoid attacks!");
	AEGfxPrint(fontId, strBuffer, 0.0f, 0.20f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Attack when the enemy is not moving!");
	AEGfxPrint(fontId, strBuffer, 0.0f, 0.30f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "W");
	AEGfxPrint(fontLarge, strBuffer, -0.31f, 0.225f, 0.40f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "A");
	AEGfxPrint(fontLarge, strBuffer, -0.49f, 0.0f, 0.40f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "S");
	AEGfxPrint(fontLarge, strBuffer, -0.30f, -0.225f, 0.40f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "D");
	AEGfxPrint(fontLarge, strBuffer, -0.06f, 0.0f, 0.40f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_six_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight(), (float)AEGetWindowWidth());
	DrawingTextureOnMesh(Mesh_maze_overview, dodging_attack, 0.0f, -20.0f); //drawing dodging attacks image

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing button boxes (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Time your movement to move into the unlit grid to avoid getting hit!");
	AEGfxPrint(fontLarge, strBuffer, -0.75f, 0.50f, 0.3f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_seven_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18); //drawing stamina potion
	DrawingTextureOnMesh(Mesh_maze_overview, stamina_potion, 180.0f, 80.0f); 

	meshfree();
	//create mesh using height * height to get square shape
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18); //drawing angry turtle
	DrawingTextureOnMesh(Mesh_maze_overview, normal_turtle, -210.0f, 80.0f);

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18); // drawing fire turtle
	DrawingTextureOnMesh(Mesh_maze_overview, fire_turtle, -210.0f, -10.0f);

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight() * 5 / 18, (float)AEGetWindowHeight() * 5 / 18); // drawing from turtle
	DrawingTextureOnMesh(Mesh_maze_overview, frost_turtle, -210.0f, -100.0f);
	meshfree();

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	//drawing button boxes (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Enemies");
	AEGfxPrint(fontLarge, strBuffer, -0.50f, 0.50f, 0.45f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Stamina");
	AEGfxPrint(fontLarge, strBuffer, 0.30f, 0.50f, 0.45f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Every move you make consumes stamina");
	AEGfxPrint(fontId, strBuffer, 0.20f, 0.05f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "so move wisely!");
	AEGfxPrint(fontId, strBuffer, 0.35f, 0.0f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Normal Turtle");
	AEGfxPrint(fontLarge, strBuffer, -0.35f, 0.28f, .25f, 0.0f, 1.0f, 0.0f);

	sprintf_s(strBuffer, "This turtle is the most ");
	AEGfxPrint(fontId, strBuffer, -0.35f, 0.23f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "common enemy you will find");
	AEGfxPrint(fontId, strBuffer, -0.35f, 0.18f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Flame Turtle");
	AEGfxPrint(fontLarge, strBuffer, -0.35f, -0.05f, 0.25f, 1.0f, 0.0f, 0.0f);

	sprintf_s(strBuffer, "Flame Turtles deal damage that ");
	AEGfxPrint(fontId, strBuffer, -0.35f, -0.10f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "burns you for damage over time");
	AEGfxPrint(fontId, strBuffer, -0.35f, -0.15f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Frost Turtle");
	AEGfxPrint(fontLarge, strBuffer, -0.35f, -0.35f, 0.25f, 0.0f, 0.0f, 1.0f);

	sprintf_s(strBuffer, "Frost Turtles can slow you");
	AEGfxPrint(fontId, strBuffer, -0.35f, -0.40f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "for the next few seconds");
	AEGfxPrint(fontId, strBuffer, -0.35f, -0.45f, 1.f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

void page_eight_code()
{
	char strBuffer[1000];

	meshfree();
	CreatingImageMesh(Mesh_maze_overview, (float)AEGetWindowHeight(), (float)AEGetWindowWidth() * 1.35f);
	DrawingTextureOnMesh(Mesh_maze_overview, LevelUpPic, 13.0f, 30.0f); //Drawing levelup Image

	//drawing button boxes (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(large_button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	sprintf_s(strBuffer, "Increase your level by defeating enemies.");
	AEGfxPrint(fontLarge, strBuffer, -0.36f, -0.30f, 0.25f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Select between increasing your health or damage.");
	AEGfxPrint(fontLarge, strBuffer, -0.44f, -0.45f, 0.25f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}

/**************************************************************
*	creates meshes
***************************************************************/
void CreatingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		//-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 0.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 0.0f, //pink
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create MazeOverview!!");
}

/**************************************************************
*	creates the meshes
***************************************************************/
void CreatingImageMesh(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		//-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 0.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 0.0f, //pink
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create MazeOverview!!");
}

/**************************************************************
*	frees the meshes
***************************************************************/
void meshfree() {
	if (Mesh_maze_overview != nullptr) {
		AEGfxMeshFree(Mesh_maze_overview);
		Mesh_maze_overview = nullptr;
	}
}

/**************************************************************
*	draws the meshes
***************************************************************/
void DrawingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(maze_screenshot, 0, 0);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

/**************************************************************
*	draws the meshes
***************************************************************/
void DrawingTextureOnMesh(AEGfxVertexList*& pMesh_MainCharacter, AEGfxTexture* texture_var, float MC_positionX, float MC_positionY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(texture_var, 0, 0);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

/**************************************************************
*	load function for the tutorial
***************************************************************/
void Tutorial_Load()
{
	//draws window outline with reference to window's width and height
	AEGfxMeshStart();
	AEGfxVertexAdd(-((float)AEGetWindowWidth() * 2 / 5), -((float)AEGetWindowHeight() * 2 / 5), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowWidth() * 2 / 5), ((float)AEGetWindowHeight() * 2 / 5), 0x00FFFF00, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowWidth() * 2 / 5), ((float)AEGetWindowHeight() * 2 / 5), 0x0000FFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowWidth() * 2 / 5), -((float)AEGetWindowHeight() * 2 / 5), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowWidth() * 2 / 5), -((float)AEGetWindowHeight() * 2 / 5), 0x00FFFF00, 0.0f, 0.0f);

	//draw the line 
	AEGfxVertexAdd(-((float)AEGetWindowWidth() * 2 / 5), ((float)AEGetWindowHeight() / 3), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowWidth() * 2 / 5), ((float)AEGetWindowHeight() / 3), 0x00FFFF00, 0.0f, 0.0f);

	fake_window_box = AEGfxMeshEnd();
	AE_ASSERT_MESG(fake_window_box, "fail to create fake window!!");


	//button box
	AEGfxMeshStart();
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 1 / 30), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 1 / 30), ((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), ((float)AEGetWindowHeight() * 1 / 30), 0x0000FFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 1 / 30), -((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);

	button_box = AEGfxMeshEnd();
	AE_ASSERT_MESG(button_box, "Failed to create triangle!!");

	//new button box
	AEGfxMeshStart();
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), ((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), ((float)AEGetWindowHeight() * 1 / 30), 0x0000FFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), -((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);

	large_button_box = AEGfxMeshEnd();
	AE_ASSERT_MESG(large_button_box, "Failed to create triangle!!");
	////middle line
	//AEGfxMeshStart();
	//AEGfxVertexAdd(0, 299, 0x00FF00FF, 0.0f, 0.0f);
	//AEGfxVertexAdd(0, -299, 0x00FFFF00, 0.0f, 0.0f);
	//line = AEGfxMeshEnd();

	ducktitle = AEGfxTextureLoad("Images/ducktitle.png");
	AE_ASSERT_MESG(ducktitle, "Failed to create MazeOverview texture!\n");

	fightingduck = AEGfxTextureLoad("Images/Fighting duck.png");
	AE_ASSERT_MESG(fightingduck, "Failed to create MazeOverview texture!\n");

	maze_screenshot = AEGfxTextureLoad("Images/maze_screenshot.png");
	AE_ASSERT_MESG(maze_screenshot, "Failed to create MazeOverview texture!\n");

	Chest = AEGfxTextureLoad("Images/Chest.png");
	AE_ASSERT_MESG(Chest, "Failed to create Chest texture!\n");

	defence_potion = AEGfxTextureLoad("Images/defencepotion.png");
	AE_ASSERT_MESG(defence_potion, "Failed to create defencepotion texture!\n");

	health_potion = AEGfxTextureLoad("Images/healthpotion.png");
	AE_ASSERT_MESG(health_potion, "Failed to create healthpotion texture!\n");

	stamina_potion = AEGfxTextureLoad("Images/staminapotioninv.png");
	AE_ASSERT_MESG(stamina_potion, "Failed to create staminapotion texture!\n");

	Whirlpool = AEGfxTextureLoad("Images/Whirlpool.png");
	AE_ASSERT_MESG(Whirlpool, "Failed to create Whirlpool texture!\n");

	tutorial_tab_map = AEGfxTextureLoad("Images/tutorial_tab_map.png");
	AE_ASSERT_MESG(tutorial_tab_map, "Failed to create tutorial_tab_map texture!\n");

	tutorial_potions = AEGfxTextureLoad("Images/tutorial_potions.png");
	AE_ASSERT_MESG(tutorial_potions, "Failed to create tutorial_potions texture!\n");

	tutorialcombat1 = AEGfxTextureLoad("Images/tutorialcombat1.png");
	AE_ASSERT_MESG(Whirlpool, "Failed to create tutorialcombat1 texture!\n");

	dodging_attack = AEGfxTextureLoad("Images/dodging_attack.png");
	AE_ASSERT_MESG(dodging_attack, "Failed to create dodging_attack texture!\n");

	normal_turtle = AEGfxTextureLoad("Images/Angry turtle.png");
	AE_ASSERT_MESG(normal_turtle, "Failed to create Angry turle texture!\n");

	fire_turtle = AEGfxTextureLoad("Images/Fire turtle.png");
	AE_ASSERT_MESG(fire_turtle, "Failed to create Fire turle texture!\n");

	frost_turtle = AEGfxTextureLoad("Images/Frost turtle.png");
	AE_ASSERT_MESG(frost_turtle, "Failed to create Frost turle texture!\n");

	LevelUpPic = AEGfxTextureLoad("Images/LevelUp.png");
	AE_ASSERT_MESG(LevelUpPic, "Failed to create LevelUp texture!\n");
}

/**************************************************************
*	init function for the tutorial
***************************************************************/
void Tutorial_Init()
{
	page = 1;
}

/**************************************************************
*	update function for the tutorial
***************************************************************/
void Tutorial_Update()
{
	Audio_Update();

	//go back to MENU
	if (AEInputCheckTriggered(AEVK_Q)) 
	{
		next = MENU;
	}

	if (AEInputCheckTriggered(AEVK_A))
	{
		if (--page) page_flip1_Audio();
		if (page < 1)
		{
			page = 1;
		}
	}

	if (AEInputCheckTriggered(AEVK_D))
	{
		++page;

		if (page <= 8) {
			page_flip2_Audio();
		}

		if (page > 8)
		{
			page = 8;
		}
	}


	switch (page) {
	case page_1: page_one_code();
		break;

	case page_2: page_two_code();
		break;

	case page_3: page_three_code();
		break;

	case page_4: page_four_code();
		break;

	case page_5: page_five_code();
		break;

	case page_6: page_six_code();
		break;

	case page_7: page_seven_code();
		break;
	
	case page_8: page_eight_code();
		break;
	}
}

/**************************************************************
*	draw function for the tutorial
***************************************************************/
void Tutorial_Draw()
{
	char strBuffer[1000];

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-100.0f, 0.0f);
	AEGfxTextureSet(maze_screenshot, 0, 0);

	//MUST HAVE - drawing of window outline
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxMeshDraw(fake_window_box, AE_GFX_MDM_LINES_STRIP);

	////line
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetPosition(0.0f, 0.0f);
	//AEGfxTextureSet(NULL, 0, 0); // No texture for object
	//AEGfxMeshDraw(line, AE_GFX_MDM_LINES_STRIP);

	//MUST HAVE print tutorial
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "Tutorial :D");
	AEGfxPrint(fontLarge, strBuffer, -0.08f, 0.71f, 0.25f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press [Q] to go back to the main menu");
	AEGfxPrint(fontLarge, strBuffer, -0.32f, -0.9f, 0.25f, 1.f, 1.f, 1.f);
}

/**************************************************************
*	free function for the tutorial
***************************************************************/
void Tutorial_Free()
{
	std::cout << "Tutorial:Free" << std::endl;
	AEGfxMeshFree(fake_window_box);
	AEGfxMeshFree(button_box);
	AEGfxMeshFree(large_button_box);
	if (Mesh_maze_overview != nullptr) {
		AEGfxMeshFree(Mesh_maze_overview);
		Mesh_maze_overview = nullptr;
	}
}

/**************************************************************
*	unload function for the tutorial
***************************************************************/
void Tutorial_Unload()
{
	std::cout << "Tutorial:Unload" << std::endl;
	AEGfxTextureUnload(ducktitle);
	AEGfxTextureUnload(maze_screenshot);
	AEGfxTextureUnload(Whirlpool);
	AEGfxTextureUnload(dodging_attack);
	AEGfxTextureUnload(Chest);
	AEGfxTextureUnload(defence_potion);
	AEGfxTextureUnload(health_potion);
	AEGfxTextureUnload(stamina_potion);
	AEGfxTextureUnload(tutorialcombat1);
	AEGfxTextureUnload(normal_turtle);
	AEGfxTextureUnload(fire_turtle);
	AEGfxTextureUnload(frost_turtle);
	AEGfxTextureUnload(tutorial_tab_map);
	AEGfxTextureUnload(tutorial_potions);
	AEGfxTextureUnload(fightingduck);
	AEGfxTextureUnload(LevelUpPic);
}