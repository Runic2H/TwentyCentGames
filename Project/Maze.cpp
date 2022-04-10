/**************************************************************************
 * 	File name	:	Maze.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Louis Mineo				(PRIMARY AUTHOR - 80%)
 *					Hu Jun Ning				(SECONDARY AUTHOR - 15%)
 *					Matthew Cheung Jun Yin	(SECONDARY AUTHOR - 4%)
 *					Richmond Choo Tze Yong	(TERTIARY AUTHOR  - 0.5%)
 *					Elton Teo Zhe Wei		(TERTIARY AUTHOR  - 0.5%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

/******************************************************************************/
/*!
*	Start of all the vertexes used in the game
*/
/******************************************************************************/


AEGfxVertexList* pMeshCellOutline = 0;
AEGfxVertexList* pMeshMazeWindow = 0;
AEGfxVertexList* pMeshSolidSquare_PATH = 0;
AEGfxVertexList* pMeshSolidSquare_WALL = 0;
AEGfxVertexList* pMesh_MainCharacter = 0;
AEGfxVertexList* pMeshChest = 0;

// meshes for the minimap only
AEGfxVertexList* pMesh_MiniMapWindow = 0;
AEGfxVertexList* pMesh_MiniMapChests = 0;
AEGfxVertexList* pMesh_MiniMapMainChar = 0;
AEGfxVertexList* pMesh_MiniMapEndPt = 0;
/******************************************************************************/
/*!
*	End of all the vertexes used in the game
*/
/******************************************************************************/


AEGfxTexture* path_art;
AEGfxTexture* wall_art;
AEGfxTexture* main_character_art;
AEGfxTexture* chest_art;
AEGfxTexture* exit_art;



/******************************************************************************/
/*!
*	Global Declartions
*/
/******************************************************************************/
float global_var_minimap_height;

AEGfxVertexList* pMesh_ChestText= 0;
float chest_pickup_display_duration;
int chestopened_flag = 0;
std::string openchest_msg;

AEMtx33 defencepotiontransform, staminapotiontransform, healthpotiontransform;

float MC_positionX;
float MC_positionY;
extern int curr_X_GRIDposition;
extern int curr_Y_GRIDposition;
extern sys systemsettings;
extern int duck_dir;


float contact_rate = 0.2f;
float chest_spawn_rate = 0.2f;

float x_scaling = 1; //noOfRows/2.0f;
float y_scaling = 1; // noOfCols / 2.0f;

extern float global_maze_cam_x;
extern float global_maze_cam_y;
float cam_x, cam_y;


//test bench
extern int level_iter;
int noOfRows = level[level_iter], noOfCols = level[level_iter];


/* FOR MAZEGEN */
/*==================================================================================*/
extern Maze_Struct* Maze;
extern int maze_init_flag;

int start_x, start_y, end_x, end_y;

const int initial_wallcells_count = (((noOfCols - 2) - 1) / 2) * (((noOfRows - 2) - 1) / 2);

struct wallXY
{
	int x;
	int y;
};

std::vector<wallXY> MazeOGWalls_XY;


int maze_iswall_isnotwall[maxRows][maxCols];
int maze_visibility[maxRows][maxCols];

/******************************************************************************/
/*!
*	
*	This function loads the mesh for the chest texture to be set on.
* 
*/
/******************************************************************************/


void Maze_LOAD_DisplayChestPickupItemMESH()
{
	float width = 220.0f;
	float height = 20.0f;
	// creating the mesh to put the text in   0xFFA500FF
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, 0xFFA500FF, 0.0f, 1.0f,
		0, height, 0xFFA500FF, 0.0f, 0.0f,
		width, 0, 0xFFA500FF, 1.0f, 1.0f);
	AEGfxTriAdd(
		0, height, 0xFFA500FF, 0.0f, 0.0f,
		width, height, 0xFFA500FF, 1.0f, 0.0f,
		width, 0, 0xFFA500FF, 1.0f, 1.0f);
	pMesh_ChestText = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
*
*	This function draws the mesh with the chest texture.
*
*/
/******************************************************************************/

void Maze_ChestPickup_Draw(float cam_x, float cam_y, float x_offset, float y_offset)
{
	float func_starting_x = cam_x + x_offset;
	float func_starting_y = cam_y + y_offset;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetPosition(func_starting_x, func_starting_y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.8f);
	AEGfxMeshDraw(pMesh_ChestText, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
*
*  This function displays the text of what item the player picks from the chest.
*
*/
/******************************************************************************/

void Maze_DisplayChestPickupItem(std::string msg)
{

	Maze_ChestPickup_Draw(cam_x, cam_y, -100, 0);
	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer,"%s", msg.c_str());
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontId, strBuffer, -0.22f, 0, 1.0f, 1.0f, 1.0f, 1.0f);
	

	chest_pickup_display_duration -= DT;
}

/******************************************************************************/
/*!
*
*	This function loads the meshes which are used in the minimap.
*	i.e. the chests, the large window, the exit tile
*
*/
/******************************************************************************/

void Maze_Minimap_LoadMeshes(float &global_var_minimap_height)
{
	float window_height = (float)(AEGetWindowHeight()*0.75); 
	global_var_minimap_height = window_height;
	// This shape has 5 vertices
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, 0xFFFFFFFF, 0.0f, 1.0f,
		0, window_height, 0xFFFFFFFF, 0.0f, 0.0f,
		window_height, 0, 0xFFFFFFFF, 1.0f, 1.0f);
	AEGfxTriAdd(
		0, window_height, 0xFFFFFFFF, 0.0f, 0.0f,
		window_height, window_height, 0xFFFFFFFF, 1.0f, 0.0f,
		window_height, 0, 0xFFFFFFFF, 1.0f, 1.0f);
	pMesh_MiniMapWindow = AEGfxMeshEnd();



	float cells_size_x = window_height / noOfCols;
	float cells_size_y = window_height / noOfRows;
	// draw main char
	AEGfxMeshStart();
	// This shape has 5 vertices
	AEGfxTriAdd(
		0, 0, 0xFFFF0000, 0.0f, 1.0f,
		0, cells_size_y, 0xFFFF0000, 0.0f, 0.0f,
		cells_size_x, 0, 0xFFFF0000, 0.25f, 1.0f);
	AEGfxTriAdd(
		0, cells_size_y, 0xFFFF0000, 0.0f, 0.0f,
		cells_size_x, cells_size_y, 0xFFFF0000, 0.25f, 0.0f,
		cells_size_x, 0, 0xFFFF0000, 0.25f, 1.0f);
	pMesh_MiniMapMainChar = AEGfxMeshEnd();

	AEGfxMeshStart();
	// This shape has 5 vertices 0x964B0000
	AEGfxTriAdd(
		0, 0, 0xD27D2D00, 0.0f, 1.0f,
		0, cells_size_y, 0xD27D2D00, 0.0f, 0.0f,
		cells_size_x, 0, 0xD27D2D00, 1.0f, 1.0f);
	AEGfxTriAdd(
		0, cells_size_y, 0xD27D2D00, 0.0f, 0.0f,
		cells_size_x, cells_size_y, 0xD27D2D00, 1.0f, 0.0f,
		cells_size_x, 0, 0xD27D2D00, 1.0f, 1.0f);
	pMesh_MiniMapChests = AEGfxMeshEnd();

	AEGfxMeshStart();
	// This shape has 5 vertices 0xADD8E600
	AEGfxTriAdd(
		0, 0, 0xADD8E600, 0.0f, 1.0f,
		0, cells_size_y, 0xADD8E600, 0.0f, 0.0f,
		cells_size_x, 0, 0xADD8E600, 1.0f, 1.0f);
	AEGfxTriAdd(
		0, cells_size_y, 0xADD8E600, 0.0f, 0.0f,
		cells_size_x, cells_size_y, 0xADD8E600, 1.0f, 0.0f,
		cells_size_x, 0, 0xADD8E600, 1.0f, 1.0f);
	pMesh_MiniMapEndPt = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
