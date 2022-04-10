#include "pch.hpp"

//variables
/* Define */
int credits_page{ 1 };
enum credits_pages { credits_page_1 = 1, credits_page_2, credits_page_3, credits_page_4, credits_page_5, credits_page_6, credits_page_7 };

extern sys systemsettings;

/*	Objects	*/
AEGfxVertexList* team_logo;
AEGfxVertexList* audacity_and_sketchbook_mesh;
AEGfxVertexList* fmod_mesh;
AEGfxVertexList* button_box_at_credits;

AEGfxTexture* team_logo_art;
AEGfxTexture* sketchbook_logo_art;
AEGfxTexture* audacity_logo_art;
AEGfxTexture* fmod_logo_art;

void Draw_left_button_box()
{
	//drawing previous page box (left)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(-(float)(AEGetWindowHeight() * 0.335), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box_at_credits, AE_GFX_MDM_LINES_STRIP);
}

void Draw_right_button_box()
{
	//drawing next page button boxes (right)
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition((float)(AEGetWindowHeight() * 0.475), (float)-(AEGetWindowHeight() * 21 / 60));
	AEGfxTextureSet(NULL, 0, 0); // No texture for object
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	AEGfxMeshDraw(button_box_at_credits, AE_GFX_MDM_LINES_STRIP);
}

