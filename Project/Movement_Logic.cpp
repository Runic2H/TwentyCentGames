#include "AEEngine.h"
#include "Movement_logic.h"
#include "Maze.h"

void CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue


	AEGfxTriAdd( 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create main character!!");
}

void DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}