*
*	This function prints the text " LEVEL X" at the tab-screen.
*
*/
/******************************************************************************/

void Maze_LevelText_Draw()
{

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer, "LEVEL %d",level_iter+1);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontLarge, strBuffer, -0.41f, 0.7f, 1.0f, 1.0f, 1.0f, 1.0f);
}

/******************************************************************************/
/*!
*
*	This function draws the minimap at the tab menu.
*
*/
/******************************************************************************/
void Maze_Minimap_Draw(float cam_x, float cam_y, float x_offset, float y_offset)
{
	float func_starting_x = cam_x + x_offset;
	float func_starting_y = cam_y + y_offset;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetPosition(func_starting_x, func_starting_y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);
	AEGfxMeshDraw(pMesh_MiniMapWindow, AE_GFX_MDM_TRIANGLES);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfRows; c++)
		{
			//AEGfxSetPosition(func_starting_x, func_starting_y);

			AEGfxSetPosition(
				(func_starting_x + (r * (global_var_minimap_height / noOfCols)))
				,
				(func_starting_y + (c * (global_var_minimap_height) / noOfRows))
			);
			

			

			if (r == curr_X_GRIDposition && c == curr_Y_GRIDposition) // is wall
			{

				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);
				AEGfxTextureSet(main_character_art, (float)(duck_dir * 0.25f), 0.0f);
				AEGfxMeshDraw(pMesh_MiniMapMainChar, AE_GFX_MDM_TRIANGLES);
			}
			else if (r == end_x && c == end_y)
			{
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);
				AEGfxTextureSet(exit_art, 0.0f, 0.0f);
				AEGfxMeshDraw(pMesh_MiniMapEndPt, AE_GFX_MDM_TRIANGLES);
			}
			else if (Maze->grid[r][c].value == CHEST)
			{
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.5f);
				AEGfxTextureSet(chest_art, 0.0f, 0.0f);
				AEGfxMeshDraw(pMesh_MiniMapChests, AE_GFX_MDM_TRIANGLES);
			}
			else
			{

			}
			AEGfxTextureSet(NULL, 0.0f, 0.0f);

		}
	}
}


/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, sets a boss
*	tiles at the final tile before preceding to the next level.
*
*/
/******************************************************************************/
void MazeGenAlgo_BossSpawn()
{
	maze_iswall_isnotwall[end_x][end_y - 1] = 5;
}


/******************************************************************************/
/*!
*
*	This function, spwawns enemy tiles in the binary map, after the maze has
*	been generated as a binary map. It take contact rate as the perecentage of
*	enemies to spawn out of all the non-wall tiles
*
*/
/******************************************************************************/
void Maze_EnemySpawn(float contact_rate)
{
	// count how many paths there are
	std::vector<int> path_x;
	std::vector<int> path_y;

	for (int r = 0; r < noOfRows; r++)
	{
		for (int c = 0; c < noOfCols; c++)
		{
			if (maze_iswall_isnotwall[r][c] == EMPTY_PATH)
			{
				if ((r == start_x && c == start_y))
				{

				}
				else if (r == end_x && c == end_y)
				{

				}
				else
				{
					path_x.push_back(r);
					path_y.push_back(c);
				}
			}
		}
	}

	int no_of_battles = (int)(path_x.size() * contact_rate);
	std::cout << no_of_battles << "out of " << path_x.size() << std::endl;

	int rand_index;

	srand((unsigned)time(NULL));
	while (no_of_battles > 0)
	{
		rand_index = rand() % path_x.size();

		maze_iswall_isnotwall[path_x[rand_index]][path_y[rand_index]] = 9;

		path_x.erase(path_x.begin() + rand_index);
		path_y.erase(path_y.begin() + rand_index);
		no_of_battles--;
	}
}


/******************************************************************************/
/*!
*
*	This function, spwawns chests in the binary map, after the maze has
*	been generated and the enemies has been spawned in the binary map. 
*	It take spawn rate as the perecentage of chests to spawn out of all the 
*	non-wall and non-enemy tiles
*
*/
/******************************************************************************/
void Maze_ChestSpawn(float spawn_rate)
{
	// count how many paths there are
	std::vector<int> path_x;
	std::vector<int> path_y;

	for (int r = 0; r < noOfRows; r++)
	{
		for (int c = 0; c < noOfCols; c++)
		{
			if (maze_iswall_isnotwall[r][c] == EMPTY_PATH)
			{
				if ((r == start_x && c == start_y))
				{
					// blank by design
				}
				else if (r == end_x && c == end_y)
				{
					// blank by design
				}
				else
				{
					path_x.push_back(r);
					path_y.push_back(c);
				}
			}
		}
	}

	int no_of_chests = (int)(path_x.size() * spawn_rate);					
	std::cout << no_of_chests << "out of " << path_x.size() << std::endl;

	int rand_index = 0;

	srand((unsigned)time(NULL));
	while (no_of_chests > 0)
	{
		int rand_index = rand() % path_x.size();

		maze_iswall_isnotwall[path_x[rand_index]][path_y[rand_index]] = 3;		// setting mapvalue to chest(3) in maze

		path_x.erase(path_x.begin() + rand_index);
		path_y.erase(path_y.begin() + rand_index);
		no_of_chests--;
	}

}

/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, creates an
*	outline of the maze, of size noOfRows and noOfCols, then creating a 
*	surrounding of walls and creating the starting and ending points as value
*	zero. It also pushes the xy of all the pre-determined walls 
*
*/
/******************************************************************************/

