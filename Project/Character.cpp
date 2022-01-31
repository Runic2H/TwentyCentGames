#include "pch.h"

namespace Character
{
	AEGfxVertexList* GridStart = 0;
	//AEGfxVertexList* GridTop = 0;
	//AEGfxVertexList* GridBottom = 0;
	//AEGfxVertexList* GridBack = 0;
	//AEGfxVertexList* GridFront = 0;

	c_statsheet* c_initialize()
	{
		c_statsheet* c_stats = new c_statsheet;
		return c_stats;
	}

	void renderGrid()
	{
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxTriAdd(
			-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
			30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
			-30.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
			30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
			-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

		// Saving the mesh (list of triangles) in pMesh2

		GridStart = AEGfxMeshEnd();
	}
}