void credits_page_one_code()
{
	//Draw team logo
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//AEGfxSetPosition(-10.0f, 50.0f);
	AEGfxSetPosition((float)-(AEGetWindowWidth() * 0.0125), (float)(AEGetWindowHeight() *1/12));
	AEGfxTextureSet(team_logo_art, 0, 0);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(team_logo, AE_GFX_MDM_TRIANGLES);

	Draw_right_button_box();



	char strBuffer[1000];
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Created by");
	AEGfxPrint(fontLarge, strBuffer, -0.2f, 0.65f, 0.50f, 0.678f, 0.847f, 0.902f);

	sprintf_s(strBuffer, "Elton Teo Zhe Wei");
	AEGfxPrint(fontId, strBuffer, -0.12f, -0.42f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Louis Mineo @ Linn Min Htoo");
	AEGfxPrint(fontId, strBuffer, -0.2f, -0.48f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Richmond Choo Tze Yong");
	AEGfxPrint(fontId, strBuffer, -0.178f, -0.54f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Hu Jun Ning");
	AEGfxPrint(fontId, strBuffer, -0.09f, -0.6f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Matthew Cheung");
	AEGfxPrint(fontId, strBuffer, -0.115f, -0.66f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved");
	AEGfxPrint(fontId, strBuffer, -0.51f, -0.96f, 1.0f, 1.f, 0.831f, 0.36f);
}

void credits_page_two_code()
{
	Draw_left_button_box();
	Draw_right_button_box();



	char strBuffer[1000];
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Faculty and Advisors");
	AEGfxPrint(fontLarge, strBuffer, -0.39f, 0.65f, 0.50f, 0.678f, 0.847f, 0.902f);



	sprintf_s(strBuffer, "High Level Programming");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.5f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Prasanna Ghali");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.44f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Fang Liu");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.38f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Slawomir Wlodkowski");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.32f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Vadim Surov");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.26f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Jeremy Chew");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.2f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Mathematics");
	AEGfxPrint(fontId, strBuffer, -0.6f, 0.f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Micheal Yahn");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.06f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Micheal Daniel Samson");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.12f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Wu Yilin");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.18f, 1.0f, 1.f, 1.f, 1.f);

	

	sprintf_s(strBuffer, "Software Engineering Project");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.38f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Gerald Wong Han Feng");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.44f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Cheng Ding Xiang");
	AEGfxPrint(fontId, strBuffer, -0.6f, -0.5f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Humanities and Social Sciences");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.5f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Dr. Sim Jiaying");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.44f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Yasmin Merchant");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.38f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Thanusha Raj");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.32f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Francis Hau");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.26f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Game Implementation Techniques");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.06f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Elie Hosry");
	AEGfxPrint(fontId, strBuffer, 0.2f, 0.f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Computer Environment");
	AEGfxPrint(fontId, strBuffer, 0.2f, -0.2f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "Vadim Surov");
	AEGfxPrint(fontId, strBuffer, 0.2f, -0.26f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Ng Kian Ann");
	AEGfxPrint(fontId, strBuffer, 0.2f, -0.32f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved");
	AEGfxPrint(fontId, strBuffer, -0.51f, -0.96f, 1.0f, 1.f, 0.831f, 0.36f);
}

void credits_page_three_code()
{
	Draw_left_button_box();
	Draw_right_button_box();



	char strBuffer[1000];
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Created at DigiPen Institute of Technology Singapore");
	AEGfxPrint(fontLarge, strBuffer, -0.79f, 0.65f, 0.4f, 0.678f, 0.847f, 0.902f);



	sprintf_s(strBuffer, "President");
	AEGfxPrint(fontLarge, strBuffer, -0.11f, 0.4f, 0.30f, 0.678f, 0.847f, 0.902f);

	sprintf_s(strBuffer, "Claude Comair");
	AEGfxPrint(fontId, strBuffer, -0.1f, 0.34f, 1.f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Executives");
	AEGfxPrint(fontLarge, strBuffer, -0.12f, 0.14f, 0.30f, 0.678f, 0.847f, 0.902f);

	sprintf_s(strBuffer, "Michael Gats");
	AEGfxPrint(fontId, strBuffer, -0.09f, 0.08f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Samir Abou Samra");
	AEGfxPrint(fontId, strBuffer, -0.13f, 0.02f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Dr. Erik Mohrmann");
	AEGfxPrint(fontId, strBuffer, -0.129f, -0.04f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Dr. Charles Duba");
	AEGfxPrint(fontId, strBuffer, -0.115f, -0.1f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Jason Chu");
	AEGfxPrint(fontId, strBuffer, -0.075f, -0.16f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prasanna Ghali");
	AEGfxPrint(fontId, strBuffer, -0.105f, -0.22f, 1.f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Melvin Gonsalvez");
	AEGfxPrint(fontId, strBuffer, -0.12f, -0.28f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Ben Ellinger");
	AEGfxPrint(fontId, strBuffer, -0.08f, -0.34f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Christopher Comair");
	AEGfxPrint(fontId, strBuffer, -0.135f, -0.4f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Raymond Yan");
	AEGfxPrint(fontId, strBuffer, -0.095f, -0.46f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "John Bauer");
	AEGfxPrint(fontId, strBuffer, -0.08f, -0.52f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Angela Kugler");
	AEGfxPrint(fontId, strBuffer, -0.098f, -0.58f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Johnny Deek");
	AEGfxPrint(fontId, strBuffer, -0.09f, -0.64f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press D for next page");
	AEGfxPrint(fontId, strBuffer, 0.465f, -0.720f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved");
	AEGfxPrint(fontId, strBuffer, -0.51f, -0.96f, 1.0f, 1.f, 0.831f, 0.36f);
}

void credits_page_four_code()
{	
	//Draw sketchbook logo
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition((float)-(AEGetWindowWidth()/8), (float)(AEGetWindowHeight()/12));
	AEGfxTextureSet(sketchbook_logo_art, 0, 0);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(audacity_and_sketchbook_mesh, AE_GFX_MDM_TRIANGLES);

	//Draw audacity logo
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition((float)(AEGetWindowWidth() / 8), (float)(AEGetWindowHeight() / 12));
	AEGfxTextureSet(audacity_logo_art, 0, 0);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(audacity_and_sketchbook_mesh, AE_GFX_MDM_TRIANGLES);

	//Draw fmod logo
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition((float)-(AEGetWindowWidth() * 0.13125), (float)-(AEGetWindowHeight()*0.25));
	AEGfxTextureSet(fmod_logo_art, 0, 0);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxSetTransparency(1);
	AEGfxMeshDraw(fmod_mesh, AE_GFX_MDM_TRIANGLES);

	Draw_left_button_box();



	char strBuffer[1000];
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Apps used");
	AEGfxPrint(fontLarge, strBuffer, -0.2f, 0.65f, 0.50f, 0.678f, 0.847f, 0.902f);

	sprintf_s(strBuffer, "FMOD Sound System by FireLight Technologies Pty Ltd (1998 - 2022)");
	AEGfxPrint(fontId, strBuffer, -0.469f, -0.6f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Audacity");
	AEGfxPrint(fontId, strBuffer, 0.2f, -0.05f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Sketchbook");
	AEGfxPrint(fontId, strBuffer, -0.33f, -0.05f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press A for last page");
	AEGfxPrint(fontId, strBuffer, -0.745f, -0.720f, 1.0f, 1.f, 1.f, 1.f);



	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 0.831f, 0.36f);

	sprintf_s(strBuffer, "All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved");
	AEGfxPrint(fontId, strBuffer, -0.51f, -0.96f, 1.0f, 1.f, 0.831f, 0.36f);
}

void Credits_Load()
{
	//team logo
	AEGfxMeshStart();
	AEGfxTriAdd(
		-(float)(AEGetWindowHeight()*0.25), -(float)(AEGetWindowHeight() * 0.25), 0x00FF00FF, 0.f, 1.f,
		-(float)(AEGetWindowHeight() * 0.25), (float)(AEGetWindowHeight() * 0.25), 0x00FFFFFF, 0.f, 0.f,
		(float)(AEGetWindowHeight() * 0.25), (float)(AEGetWindowHeight() * 0.25), 0x0000FFFF, 1.f, 0.f);

	AEGfxTriAdd(
		-(float)(AEGetWindowHeight() * 0.25), -(float)(AEGetWindowHeight() * 0.25), 0x00FFFFFF, 0.f, 1.f,
		(float)(AEGetWindowHeight() * 0.25), (float)(AEGetWindowHeight() * 0.25), 0x00FF00FF, 1.f, 0.f,
		(float)(AEGetWindowHeight() * 0.25), -(float)(AEGetWindowHeight() * 0.25), 0x0000FFFF, 1.f, 1.f);

	team_logo = AEGfxMeshEnd();
	AE_ASSERT_MESG(team_logo, "Failed to create team logo!!");

	//audacity and sketckbook mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-(float)(AEGetWindowWidth()*0.0625), -(float)(AEGetWindowWidth() * 0.0625), 0x00FF00FF, 0.f, 1.f,
		-(float)(AEGetWindowWidth() * 0.0625), (float)(AEGetWindowWidth() * 0.0625), 0x00FFFFFF, 0.f, 0.f,
		(float)(AEGetWindowWidth() * 0.0625), (float)(AEGetWindowWidth() * 0.0625), 0x0000FFFF, 1.f, 0.f);

	AEGfxTriAdd(
		-(float)(AEGetWindowWidth() * 0.0625), -(float)(AEGetWindowWidth() * 0.0625), 0x00FFFFFF, 0.f, 1.f,
		(float)(AEGetWindowWidth() * 0.0625), (float)(AEGetWindowWidth() * 0.0625), 0x00FF00FF, 1.f, 0.f,
		(float)(AEGetWindowWidth() * 0.0625), -(float)(AEGetWindowWidth() * 0.0625), 0x0000FFFF, 1.f, 1.f);

	audacity_and_sketchbook_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(audacity_and_sketchbook_mesh, "Failed to create audacity and sketchbook mesh!!");

	//fmod mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, 0x00FF00FF, 0.f, 1.f,
		0, (float)(AEGetWindowHeight()*0.096), 0x00FFFFFF, 0.f, 0.f,
		(float)(AEGetWindowWidth()*0.273), (float)(AEGetWindowHeight() * 0.096), 0x0000FFFF, 1.f, 0.f);

	AEGfxTriAdd(
		0, 0, 0x00FFFFFF, 0.f, 1.f,
		(float)(AEGetWindowWidth() * 0.273), (float)(AEGetWindowHeight() * 0.096), 0x00FF00FF, 1.f, 0.f,
		(float)(AEGetWindowWidth() * 0.273), 0, 0x0000FFFF, 1.f, 1.f);

	fmod_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(fmod_mesh, "Failed to create fmod mesh!!");

	//new button box
	AEGfxMeshStart();
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), ((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), ((float)AEGetWindowHeight() * 1 / 30), 0x0000FFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(((float)AEGetWindowHeight() * 1 / 30), -((float)AEGetWindowHeight() * 1 / 30), 0x00FF00FF, 0.0f, 0.0f);
	AEGfxVertexAdd(-((float)AEGetWindowHeight() * 2 / 12), -((float)AEGetWindowHeight() * 1 / 30), 0x00FFFF00, 0.0f, 0.0f);

	button_box_at_credits = AEGfxMeshEnd();
	AE_ASSERT_MESG(button_box_at_credits, "Failed to create button mesh!!");


	team_logo_art = AEGfxTextureLoad("Images/TwentyCent Games logo.png");
	AE_ASSERT_MESG(team_logo_art, "Failed to create team logo texture!\n");

	fmod_logo_art = AEGfxTextureLoad("Images/FMOD Logo White - Black Background.png");
	AE_ASSERT_MESG(fmod_logo_art, "Failed to create fmod logo texture!\n");

	audacity_logo_art = AEGfxTextureLoad("Images/Audacity_Logo_nofilter.png");
	AE_ASSERT_MESG(audacity_logo_art, "Failed to create audacity logo texture!\n");

	sketchbook_logo_art = AEGfxTextureLoad("Images/Sketchbook logo.png");
	AE_ASSERT_MESG(sketchbook_logo_art, "Failed to create sketchbook logo texture!\n");
}

void Credits_Init()
{
	credits_page = 1;

	AEGfxSetCamPosition(0.f, 0.f);
}

void Credits_Update()
{
	Audio_Update();
	increase_bgm_fader();
	decrease_bgm_fader();
	//mute_master_fader();
	//unmute_master_fader();

	//go back to MENU
	if (AEInputCheckTriggered(AEVK_Q))
	{
		next = MENU;
	}

	if (AEInputCheckTriggered(AEVK_A))
	{
		if (--credits_page) page_flip1_Audio();
		if (credits_page < 1)
		{
			credits_page = 1;
		}
	}

	if (AEInputCheckTriggered(AEVK_D))
	{
		++credits_page;

		if (credits_page <= 4) {
			page_flip2_Audio();
		}

		if (credits_page > 4)
		{
			credits_page = 4;
		}
	}
}

void Credits_Draw()
{
	switch (credits_page) {
	case credits_page_1: credits_page_one_code();
		break;

	case credits_page_2: credits_page_two_code();
		break;

	case credits_page_3: credits_page_three_code();
		break;

	case credits_page_4: credits_page_four_code();
		break;
	}
}

void Credits_Free()
{
	AEGfxMeshFree(team_logo);
	AEGfxMeshFree(audacity_and_sketchbook_mesh);
	AEGfxMeshFree(fmod_mesh);
	AEGfxMeshFree(button_box_at_credits);

	//if (Mesh_maze_overview != nullptr) {
	//	AEGfxMeshFree(Mesh_maze_overview);
	//	Mesh_maze_overview = nullptr;
	//}
}

void Credits_Unload()
{
	AEGfxTextureUnload(team_logo_art);
	AEGfxTextureUnload(fmod_logo_art);
	AEGfxTextureUnload(audacity_logo_art);
	AEGfxTextureUnload(sketchbook_logo_art);
}