void MazeGenAlgo_MakeMaze()
{
	// draw the walls 
	for (int r = 0; r < noOfRows; r++)
	{
		for (int c = 0; c < noOfCols; c++)
		{

			if (r == 0 || r == noOfRows - 1)
			{
				maze_iswall_isnotwall[r][c] = 1;
			}
			else if (c == 0 || c == noOfCols - 1)
			{
				maze_iswall_isnotwall[r][c] = 1;
			}
			else if ((r % 2 == 0) && (c % 2 == 0))
			{
				maze_iswall_isnotwall[r][c] = 7;
				wallXY p = { r,c };
				MazeOGWalls_XY.push_back(p);
			}
			else
			{
				maze_iswall_isnotwall[r][c] = 0;
			}
		}
	}
	
}

/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, sets the
*	starting cell and ending cell, as well as use them as output values
*
*/
/******************************************************************************/

void MazeGenAlgo_ChoosingStartingPos(int& startX, int& startY, int& endX, int& endY, int height, int width)
{
	startX = ((width - 2) - 1) / 2 + 1;
	startY = 0;

	endX = startX;
	endY = height - 1;

	maze_iswall_isnotwall[start_x][start_y] = 0;
	maze_iswall_isnotwall[end_x][end_y] = 0;

	curr_X_GRIDposition = startX;
	curr_Y_GRIDposition = startY;
}

/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, uses the 
*	predetermined walls to set walls around it, at a random sequence. It will 
*	not re-set walls that have been set around them.
*
*/
/******************************************************************************/

void MazeGenAlgo_Set_walls()
{
	//std::cout << initial_wallcells_count << std::endl;
	//srand(time(NULL));


	while (MazeOGWalls_XY.size() != 0)
	{
		int wall_counter = 0;
		int rand_index = rand() % MazeOGWalls_XY.size();

		//std::cout << "rand x is " << MazeOGWalls_XY[rand_index].x << std::endl;
		//std::cout << "rand y is " << MazeOGWalls_XY[rand_index].y << std::endl;
		//std::cout << MazeOGWalls_XY.size() << "left" << std::endl << "------------" << std::endl;

		int wall_flag[4] = { 0,0,0,0 };
		if (maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x][MazeOGWalls_XY[rand_index].y - 1] != 0) { wall_flag[0] = 1; wall_counter++; } 	// UP 
		else if (maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x - 1][MazeOGWalls_XY[rand_index].y] != 0) { wall_flag[1] = 1;  wall_counter++; }// LEFT
		else if (maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x + 1][MazeOGWalls_XY[rand_index].y] != 0) { wall_flag[2] = 1;  wall_counter++; }// RIGHT
		else if (maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x][MazeOGWalls_XY[rand_index].y + 1] != 0) { wall_flag[3] = 1;  wall_counter++; }// DOWN
		for (int i = 0; i < 4; i++)
		{
			//std::cout << wall_flag[i];
		}
		// set wall
		int rand_wall = rand() % (4 - wall_counter); // 0-3 is the max
		int index = 0;
		while (rand_wall > 0)
		{
			if (wall_flag[index] == 0)
			{
				rand_wall--;
				index++;
			}
			else if (wall_flag[index] == 1)
			{
				index++;
			}
		}
		//std::cout << "\n" << index << std::endl;

		if (index == 0)
		{
			//std::cout << "Wall will be placed at top\n";
			maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x][MazeOGWalls_XY[rand_index].y - 1] = 1;
		}
		else if (index == 1)
		{
			//std::cout << "Wall will be placed at left\n";
			maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x - 1][MazeOGWalls_XY[rand_index].y] = 1;
		}
		else if (index == 2)
		{
			//std::cout << "Wall will be placed at right\n";
			maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x + 1][MazeOGWalls_XY[rand_index].y] = 1;
		}
		else if (index == 3)
		{
			//std::cout << "Wall will be placed at bot\n";
			maze_iswall_isnotwall[MazeOGWalls_XY[rand_index].x][MazeOGWalls_XY[rand_index].y + 1] = 1;
		}

		MazeOGWalls_XY.erase(MazeOGWalls_XY.begin() + rand_index);
		//std::cout << "\n";

		// change all walls to 1
		for (int r = 0; r < noOfRows; r++)
		{
			for (int c = 0; c < noOfCols; c++)
			{
				if (maze_iswall_isnotwall[r][c] != 0) maze_iswall_isnotwall[r][c] = 1;
			}
		}

		// if path is surrounded by walls, block out that path
		for (int r = 1; r < noOfRows-1; r++)
		{
			for (int c = 1; c < noOfCols-1; c++)
			{
				if (
					maze_iswall_isnotwall[r][c] == EMPTY_PATH // centre cell
					&&
					maze_iswall_isnotwall[r - 1][c - 1] == WALL && maze_iswall_isnotwall[r - 1][c] == WALL && maze_iswall_isnotwall[r - 1][c + 1] == WALL &&
					maze_iswall_isnotwall[r][c - 1] == WALL && maze_iswall_isnotwall[r][c + 1] == WALL &&
					maze_iswall_isnotwall[r + 1][c - 1] == WALL && maze_iswall_isnotwall[r + 1][c] == WALL && maze_iswall_isnotwall[r + 1][c + 1] == WALL
					)
				{
					maze_iswall_isnotwall[r][c] = 1 ;

				}
			}
		}

	}
}

/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, prints the 
*	binary map the generated maze, as well as its row and col values.
*
*/
/******************************************************************************/

void  MazeGenAlgo_PrintRetrievedInformation()
{
	std::cout << "Width " << noOfCols << std::endl;
	std::cout << "Height " << noOfRows << std::endl;
	for (int rows = noOfRows - 1; rows >= 0; rows--)
	{
		for (int cols = 0; cols < noOfCols; cols++)
		{
			if (cols < noOfCols - 1)
			{
				std::cout << maze_iswall_isnotwall[cols][rows] << " ";
				//std::cout << cols << ","<<  rows<< " ";
				//printf("%i ", Maze[cols][rows]);
			}
			else
			{
				//std::cout<< cols << ","<< rows << std::endl;
				std::cout << maze_iswall_isnotwall[cols][rows] << std::endl;
				//printf("%i\n", Maze[cols][rows]);
			}
		}
	}

}


/******************************************************************************/
/*!
*
*	This function, which is part of the maze generation algorith, checks if the
*	maze does not have a vertical empty rows from the starting pt to the ending
*	pt.
*
*/
/******************************************************************************/

bool MazeGenAlgo_PostGenCheck() // checks if the center col is not ALL PATH, returns true if not all path
{
	for (int i = 0; i < noOfRows; i++)
	{
		std::cout << maze_iswall_isnotwall[curr_X_GRIDposition][i];
		if (maze_iswall_isnotwall[curr_X_GRIDposition][i] == 1)
		{
			return true;
		}
	}
	return false;
	std::cout<<std::endl;
}


