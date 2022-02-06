#pragma once
#include <iostream>

struct MC_movement
{
	int MC_Xmovement = 0;
	int MC_Ymovement = 0;
};

void CreateMainCharacter(AEGfxVertexList*& MainCharacter, float cell_height, float cell_width);

void DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY);