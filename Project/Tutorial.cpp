#include "pch.hpp"

//variables
/* Define */
int page {1};
enum pages {page_1 = 1, page_2};

extern sys systemsettings;

/* Objects */
AEGfxVertexList* fake_window_box;
AEGfxVertexList* button_box;
//AEGfxVertexList* line;

void page_one_code()
{
	char strBuffer[1000];

	/* PAGE 1 */
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "Page 1");
	AEGfxPrint(fontId, strBuffer, -0.06f, 0.59f, 1.0f, 1.f, 1.f, 1.f);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "At the start, ducky is at the beginning of the maze. You can move ducky by pressing one of these buttons: ");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.5f, 1.0f, 1.f, 1.f, 1.f);

	//height = 600 = 300
	//width = 800 = 400
	
	//draw W
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 23 / 60), (float)(AEGetWindowHeight() / 6));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "W");
	AEGfxPrint(fontId, strBuffer, -0.589f, 0.318f, 1.0f, 1.f, 1.f, 1.f);

	//draw A
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 7 / 15), (float)(AEGetWindowHeight() / 12));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "A");
	AEGfxPrint(fontId, strBuffer, -0.713f, 0.15f, 1.0f, 1.f, 1.f, 1.f);

	//draw S
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 23 / 60), (float)(AEGetWindowHeight() / 12));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "S");
	AEGfxPrint(fontId, strBuffer, -0.585f, 0.15f, 1.0f, 1.f, 1.f, 1.f);

	//draw D
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 0.3), (float)(AEGetWindowHeight() / 12));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "D");
	AEGfxPrint(fontId, strBuffer, -0.462f, 0.15f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "W to move up");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "A to move left");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.06f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "S to move down");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.12f, 1.0f, 1.f, 1.f, 1.f);
	
	sprintf_s(strBuffer, "D to move right");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.18f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "However, ducky don't have the powers to move pass the stone paths and lily pads so it can only travel from");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.28f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "water to water till it reaches the end of the maze!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.34f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "While travelling through the maze, ducky will see some chestsand collect powerups from it but ducky will also");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.44f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "meet some evil turtles along the way, so it have to defend itself and attack those turtles to continue its journey!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.50f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Your job is to help ducky to escape the maze and meet his friends!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.60f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press D to go to the next page and see what ducky needs to do when he meets the evil turtle!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.7f, 1.0f, 1.f, 1.f, 1.f);

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.45), (float)-(AEGetWindowHeight() * 19 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "D");
	AEGfxPrint(fontId, strBuffer, 0.665f, -0.65f, 1.0f, 1.f, 1.f, 1.f);
}

void page_two_code()
{
	char strBuffer[1000];

	/* PAGE 2 */
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "Page 2");
	AEGfxPrint(fontId, strBuffer, -0.06f, 0.59f, 1.0f, 1.f, 1.f, 1.f);


	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "This game tests your reflexes! Your job is to help ducky to avoid the lighted up grids when the evil turtle attacks,");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.5f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "and to fight back. There are limited stamina moves so you need to be careful and plan your steps carefully!");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.44f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "When the grids blink, its the sign that you need to quickly move ducky to the empty grid");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.34f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "by pressing one of the buttons :");
	AEGfxPrint(fontId, strBuffer, -0.75f, 0.28f, 1.0f, 1.f, 1.f, 1.f);

	//draw W
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 23 / 60), (float)(AEGetWindowHeight() * 50 / 600));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "W");
	AEGfxPrint(fontId, strBuffer, -0.589f, 0.15f, 1.0f, 1.f, 1.f, 1.f); //0.318f

	//draw A
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 7 / 15), 0);
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "A");
	AEGfxPrint(fontId, strBuffer, -0.713f, -0.013f, 1.0f, 1.f, 1.f, 1.f); //0.15f

	//draw S
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 23 / 60), 0);
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "S");
	AEGfxPrint(fontId, strBuffer, -0.585f, -0.013f, 1.0f, 1.f, 1.f, 1.f);

	//draw D
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)-(AEGetWindowHeight() * 0.3), 0);
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "D");
	AEGfxPrint(fontId, strBuffer, -0.462f, -0.013f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "W to move up");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.15f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "A to move left");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.21f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "S to move down");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.27f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "D to move right");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.33f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "If the buttons are pressed at the correct time, the evil's turtle health will decrease by 10!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.43f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "If you press the buttons too late or didn't press them at all, ducky will get attacked by the evil turtle and its health");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.49f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "will decrease by 10!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.55f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "If ducky's health is 0, that means ducky failed to defend itself :(");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.61f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Your job is to help ducky to defend itself and attack evil turtle till its health is 0! Good Luck!");
	AEGfxPrint(fontId, strBuffer, -0.75f, -0.71f, 1.0f, 1.f, 1.f, 1.f);

	////drawing button boxes (left)
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetPosition((float)(AEGetWindowHeight() * 0.35), (float)-(AEGetWindowHeight() * 19 / 60));
	//AEGfxTextureSet(NULL, 0, 0); // No texture for object
	//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	//AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	//AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	//sprintf_s(strBuffer, "A");
	//AEGfxPrint(fontId, strBuffer, 0.492f, -0.65f, 1.0f, 1.f, 1.f, 1.f);

	//drawing button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.45), (float)-(AEGetWindowHeight() * 19 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box, AE_GFX_MDM_LINES_STRIP);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "A");
	AEGfxPrint(fontId, strBuffer, 0.665f, -0.65f, 1.0f, 1.f, 1.f, 1.f);
}

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

	////middle line
	//AEGfxMeshStart();
	//AEGfxVertexAdd(0, 299, 0x00FF00FF, 0.0f, 0.0f);
	//AEGfxVertexAdd(0, -299, 0x00FFFF00, 0.0f, 0.0f);
	//line = AEGfxMeshEnd();
}

void Tutorial_Init()
{
	AEToogleFullScreen(systemsettings.fullscreen);
}

void Tutorial_Update()
{
	//go back to MENU
	if (AEInputCheckTriggered(AEVK_Q)) 
	{
		next = MENU;
	}
}

void Tutorial_Draw()
{
	char strBuffer[1000];

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
	AEGfxPrint(fontId, strBuffer, -0.08f, 0.72f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 1.f, 1.f);

	if (AEInputCheckCurr(AEVK_A))
	{
		--page;
		if (page < 1)
		{
			page = 1;
		}
	}

	if (AEInputCheckCurr(AEVK_D))
	{
		++page;

		if (page > 2)
		{
			page = 2;
		}
	}

	
	switch (page) {
	case page_1: page_one_code();
		break;


	case page_2: page_two_code();
		break;
	}
}

void Tutorial_Free()
{
	AEGfxMeshFree(fake_window_box);
	AEGfxMeshFree(button_box);
	//AEGfxMeshFree(line);
}

void Tutorial_Unload()
{
	
}