/******************************************************************************/
/*!
*
*	This function, is the compilation of the functions that create the Maze
*	Generation Algo. It will check if the maze does not have, a empty vertical 
*	row. Else, it will regenerate the maze.
*
*/
/******************************************************************************/
void MazeGenAlgo()
{
	srand((unsigned)time(NULL));
	MazeGenAlgo_MakeMaze();
	MazeGenAlgo_ChoosingStartingPos(start_x, start_y, end_x, end_y, noOfRows, noOfCols);
	MazeGenAlgo_Set_walls();
	MazeGenAlgo_BossSpawn();
	MazeGenAlgo_PrintRetrievedInformation();

	bool flag = MazeGenAlgo_PostGenCheck();
	
	while (!flag)
	{
		std::cout << "LOOP ENTERED" << std::endl;

		MazeGenAlgo_MakeMaze();
		MazeGenAlgo_ChoosingStartingPos(start_x, start_y, end_x, end_y, noOfRows, noOfCols);
		MazeGenAlgo_Set_walls();
		MazeGenAlgo_PrintRetrievedInformation();

		flag = MazeGenAlgo_PostGenCheck();
	}
	
	
	(flag) ? std::cout << "ALL OK" << std::endl : std::cout << "ONE COL STRAIGHT UP" << std::endl;
	MazeGenAlgo_BossSpawn();
	std::cout << "BOSS SPAWNED" << std::endl;
}




/******************************************************************************/
/*!
*
*	This function, creates the large Maze struct using the window widths and
*	height. As well as the count of rows and cols for the maze itself.
*
*/
/******************************************************************************/
Maze_Struct* CreateMaze(int Exe_WindowHeight, int Exe_WindowWidth, int noOfRows, int noOfCols)
{
	Maze_Struct* Maze = new Maze_Struct;


	//INITIALIZING THE DIMENSIONS STRUCT

	Maze->specifications.noOfRows = noOfRows;
	Maze->specifications.noOfCols = noOfCols;
	
	
	Maze->specifications.cellWidth = (float)Exe_WindowWidth /  6 ;
	Maze->specifications.cellHeight = Maze->specifications.cellWidth;//(float)Exe_WindowHeight / 6;
	
	Maze->specifications.mazeWindowHeight = Maze->specifications.cellHeight * noOfRows; //((float)Exe_WindowHeight / 6.0f) * 5 *y_scaling;
	Maze->specifications.mazeWindowWidth = Maze->specifications.cellWidth * noOfRows;//(float)Exe_WindowWidth / 2.0f * x_scaling;
	Maze->specifications.MazeWindowStart_X = -Maze->specifications.mazeWindowWidth/2;
	Maze->specifications.MazeWindowStart_Y = (Exe_WindowHeight / 6.0f * 5 / -2);  //(Exe_WindowHeight / 6.0f * 5 / -2);

	// Init the grid cells
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{

			Maze->grid[r][c].value = maze_iswall_isnotwall[r][c];

		}
	}
	return Maze;
}

/******************************************************************************/
/*!
*
*	This function, creates the mesh for the entire maze/window
*
*/
/******************************************************************************/

void MAZE_CreateMESH_MazeWindow2(AEGfxVertexList*& MazeWindow_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	// This shape has 5 vertices
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.mazeWindowWidth, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.mazeWindowHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	MazeWindow_Var = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
*
*	This function, creates the mesh of lines, that surround each cell in the 
*	maze.
*
*/
/******************************************************************************/

void MAZE_CreateMESH_CellOutline2(AEGfxVertexList*& CellOutlineMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, 0.0f, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f);
	AEGfxVertexAdd(0.0f, 0.0f, colour_HEXA, 0.0f, 0.0f);
	CellOutlineMesh_Var = AEGfxMeshEnd();
}

/******************************************************************************/
/*!
*
*	This function, creates the mesh of each cell in the maze.
*
*/
/******************************************************************************/

void MAZE_CreateSolidCell2(AEGfxVertexList*& SolidCellMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, colour_HEXA, 0.0f, 1.0f,
		0, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 1.0f, 1.0f);
	AEGfxTriAdd(
		0, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f,
		Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 0.0f,
		Maze->specifications.cellWidth, 0, colour_HEXA, 1.0f, 1.0f);
	SolidCellMesh_Var = AEGfxMeshEnd();
}


/******************************************************************************/
/*!
*
*	This function, draws the meshes containing the outline of the entire maze
*	and all the cells.
*
*/
/******************************************************************************/

void MAZE_DrawMazeCellsandCellOutline2(AEGfxVertexList* &WALLCellMesh,
	AEGfxVertexList* &PATHCellMesh,
	AEGfxVertexList* &CellOutlineMesh,
	Maze_Struct *Maze)
{
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{
			AEGfxSetPosition(
				(Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth)),
				(Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight))
			);

			if (Maze->grid[r][c].is_visible)
			{
				if (Maze->grid[r][c].value == WALL) // is wall
				{
					AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
					AEGfxTextureSet(wall_art, 0.0f, 0.0f);
					AEGfxMeshDraw(WALLCellMesh, AE_GFX_MDM_TRIANGLES);
				}
				else
				{
					AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
					AEGfxTextureSet(path_art, 0.0f, 0.0f);
					AEGfxMeshDraw(PATHCellMesh, AE_GFX_MDM_TRIANGLES);
				}

				if (Maze->grid[r][c].value == CHEST)
				{
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);

					AEGfxSetPosition(
						(Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth) + Maze->specifications.cellWidth / 2),
						(Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight) + Maze->specifications.cellHeight / 2)
					);
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxTextureSet(chest_art, 0, 0);
					AEGfxMeshDraw(pMeshChest, AE_GFX_MDM_TRIANGLES);
				}

				if (r == (end_x) && c == (end_y))
				{
					AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
					AEGfxTextureSet(exit_art, 0.0f, 0.0f);
					AEGfxMeshDraw(PATHCellMesh, AE_GFX_MDM_TRIANGLES);
				}
			}

			AEGfxSetPosition(
				Maze->specifications.MazeWindowStart_X + (r * Maze->specifications.cellWidth),
				Maze->specifications.MazeWindowStart_Y + (c * Maze->specifications.cellHeight)
			);
			AEGfxTextureSet(NULL, 0.0f, 0.0f);
			AEGfxMeshDraw(CellOutlineMesh, AE_GFX_MDM_LINES_STRIP);

		}
	}
}

/******************************************************************************/
/*!
*
*	This function, sets a certain cell in the maze as 0. which is usally called 
*	when a combat sequence intialiates.
*
*/
/******************************************************************************/

