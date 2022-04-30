/**************************************************************************
 * 	File name	:	Tutorial.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Matthew Cheung Jun Yin	(PRIMARY AUTHOR - 90%)
					Hu Jun Ning				(SECONDARY AUTHOR - 10%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/


/**************************************************************
*	creates meshes
***************************************************************/
void CreatingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width);

/**************************************************************
*	draws the meshes
***************************************************************/
void DrawingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY);

/**************************************************************
*	draws the meshes
***************************************************************/
void DrawingTextureOnMesh(AEGfxVertexList*& pMesh_MainCharacter, AEGfxTexture* texture_var, float MC_positionX, float MC_positionY);

/**************************************************************
*	creates the meshes
***************************************************************/
void CreatingImageMesh(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width);

/**************************************************************
*	load function for the tutorial
***************************************************************/
void Tutorial_Load();

/**************************************************************
*	init function for the tutorial
***************************************************************/
void Tutorial_Init();

/**************************************************************
*	update function for the tutorial
***************************************************************/
void Tutorial_Update();

/**************************************************************
*	draw function for the tutorial
***************************************************************/
void Tutorial_Draw();

/**************************************************************
*	free function for the tutorial
***************************************************************/
void Tutorial_Free();

/**************************************************************
*	unload function for the tutorial
***************************************************************/
void Tutorial_Unload();

/**************************************************************
*	frees the meshes
***************************************************************/
void meshfree();
