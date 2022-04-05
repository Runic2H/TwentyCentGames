#include "pch.hpp"



namespace {
	AEGfxVertexList* LevelMesh = 0;
	AEGfxVertexList* LevelButtons = 0;
	AEGfxVertexList* LevelTriRight = 0;
	AEGfxVertexList* LevelTriLeft = 0;
	int selection{ 1 };
	int skillpoints;
	int skillselected[3];
	int damage;
	int maxhealth;
}

void LevelUp_Load()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-(f32)AEGetWindowWidth() / 3, (f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 0.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 3, -(f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 0.0f, 1.0f,
		(f32)AEGetWindowWidth() / 3, (f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		(f32)AEGetWindowWidth() / 3, (f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 1.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 3, -(f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 0.0f, 1.0f,
		(f32)AEGetWindowWidth() / 3, -(f32)AEGetWindowHeight() / 4, 0xFFFFFFFF, 1.0f, 1.0f);

	LevelMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(LevelMesh, "Failed to create LevelMesh!\n");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-(f32)AEGetWindowWidth() / 4, (f32)AEGetWindowHeight() / 18, 0xFFFF0000, 0.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 4, -(f32)AEGetWindowHeight() / 18, 0xFFFF0000, 0.0f, 1.0f,
		(f32)AEGetWindowWidth() / 4, (f32)AEGetWindowHeight() / 18, 0xFFFF0000, 1.0f, 0.0f);
	AEGfxTriAdd(
		(f32)AEGetWindowWidth() / 4, (f32)AEGetWindowHeight() / 18, 0xFFFF0000, 1.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 4, -(f32)AEGetWindowHeight() / 18, 0xFFFF0000, 0.0f, 1.0f,
		(f32)AEGetWindowWidth() / 4, -(f32)AEGetWindowHeight() / 18, 0xFFFF0000, 1.0f, 1.0f);

	LevelButtons = AEGfxMeshEnd();
	AE_ASSERT_MESG(LevelButtons, "Failed to create LevelMesh!\n");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-(f32)AEGetWindowWidth() / 24, (f32)AEGetWindowHeight() / 24, 0xFFFF0000, 0.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 24, -(f32)AEGetWindowHeight() / 24, 0xFFFF0000, 0.0f, 1.0f,
		(f32)AEGetWindowWidth() / 100, 1, 0xFFFF0000, 1.0f, 0.0f);

	LevelTriRight = AEGfxMeshEnd();
	AE_ASSERT_MESG(LevelTriRight, "Failed to create LevelMesh!\n");

	AEGfxMeshStart();

	AEGfxTriAdd(
		-(f32)AEGetWindowWidth() / 24, (f32)AEGetWindowHeight() / 24, 0xFFFF0000, 0.0f, 0.0f,
		-(f32)AEGetWindowWidth() / 24, -(f32)AEGetWindowHeight() / 24, 0xFFFF0000, 0.0f, 1.0f,
		-((f32)AEGetWindowWidth()/11), -1, 0xFFFF0000, 1.0f, 0.0f);

	LevelTriLeft = AEGfxMeshEnd();
	AE_ASSERT_MESG(LevelTriLeft, "Failed to create LevelMesh!\n");
}

void LevelUp_Init()
{
	selection = 1;
	skillpoints = 2;
	for (int i = 0; i < 3; i++)
	{
		skillselected[i] = 0;
	}
	maxhealth = playerstats->maxhealth;
	damage = playerstats->damage;
}

void LevelUp_Update()
{
	if (AEInputCheckTriggered(AEVK_W))
	{
		if (selection == 0)
		{
			selection = 1;
		}
		else
		{
			selection--;
		}
	}
	if (AEInputCheckTriggered(AEVK_S))
	{
		if (selection == 1)
		{
			selection = 0;
		}
		else
		{
			selection++;
		}
	}
	if (AEInputCheckTriggered(AEVK_D))
	{
		if (skillpoints > 0)
		{
			if (selection == 0)
			{
				skillselected[0]++;
			}
			if (selection == 1)
			{
				skillselected[1]++;
			}
			skillpoints--;
		}
	}
	if (AEInputCheckTriggered(AEVK_A))
	{
		if (skillpoints < 2)
		{
			if (selection == 0 && skillselected[selection] != 0)
			{
				skillselected[selection]--;
				skillpoints++;
			}
			if (selection == 1 && skillselected[selection] != 0)
			{
				skillselected[selection]--;
				skillpoints++;
			}
		}
	}
	if (skillpoints == 0)
	{
		if (AEInputCheckTriggered(AEVK_SPACE))
		{
			if (selection == 0)
			{
				playerstats->maxhealth += skillselected[0] * 10;
			}
			if (selection == 1)
			{
				playerstats->damage += skillselected[1] * 1;
			}
			if (playerstats->health < playerstats->maxhealth / 2)
			{
				playerstats->health = playerstats->maxhealth/2;
			}
			next = MAZE;
		}
	}
}

void LevelUp_Draw()
{
	float w_ht = (float)AEGetWindowHeight();
	float w_wd = (float)AEGetWindowWidth();

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char)); 
	sprintf_s(strBuffer, "LEVEL UP !");
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.41f, 0.7f, 1.0f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "Lv%d -> Lv%d", playerstats->PlayerLevel - 1, playerstats->PlayerLevel);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.18f, 0.55f, 0.5f, 1.0f, 1.0f, 1.0f);


	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(LevelMesh, AE_GFX_MDM_TRIANGLES);

	if (selection == 0)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(-(f32)w_wd / 4.55f, (f32)w_ht / 6.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		if (AEInputCheckTriggered(AEVK_A))
		{
			AEGfxSetTransparency(1.0f);
		}
		else
		{
			AEGfxSetTransparency(0.2f);
		}
		AEGfxMeshDraw(LevelTriLeft, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition((f32)w_wd / 3.3f, (f32)w_ht / 6.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		if (AEInputCheckTriggered(AEVK_D))
		{
			AEGfxSetTransparency(1.0f);
		}
		else
		{
			AEGfxSetTransparency(0.2f);
		}
		AEGfxMeshDraw(LevelTriRight, AE_GFX_MDM_TRIANGLES);
	}

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, (f32)w_ht / 6.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (selection == 0)
	{
		AEGfxSetTransparency(0.5f);
	}
	else
	{
		AEGfxSetTransparency(0.0f);
	}
	AEGfxMeshDraw(LevelButtons, AE_GFX_MDM_TRIANGLES);

	sprintf_s(strBuffer, "Health %d |+%d %d", playerstats->maxhealth,skillselected[0], maxhealth + skillselected[0]*10);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.35f, 0.29f, 0.5f, 0.0f, 0.0f, 0.0f);

	if (selection == 1)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(-(f32)w_wd / 4.55f, (f32)w_ht / 22);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		if (AEInputCheckTriggered(AEVK_A))
		{
			AEGfxSetTransparency(1.0f);
		}
		else
		{
			AEGfxSetTransparency(0.2f);
		}
		AEGfxMeshDraw(LevelTriLeft, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition((f32)w_wd / 3.3f, (f32)w_ht / 22);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		if (AEInputCheckTriggered(AEVK_D))
		{
			AEGfxSetTransparency(1.0f);
		}
		else
		{
			AEGfxSetTransparency(0.2f);
		}
		AEGfxMeshDraw(LevelTriRight, AE_GFX_MDM_TRIANGLES);
	}

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, (f32)w_ht / 22);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (selection == 1)
	{
		AEGfxSetTransparency(0.5f);
	}
	else
	{
		AEGfxSetTransparency(0.0f);
	}
	AEGfxMeshDraw(LevelButtons, AE_GFX_MDM_TRIANGLES);

	sprintf_s(strBuffer, "Damage %d |+%d %d", playerstats->damage, skillselected[1], damage + skillselected[1]*1);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.35f, 0.05f, 0.5f, 0.0f, 0.0f, 0.0f);

	if (skillpoints != 0)
	{
		sprintf_s(strBuffer, "Allocate your skill points!");
	}
	else
	{
		sprintf_s(strBuffer, "Press [Space] to confirm");
	}
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.35f, -0.20f, 0.40f, 0.0f, 0.0f, 0.0f);

	sprintf_s(strBuffer, "%d", skillpoints);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.02f, -0.42f, 0.5f, 0.0f, 0.0f, 1.0f);
}

void LevelUp_Free()
{
}

void LevelUp_Unload()
{
	AEGfxMeshFree(LevelMesh);

	AEGfxMeshFree(LevelButtons);

	AEGfxMeshFree(LevelTriLeft);

	AEGfxMeshFree(LevelTriRight);
}