void MAZE_SetPosAsEmpty(Maze_Struct* Maze, int curr_X_GRIDposition, int curr_Y_GRIDposition )
{
	Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value = EMPTY_PATH;
	maze_iswall_isnotwall[curr_X_GRIDposition][curr_Y_GRIDposition] = EMPTY_PATH;
}

/******************************************************************************/
/*!
*
*	This function, draws the maze outline mesh.
*
*/
/******************************************************************************/

void MAZE_DrawMazeOutline2(AEGfxVertexList*& mazeOutlineMesh, Maze_Struct* Maze)
{
	AEGfxSetTransparency(1.0f);
	AEGfxSetPosition(Maze->specifications.MazeWindowStart_X, Maze->specifications.MazeWindowStart_Y);
	AEGfxMeshDraw(mazeOutlineMesh, AE_GFX_MDM_LINES_STRIP);
}


/******************************************************************************/
/*!
*
*	This function, creates the mesh of the main character in the maze
*
*/
/******************************************************************************/

void MAZE_CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 0.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 0.25f, 1.0f, //white
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 0.25f, 1.0f, //white
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 0.25f, 0.0f, //pink
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	pMesh_MainCharacter= AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create main character!!");
}

/******************************************************************************/
/*!
*
*	This function creates the mesh for the chests that will be rendered in the
*	maze
*
*/
/******************************************************************************/

void MAZE_CreateMESH_Chests(AEGfxVertexList*& pMeshChest, float cell_height, float cell_width)
{
	AEGfxMeshStart();
	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 0.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 0.0f, //pink
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	pMeshChest = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshChest, "fail to create chest!!");
}

/******************************************************************************/
/*!
*
*	This function draws the mesh for the main characters in the maze
*
*/
/******************************************************************************/

void MAZE_DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(main_character_art, (float)(duck_dir*0.25f), 0.0f);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
*
*	This function checks if the UDLR movements of the character is obstructed 
*	by a wall or not.
*
*/
/******************************************************************************/


int MAZE_CharMoveCHECK_NEXT_POS(int UpDownLeftRight, Maze_Struct* Maze, int& Char_Pos_X, int& Char_Pos_Y)
{
	switch (UpDownLeftRight)//1 is up, 2 is left, 3 is down, 3 is right
	{
	case 1: // move up aka y+1 
		if (Maze->grid[Char_Pos_X][Char_Pos_Y + 1].value != WALL && (Char_Pos_Y + 1) < Maze->specifications.noOfRows)
		{
			//std::cout << "Can move up" << "\n";
			Char_Pos_Y++;
			return 1;
		}
		else
		{
			//std::cout << "Cant move up to :" << Char_Pos_X << "-" << Char_Pos_Y + 1
				//<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y + 1].value << "\n";
			return 0;
		}
		break;
	case 2: // move left aka x-1
		if (Maze->grid[Char_Pos_X - 1][Char_Pos_Y].value != WALL && (Char_Pos_X - 1) >= 0)
		{
			//std::cout << "Can move left" << "\n";
			Char_Pos_X--;
			return 1;
		}
		else
		{
			//std::cout << "Cant move left to :" << Char_Pos_X - 1 << "-" << Char_Pos_Y
				//<< "because :" << Maze->grid[Char_Pos_X - 1][Char_Pos_Y].value << "\n";
			return 0;
		}
		break;
	case 3: // move down aka y-1
		if (Maze->grid[Char_Pos_X][Char_Pos_Y - 1].value != WALL && (Char_Pos_Y - 1) >= 0)
		{
			//std::cout << "Can move down" << "\n";
			Char_Pos_Y--;
			return 1;
		}
		else
		{
			//std::cout << "Cant move down to :" << Char_Pos_X << "-" << Char_Pos_Y - 1
				//<< "because :" << Maze->grid[Char_Pos_X][Char_Pos_Y - 1].value << "\n";
			return 0;
		}
		break;
	case 4: // move right aka x+1
		if (Maze->grid[Char_Pos_X + 1][Char_Pos_Y].value != WALL && (Char_Pos_X + 1) < Maze->specifications.noOfCols)
		{
			//std::cout << "Can move right" << "\n";
			Char_Pos_X++;
			return 1;
		}
		else
		{
			//std::cout << "Cant move right to :" << Char_Pos_X + 1 << "-" << Char_Pos_Y
				//<< "because :" << Maze->grid[Char_Pos_X + 1][Char_Pos_Y].value << "\n";
			return 0;
		}
		break;

	default: return 0;
	}

}


/******************************************************************************/
/*!
*
*	This function create the maze's fog of war, by setting the surrounding 8 
	cells as visible
*
*/
/******************************************************************************/

void MAZE_FogOfWar(int curr_X_GRIDposition, int curr_Y_GRIDposition)
{
	//std::cout << "\n\nPlayer's position x: " << curr_X_GRIDposition << "\n";
	//std::cout << "Player's position y: " << curr_Y_GRIDposition << "\n";


	//+1 -1 of player's position
	for (int a = -1; a < 2; ++a)
	{
		for (int b = -1; b < 2; ++b)
		{
			//check if the grid is within the boundaries
			if ( (curr_Y_GRIDposition + b) >= 0 &&
				 (curr_Y_GRIDposition + b) < Maze->specifications.noOfRows &&
				 (curr_X_GRIDposition + a) >= 0 &&
				 (curr_X_GRIDposition + a) < Maze->specifications.noOfCols)
			{
				//grids surrounding player will be visible	
				Maze->grid[curr_X_GRIDposition+a][curr_Y_GRIDposition+b].is_visible = 1;

				//std::cout << "position x: " << (curr_X_GRIDposition+b) << "     position y: " << (curr_Y_GRIDposition+a) << " is visible.\n\n";
			}
		}
	}
}

/******************************************************************************/
/*!
*
*	This function saves the current visibility binary map into a static
*	array, which is used when jumping between gamestates, while preserving the
*	specific visibility of the cells.
*
*/
/******************************************************************************/

void MAZE_SaveCellVisibility(Maze_Struct* maze_var)
{
	for (int r =0; r < maze_var->specifications.noOfRows; r++)
	{
		for (int c =0; c < maze_var->specifications.noOfRows; c++)
		{
			maze_visibility[r][c] = maze_var->grid[r][c].is_visible;
			maze_iswall_isnotwall[r][c]= maze_var->grid[r][c].value;
		}
	}
}


/******************************************************************************/
/*!
*
*	This function resets the current visibility binary map into a static
*	array, which is used when jumping between gamestates. 
*	i.e lvl1 to lvl2
*
*/
/******************************************************************************/
void MAZE_ResetCellVisibility(Maze_Struct* maze_var)
{
	for (int r = 0; r < maze_var->specifications.noOfRows; r++)
	{
		for (int c = 0; c < maze_var->specifications.noOfRows; c++)
		{
			maze_visibility[r][c] = 0;
		}
	}
}

