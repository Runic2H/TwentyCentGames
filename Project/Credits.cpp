#include "pch.hpp"

//AEGfxVertexList* line;

void Credits_Load()
{
	////middle line
	//AEGfxMeshStart();
	//AEGfxVertexAdd(-200, 299, 0x00FF00FF, 0.0f, 0.0f);
	//AEGfxVertexAdd(-200, -299, 0x00FFFF00, 0.0f, 0.0f);
	//line = AEGfxMeshEnd();
}

void Credits_Init()
{

}

void Credits_Update()
{
	//go back to MENU
	if (AEInputCheckTriggered(AEVK_Q))
	{
		next = MENU;
	}
}

void Credits_Draw()
{
	char strBuffer[1000];
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(strBuffer, "Credits");
	AEGfxPrint(fontId, strBuffer, -0.06f, 0.9f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved");
	AEGfxPrint(fontId, strBuffer, -0.51f, -0.96f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Team members");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.78f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Elton Teo Zhe Wei");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.70f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Louis Mineo @ Linn Min Htoo");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.64f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Richmond Choo Tze Yong");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.58f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Hu Jun Ning");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.52f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Matthew Cheung");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.46f, 1.0f, 1.f, 1.f, 1.f);

	//-12
	sprintf_s(strBuffer, "Instructors");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.34f, 1.0f, 1.f, 1.f, 1.f);

	//-1
	sprintf_s(strBuffer, "Software Engineering Project 2");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.26f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Gerald Wong Han Feng");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.2f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Cheng Ding Xiang");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.14f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Math");
	AEGfxPrint(fontId, strBuffer, -0.85f, 0.04f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Michael Daniel Samson");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.02f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Wu Yi Lin");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.08f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.14f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "High Level Programming 2");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.24f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Prasanna Ghali");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.3f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Vadim Surov");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.36f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Jeremy Chew");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.42f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Game Implementation Techniques");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.52f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Elie Hosry");
	AEGfxPrint(fontId, strBuffer, -0.85f, -0.58f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Interpersonal and Work Communication");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.78f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Francis Hau");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.72f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prof Thanusha Raj");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.66f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "President");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.54f, 1.0f, 1.f, 1.f, 1.f);
		
	sprintf_s(strBuffer, "Claude Comair");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.48f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Vice-Presidents");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.38f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Micheal Comair");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.32f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "John Bauer");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.26f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Melvin Gonsalves");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.2f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Angela Kugler");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.14f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Johnny Deek");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.08f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Ben Ellinger");
	AEGfxPrint(fontId, strBuffer, -0.15f, 0.02f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Dr. Charles Duba");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.04f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Raymond Yan");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.1f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Executives");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.16f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Micheal Gats");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.26f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Samir Abou");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.32f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Samra");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.38f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Dr. Erik");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.44f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Mohrmann");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.5f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Jason Chu");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.56f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Prasanna Ghali");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.62f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Christopher");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.68f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Comair");
	AEGfxPrint(fontId, strBuffer, -0.15f, -0.74f, 1.0f, 1.f, 1.f, 1.f);


	sprintf_s(strBuffer, "Apps used");
	AEGfxPrint(fontId, strBuffer, 0.55f, 0.78f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Visual Studio 2019");
	AEGfxPrint(fontId, strBuffer, 0.55f, 0.72f, 1.0f, 1.f, 1.f, 1.f);

	sprintf_s(strBuffer, "Sketchbook");
	AEGfxPrint(fontId, strBuffer, 0.55f, 0.66f, 1.0f, 1.f, 1.f, 1.f);

	//line
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetPosition(0.0f, 0.0f);
	//AEGfxTextureSet(NULL, 0, 0); // No texture for object
	//AEGfxMeshDraw(line, AE_GFX_MDM_LINES_STRIP);
}

void Credits_Free()
{
	//AEGfxMeshFree(line);
}

void Credits_Unload()
{

}