
void CreatingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width);

void DrawingMazeOverview(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY);

void DrawingTextureOnMesh(AEGfxVertexList*& pMesh_MainCharacter, AEGfxTexture* texture_var, float MC_positionX, float MC_positionY);
void CreatingImageMesh(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width);

void Tutorial_Load();

void Tutorial_Init();

void Tutorial_Update();

void Tutorial_Draw();

void Tutorial_Free();

void Tutorial_Unload();

void meshfree();