/******************************************************************************/
/*!
*
*	This function copies the static array of the presevered visibility binary
*	map onto the maze's values.
*
*/
/******************************************************************************/

void MAZE_ReLOADCellVisibility(Maze_Struct* maze_var)
{
	for (int r=0; r < maze_var->specifications.noOfRows; r++)
	{
		for (int c=0; c < maze_var->specifications.noOfRows; c++)
		{
			maze_var->grid[r][c].is_visible = maze_visibility[r][c];
		}
	}
}


/******************************************************************************/
/*!
*
*	This function checks if the current cell that the main character is standing
*	on is a special cells. which can be combat, enemy boss combat, chests or 
*	whirlppol to the next level
*
*/
/******************************************************************************/
void MAZE_StepOntoSpecialCell(int curr_X_GRIDposition, int curr_Y_GRIDposition)
{

	if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == BOSS)
	{
		enemystats->EnemyType = ENEMYBOSS;
		next = COMBAT;
		global_maze_cam_x = cam_x;
		global_maze_cam_y = cam_y;
		MAZE_SaveCellVisibility(Maze);

		AEGfxSetCamPosition(0.0f, 0.0f);
	}

	if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == ENEMY)
	{
		next = COMBAT;
		global_maze_cam_x = cam_x;
		global_maze_cam_y = cam_y;
		MAZE_SaveCellVisibility(Maze);

		AEGfxSetCamPosition(0.0f, 0.0f);
	}

	if (curr_X_GRIDposition == end_x && curr_Y_GRIDposition == end_y)
	{
		if (level_iter < 3) {
			next = GS_RESTART;
			level_iter += 1;
			noOfCols = level[level_iter];
			noOfRows = level[level_iter];
			maze_init_flag = 0;
			MAZE_ResetCellVisibility(Maze);
			global_maze_cam_x = cam_x;
			global_maze_cam_y = cam_y;
			AEGfxSetCamPosition(0.0f, 0.0f);
		}

		else {
			next = VICTORY;
			maze_init_flag = 0;
			MAZE_ResetCellVisibility(Maze);
			global_maze_cam_x = cam_x;
			global_maze_cam_y = cam_y;
			AEGfxSetCamPosition(0.0f, 0.0f);
			level_iter = 0;
			noOfRows = level[level_iter];
			noOfCols = noOfRows;
		}
	}

	if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == CHEST)
	{
		chest_open_Audio();
		std::cout << "player is on chest" << std::endl;
		MAZE_ChestOpened(curr_X_GRIDposition, curr_Y_GRIDposition);				
	}
}


/******************************************************************************/
/*!
*
*	This function opens the chest and RNGs a potion for the main character. 
*	Then it uses flags to indicate that the chest has been opened, thus 
*	the binary map can be updated.
*
*/
/******************************************************************************/
void MAZE_ChestOpened(int curr_X_GRIDposition, int curr_Y_GRIDposition)
{
	Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value = EMPTY_PATH;
	std::cout << "Player has opened chest" << std::endl;

	int randindex;
	srand((unsigned)time(NULL));
	randindex = ( rand() % 3 ) + 1;
	if (randindex == 1)
	{
		playerinventory->healthpotion.itemcounter += 1;
		openchest_msg = "You have picked up 1 health potion!";
	}
	else if (randindex == 2)
	{
		playerinventory->staminapotion.itemcounter += 1;
		openchest_msg = "You have picked up 1 stamina potion!";
	}
	else if (randindex == 3)
	{
		playerinventory->defencepotion.itemcounter += 1;
		openchest_msg = "You have picked up 1 defence potion!";
	}

	chest_pickup_display_duration = 1.5f;
	chestopened_flag = 1;
}

/******************************************************************************/
/*!
*
*	This function uses directon to move the camera up, down, left right.
*
*/
/******************************************************************************/

void Maze_CameraAdjustment(int direction)
{
	float min_Cam_AA_x = cam_x - AEGetWindowWidth()/2 ;
	float min_Cam_AA_y = cam_y - AEGetWindowHeight()/2;
	float max_Cam_BB_x = cam_x + AEGetWindowWidth()/2;
	float max_Cam_BB_y = cam_y + AEGetWindowHeight()/2;

	if (direction == 1) // up
	{
		//if (MC_positionY + Maze->specifications.cellHeight > max_Cam_BB_y)
		if (MC_positionY + Maze->specifications.cellHeight /2 > max_Cam_BB_y)
		{
			std::cout << " camera move" << std::endl;
			AEGfxSetCamPosition(cam_x, cam_y + Maze->specifications.cellHeight);
		}
	}
	else if (direction == 2) // left
	{
		//if (MC_positionX - Maze->specifications.cellWidth < min_Cam_AA_x)
		if (MC_positionX - Maze->specifications.cellWidth/2 < min_Cam_AA_x)
		{
			std::cout << " camera move" << std::endl;
			AEGfxSetCamPosition(cam_x - Maze->specifications.cellWidth, cam_y );
		}
	}
	else if (direction == 3) // down
	{
		//if (MC_positionY - Maze->specifications.cellHeight < min_Cam_AA_y)
		if (MC_positionY - Maze->specifications.cellHeight / 2 < min_Cam_AA_y)
		{
			std::cout << " camera move" << std::endl;
			AEGfxSetCamPosition(cam_x, cam_y - Maze->specifications.cellHeight);
		}
	}
	else if (direction == 4) // right
	{
		//if (MC_positionX + Maze->specifications.cellWidth > max_Cam_BB_x)
		if (MC_positionX + Maze->specifications.cellWidth / 2 > max_Cam_BB_x)
		{
			std::cout << " camera move" << std::endl;
			AEGfxSetCamPosition(cam_x + Maze->specifications.cellWidth, cam_y);
		}
	}


	AEGfxGetCamPosition(&cam_x, &cam_y);
	std::cout << "cam X position is " << cam_x << "cam Y position is " << cam_y <<  std::endl;
}

/******************************************************************************/
/*!
*
*	This function updates the meshes of inventory in the TAB menu.
*
*/
/******************************************************************************/

void Maze_Inventory_MeshUpdate(float camX, float camY){
	
	AEMtx33 scale, rot, trans, buffer;

	AEMtx33Scale(&scale, 50.0f, 50.0f);
	AEMtx33Rot(&rot, 0.0f);
	AEMtx33Concat(&buffer, &scale, &rot);

	AEMtx33Trans(&trans, -300.0f + camX, 100.0f + camY);
	AEMtx33Concat(&defencepotiontransform, &trans, &buffer);

	AEMtx33Trans(&trans, -300.0f + camX, 0.0f + camY);
	AEMtx33Concat(&healthpotiontransform, &trans, &buffer);

	AEMtx33Trans(&trans, -300.0f + camX, -100.0f + camY);
	AEMtx33Concat(&staminapotiontransform, &trans, &buffer);
}


/******************************************************************************/
/*!
*
*	This function draws the meshes of the inventory when in TAB menu
*
*/
/******************************************************************************/
void Maze_Inventory_MeshRender() {

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxSetTransform(defencepotiontransform.m);
	AEGfxSetTransparency(1);
	AEGfxTextureSet(playerinventory->defencepotion.pTexture, 0, 0);
	AEGfxMeshDraw(playerinventory->defencepotion.pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(healthpotiontransform.m);
	AEGfxSetTransparency(1);
	AEGfxTextureSet(playerinventory->healthpotion.pTexture, 0, 0);
	AEGfxMeshDraw(playerinventory->healthpotion.pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransform(staminapotiontransform.m);
	AEGfxSetTransparency(1);
	AEGfxTextureSet(playerinventory->staminapotion.pTexture, 0, 0);
	AEGfxMeshDraw(playerinventory->staminapotion.pMesh, AE_GFX_MDM_TRIANGLES);

	char strBuffer[35];

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransparency(1.0f);

	sprintf_s(strBuffer, "Defence potion");
	AEGfxPrint(fontId, strBuffer, -0.84f, 0.43f, 1.0f, 0.9f, 0.9f, 1.0f);

	sprintf_s(strBuffer, "Health potion");
	AEGfxPrint(fontId, strBuffer, -0.84f, 0.1f, 1.0f, 1.0f, 0.9f, 0.9f);

	sprintf_s(strBuffer, "Stamina potion");
	AEGfxPrint(fontId, strBuffer, -0.84f, -0.23f, 1.0f, 0.9f, 1.0f, 0.9f);

	sprintf_s(strBuffer, "%0.0f", playerinventory->defencepotion.itemcounter);
	AEGfxPrint(fontId, strBuffer, -0.68f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f);

	sprintf_s(strBuffer, "%0.0f", playerinventory->healthpotion.itemcounter);
	AEGfxPrint(fontId, strBuffer, -0.68f, -0.07f, 1.0f, 0.9f, 1.0f, 0.9f);

	sprintf_s(strBuffer, "%0.0f", playerinventory->staminapotion.itemcounter);
	AEGfxPrint(fontId, strBuffer, -0.68f, -0.4f, 1.0f, 0.9f, 1.0f, 0.9f);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
}



/******************************************************************************/
/*!
*
*	Loads all assets in Level1. It should only be called once before the start of the level.
*	Opens and reads required files, and assigns values to necessary variables.
*
*/
/******************************************************************************/
void Maze_Load()
{
	std::cout << "Maze:Load" << std::endl;

	wall_art = AEGfxTextureLoad("Images/Wall.png");
	AE_ASSERT_MESG(wall_art, "Failed to create wall texture!\n");

	path_art = AEGfxTextureLoad("Images/Pond.png");
	AE_ASSERT_MESG(path_art, "Failed to create path texture!\n");

	main_character_art = AEGfxTextureLoad("Images/Map duck sprite.png");
	AE_ASSERT_MESG(main_character_art, "Failed to create path texture!\n");

	chest_art = AEGfxTextureLoad("Images/Chest.png");
	AE_ASSERT_MESG(chest_art, "Failed to create chest texture!\n");

	exit_art = AEGfxTextureLoad("Images/Whirlpool.png");
	AE_ASSERT_MESG(exit_art, "Failed to create chest texture!\n");
}





/******************************************************************************/
/*!
*
*	Initializes and sets the starting values of level1.
*	Ensures the input file stream opens correctly, and the values
*	are assigned accordingly to the variables.
*
*/
/******************************************************************************/
void Maze_Initialize()
{
	stop_Audio();
	maze_background_Audio();
	//initialise_pausemenu();

	AEToogleFullScreen(systemsettings.fullscreen); // R: added

	static float initialplayerCD = playerstats->resetCD;	//R: added, combat
	playerstats->resetCD = initialplayerCD;					// resets CD after combat

	if (maze_init_flag == 0)
	{
		std::cout << "Maze:Initialize" << std::endl;
		MazeGenAlgo();
		Maze_EnemySpawn(contact_rate);
		//MazeGenAlgo_BossSpawn();
		Maze_ChestSpawn(chest_spawn_rate);
		MazeGenAlgo_PrintRetrievedInformation();
		//AEGfxSetCamPosition(0.0f, 0.0f);
		Maze = CreateMaze(AEGetWindowHeight(), AEGetWindowWidth(), noOfRows, noOfCols);
	}
	else
	{
		cam_x = global_maze_cam_x; 
		cam_y = global_maze_cam_y;
		AEGfxSetCamPosition(cam_x, cam_y);
		Maze = CreateMaze(AEGetWindowHeight(), AEGetWindowWidth(), noOfRows, noOfCols);
		MAZE_ReLOADCellVisibility(Maze);
	}
	
	Maze_Minimap_LoadMeshes(global_var_minimap_height);
	Maze_LOAD_DisplayChestPickupItemMESH();
	MAZE_CreateMESH_MazeWindow2(pMeshMazeWindow, Maze, 0xFF0000);
	MAZE_CreateMESH_CellOutline2(pMeshCellOutline, Maze, 0xFFFFFFFF);
	MAZE_CreateSolidCell2(pMeshSolidSquare_WALL, Maze, 0x000000);
	MAZE_CreateSolidCell2(pMeshSolidSquare_PATH, Maze, 0x808080);
	MAZE_CreateMainCharacter(pMesh_MainCharacter, Maze->specifications.cellHeight, Maze->specifications.cellWidth);
	MAZE_CreateMESH_Chests(pMeshChest, Maze->specifications.cellHeight, Maze->specifications.cellWidth);

	MC_positionX = Maze->specifications.MazeWindowStart_X + (Maze->specifications.cellWidth / 2) + (curr_X_GRIDposition * Maze->specifications.cellWidth);

	MC_positionY = Maze->specifications.MazeWindowStart_Y + (Maze->specifications.cellHeight / 2) + (curr_Y_GRIDposition * Maze->specifications.cellHeight);
	std::cout << "X : " << MC_positionX << " --- Y : " << MC_positionY << std::endl;

	MAZE_SetPosAsEmpty(Maze, curr_X_GRIDposition, curr_Y_GRIDposition);
	
	maze_init_flag = 1; // make sure the game does not re-init after
						// exiting combat state

}



/******************************************************************************/
/*!
*
*	In charge of checking and updating the program.
*	Updates every frame. Part of the actual game loop for level1.
*	Contols the logic to end or restart the program.
*
*/
/******************************************************************************/
void Maze_Update()
{
	//std::cout << "Maze:Update" << std::endl;
	Audio_Update();

	if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 0) {
		click_Audio();
		systemsettings.paused = 1;
		global_maze_cam_x = cam_x;
		global_maze_cam_y = cam_y;
		AEGfxSetCamPosition(0.0f, 0.0f);
	}

	else if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 1) {
		click_Audio();
		systemsettings.paused = 0;
		//global_maze_cam_x = cam_x;
		//global_maze_cam_y = cam_y;
		AEGfxSetCamPosition(global_maze_cam_x, global_maze_cam_y);
	}


		AEGfxGetCamPosition(&cam_x, &cam_y);

	if (systemsettings.paused == 0 && systemsettings.exit_confirmation == 0) {
		if (AEInputCheckTriggered(AEVK_W))
		{
			duck_dir = DD_UP;
			if (MAZE_CharMoveCHECK_NEXT_POS(1, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
			{
				MC_positionY += Maze->specifications.cellHeight;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";

				Maze_CameraAdjustment(1);
				//AEGfxSetCamPosition(cam_x, cam_y + Maze->specifications.cellHeight);

				if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == EMPTY_PATH)
				{
					swimming_Audio();
				}
			}

			else wall_hit_Audio();
		}

		if (AEInputCheckTriggered(AEVK_S))
		{
			duck_dir = DD_DOWN;
			if (MAZE_CharMoveCHECK_NEXT_POS(3, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
			{
				MC_positionY -= Maze->specifications.cellHeight;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";


				Maze_CameraAdjustment(3);
				//AEGfxSetCamPosition(cam_x, cam_y - Maze->specifications.cellHeight);

				if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == EMPTY_PATH)
				{
					swimming_Audio();
				}
			}

			else wall_hit_Audio();
		}


		if (AEInputCheckTriggered(AEVK_A))
		{
			duck_dir = DD_LEFT;
			if (MAZE_CharMoveCHECK_NEXT_POS(2, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
			{

				MC_positionX -= Maze->specifications.cellWidth;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";


				Maze_CameraAdjustment(2);
				//AEGfxSetCamPosition(cam_x- Maze->specifications.cellWidth, cam_y);
			
				if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == EMPTY_PATH)
				{
					swimming_Audio();
				}
			}

			else wall_hit_Audio();
		}

		if (AEInputCheckTriggered(AEVK_D))
		{
			duck_dir = DD_RIGHT;
			if (MAZE_CharMoveCHECK_NEXT_POS(4, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
			{

				MC_positionX += Maze->specifications.cellWidth;
				std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
					"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";

				Maze_CameraAdjustment(4);
				//AEGfxSetCamPosition(cam_x + Maze->specifications.cellWidth, cam_y);
			
				if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == EMPTY_PATH)
				{
					swimming_Audio();
				}
			}

			else wall_hit_Audio();
		}

		MAZE_FogOfWar(curr_X_GRIDposition, curr_Y_GRIDposition);

		//go back to MENU
		if (AEInputCheckTriggered(AEVK_Q))
		{

			AEGfxSetCamPosition(0.0f, 0.0f);
			next = MENU;
			curr_X_GRIDposition = start_x;
			curr_Y_GRIDposition = start_y;

		}

		MAZE_StepOntoSpecialCell(curr_X_GRIDposition, curr_Y_GRIDposition);
		AEGfxGetCamPosition(&cam_x, &cam_y);
	}

	else if (systemsettings.exit_confirmation == 1) {
		LogicExit_Confirmation();
	}
	else {
		logicpausemenu();
	}
}


/******************************************************************************/
/*!
*
*	Updates every frame together with the update function.
*	Draws the updated logic from the update function.
*
*/
/******************************************************************************/
void Maze_Draw()
{
	//std::cout << "Maze:Draw" << std::endl;
	if (systemsettings.paused == 0 && systemsettings.exit_confirmation == 0) {

		if (AEInputCheckCurr(AEVK_TAB)) {
			Maze_Inventory_MeshUpdate(cam_x, cam_y);
			Maze_Inventory_MeshRender();
			Maze_Minimap_Draw(cam_x, cam_y, -160.0f, -250.0f);
			Maze_LevelText_Draw();
		}
		else {
			MAZE_DrawMazeCellsandCellOutline2(pMeshSolidSquare_WALL,
				pMeshSolidSquare_PATH,
				pMeshCellOutline,
				Maze
			);

			//must draw
			MAZE_DrawMazeOutline2(pMeshMazeWindow, Maze); //AEGFX MeshDrawMode MDM != AEGFX RenderMode RM
			MAZE_DrawingMainCharacter(pMesh_MainCharacter, MC_positionX, MC_positionY);
			
			char strBuffer[100];
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0); // No texture for object
			sprintf_s(strBuffer, "Press TAB to view minimap and inventory");
			AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 1.f, 1.f);


			if (chest_pickup_display_duration > 0)
			{
				Maze_DisplayChestPickupItem(openchest_msg);
			}
			else
			{
				chest_pickup_display_duration = 0;
			}
		}
	}

	if (systemsettings.paused == 1) {
		renderpausemenu();
	}

	else if (systemsettings.exit_confirmation == 1) {
		RenderExit_Confirmation();
	}
}

/******************************************************************************/
/*!
*
*	Cleans game object instances.
*
*/
/******************************************************************************/
void Maze_Free()
{
	std::cout << "Maze:Free" << std::endl;
	AEGfxMeshFree(pMeshCellOutline);
	AEGfxMeshFree(pMeshMazeWindow);
	AEGfxMeshFree(pMeshSolidSquare_PATH);
	AEGfxMeshFree(pMeshSolidSquare_WALL);
	AEGfxMeshFree(pMesh_MainCharacter);
	AEGfxMeshFree(pMeshChest);
	AEGfxMeshFree(pMesh_ChestText);
	//unloadpausemenu();

	AEGfxMeshFree(pMesh_MiniMapChests);
	AEGfxMeshFree(pMesh_MiniMapMainChar);
	AEGfxMeshFree(pMesh_MiniMapWindow);
	AEGfxMeshFree(pMesh_MiniMapEndPt);

	delete(Maze);
}

/******************************************************************************/
/*!
*
*	Unload game assets. Frees and releases memory
*
*/
/******************************************************************************/
void Maze_Unload()
{
	std::cout << "Maze:Unload" << std::endl;
	AEGfxTextureUnload(wall_art);
	AEGfxTextureUnload(path_art);
	AEGfxTextureUnload(main_character_art);
	AEGfxTextureUnload(chest_art);
	AEGfxTextureUnload(exit_art);
}
