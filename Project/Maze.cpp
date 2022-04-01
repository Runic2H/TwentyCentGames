#include "pch.hpp"

AEGfxVertexList* pMeshCellOutline = 0;
AEGfxVertexList* pMeshMazeWindow = 0;
AEGfxVertexList* pMeshSolidSquare_PATH = 0;
AEGfxVertexList* pMeshSolidSquare_WALL = 0;

AEGfxTexture* path_art;
AEGfxTexture* wall_art;
AEGfxTexture* main_character_art;

float MC_positionX;
float MC_positionY;
AEGfxVertexList* pMesh_MainCharacter = 0;
extern int curr_X_GRIDposition;
extern int curr_Y_GRIDposition;
extern sys systemsettings;


float contact_rate = 0.3f;
float chest_spawn_rate = 0.3f;

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

/*
int maze_iswall_isnotwall[noOfRows][noOfCols];
int maze_visibility[noOfRows][noOfCols];
*/
int maze_iswall_isnotwall[maxRows][maxCols];
int maze_visibility[maxRows][maxCols];


void MazeGenAlgo_BossSpawn()
{
	maze_iswall_isnotwall[end_x][end_y - 1] = 5;
}

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

	srand(time(NULL));
	while (no_of_battles > 0)
	{
		rand_index = rand() % path_x.size();

		maze_iswall_isnotwall[path_x[rand_index]][path_y[rand_index]] = 9;

		path_x.erase(path_x.begin() + rand_index);
		path_y.erase(path_y.begin() + rand_index);
		no_of_battles--;
	}

}

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

	int no_of_chests = (int)(path_x.size() * spawn_rate);
	std::cout << no_of_chests << "out of " << path_x.size() << std::endl;

	int rand_index;

	srand(time(NULL));
	while (no_of_chests > 0)
	{
		int rand_index = rand() % path_x.size();

		maze_iswall_isnotwall[path_x[rand_index]][path_y[rand_index]] = 3;

		path_x.erase(path_x.begin() + rand_index);
		path_y.erase(path_y.begin() + rand_index);
		no_of_chests--;
	}

}

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

void MazeGenAlgo_Set_walls()
{
	//std::cout << initial_wallcells_count << std::endl;
	srand(time(NULL));


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
		for (int r = 0; r < noOfRows; r++)
		{
			for (int c = 0; c < noOfCols; c++)
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



void MazeGenAlgo()
{
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

/*========================================================================================*/
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


	/*
	Maze->specifications.noOfRows = noOfRows;
	Maze->specifications.noOfCols = noOfCols;
	Maze->specifications.mazeWindowHeight = ((float)Exe_WindowHeight / 6.0f) * 5;
	Maze->specifications.mazeWindowWidth = (float)Exe_WindowWidth / 2.0f;
	Maze->specifications.cellHeight = Maze->specifications.mazeWindowHeight / noOfRows ;
	Maze->specifications.cellWidth = Maze->specifications.mazeWindowWidth / noOfCols;
	Maze->specifications.MazeWindowStart_X = Exe_WindowWidth / 2.0f / -2;
	Maze->specifications.MazeWindowStart_Y = (Exe_WindowHeight / 6.0f * 5 / -2)
	*/

	// Init the grid cells
	for (int r = 0; r < Maze->specifications.noOfRows; r++)
	{
		for (int c = 0; c < Maze->specifications.noOfCols; c++)
		{

			Maze->grid[r][c].value = maze_iswall_isnotwall[r][c];
			//Maze->grid[r][c].is_PlayerPos = 0;

		}
	}

	//Maze->grid[0][7].is_PlayerPos = 1;


	return Maze;
}

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

void MAZE_CreateSolidCell2(AEGfxVertexList*& SolidCellMesh_Var, Maze_Struct* Maze, int colour_HEXA)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		0, 0, colour_HEXA, 0.0f, 1.0f,
		//0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		0, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f,
		//Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
		Maze->specifications.cellWidth, 0, colour_HEXA, 1.0f, 1.0f);
	AEGfxTriAdd(
		//0, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 1.0f,
		0, Maze->specifications.cellHeight, colour_HEXA, 0.0f, 0.0f,
		Maze->specifications.cellWidth, Maze->specifications.cellHeight, colour_HEXA, 1.0f, 0.0f,
		//Maze->specifications.cellWidth, 0, colour_HEXA, 0.0f, 0.0f);
		Maze->specifications.cellWidth, 0, colour_HEXA, 1.0f, 1.0f);
	SolidCellMesh_Var = AEGfxMeshEnd();
}


void MAZE_DrawMazeCellsandCellOutline2(AEGfxVertexList* &WALLCellMesh,
	AEGfxVertexList* &PATHCellMesh,
	AEGfxVertexList* &CellOutlineMesh,
	Maze_Struct *Maze)
{
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
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

void MAZE_SetPosAsEmpty(Maze_Struct* Maze, int curr_X_GRIDposition, int curr_Y_GRIDposition )
{
	Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value = EMPTY_PATH;
	maze_iswall_isnotwall[curr_X_GRIDposition][curr_Y_GRIDposition] = EMPTY_PATH;
}

void MAZE_DrawMazeOutline2(AEGfxVertexList*& mazeOutlineMesh, Maze_Struct* Maze)
{
	AEGfxSetPosition(Maze->specifications.MazeWindowStart_X, Maze->specifications.MazeWindowStart_Y);
	AEGfxMeshDraw(mazeOutlineMesh, AE_GFX_MDM_LINES_STRIP);
}


void MAZE_CreateMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float cell_height, float cell_width)
{
	AEGfxMeshStart();

	//pink: 0x00FF00FF
	//white: 0x00FFFFFF
	//light blue: 0x0000FFFF

	AEGfxTriAdd( //This triangle is colorful, blends 3 colours wowza
		//-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink 
		-(cell_width / 4), -(cell_height / 4), 0x00FF00FF, 0.0f, 1.0f, //pink 
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue


	AEGfxTriAdd(
		(cell_width / 4), -(cell_height / 4), 0x00FFFFFF, 1.0f, 1.0f, //white
		//(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 1.0f, //pink
		(cell_width / 4), (cell_height / 4), 0x00FF00FF, 1.0f, 0.0f, //pink
		//-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 1.0f, 1.0f); //light blue
		-(cell_width / 4), (cell_height / 4), 0x0000FFFF, 0.0f, 0.0f); //light blue

	pMesh_MainCharacter = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh_MainCharacter, "Failed to create main character!!");
}

void MAZE_DrawingMainCharacter(AEGfxVertexList*& pMesh_MainCharacter, float MC_positionX, float MC_positionY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(MC_positionX, MC_positionY);
	AEGfxTextureSet(main_character_art, 0, 0);
	AEGfxMeshDraw(pMesh_MainCharacter, AE_GFX_MDM_TRIANGLES);
}

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

void MAZE_SaveCellVisibility(Maze_Struct* maze_var)
{
	for (int r =0; r < maze_var->specifications.noOfRows; r++)
	{
		for (int c =0; c < maze_var->specifications.noOfRows; c++)
		{
			maze_visibility[r][c] = maze_var->grid[r][c].is_visible;
		}
	}
}

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

void MAZE_StepOntoSpecialCell(int curr_X_GRIDposition, int curr_Y_GRIDposition)
{
	/*
	if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == BOSS)
	{
		next = COMBAT;
		global_maze_cam_x = cam_x;
		global_maze_cam_y = cam_y;
		MAZE_SaveCellVisibility(Maze);

		AEGfxSetCamPosition(0.0f, 0.0f);
	}
	*/

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
		next = GAMEOVER;
		level_iter+= 1;
		noOfCols = level[level_iter];
		noOfRows = level[level_iter];
		maze_init_flag = 0; 
		MAZE_ResetCellVisibility(Maze);
		global_maze_cam_x = cam_x;
		global_maze_cam_y = cam_y;
		AEGfxSetCamPosition(0.0f, 0.0f);
	}

	if (Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value == CHEST)
	{
		std::cout << "player is on chest" << std::endl;
		MAZE_ChestOpened(curr_X_GRIDposition, curr_Y_GRIDposition);
	}
}


void MAZE_ChestOpened(int curr_X_GRIDposition, int curr_Y_GRIDposition)
{
	Maze->grid[curr_X_GRIDposition][curr_Y_GRIDposition].value = EMPTY_PATH;
	std::cout << "Player has opened chest" << std::endl;
	
	//int randindex;
	//srand(time(NULL));
	//randindex = ( rand() % 2 ) + 1;
	//if (randindex == 1)
	//{
	//	std::cout << "PLACEHOLDER : player +10 hp" << std::endl;
	//	playerstats->health + 10;
	//}
	//else if (randindex == 2)
	//{
	//	std::cout << "PLACEHOLDER : player +10 dmg" << std::endl;
	//	playerstats->damage += 10;
	//}
	//1 - increased hp
	//2 - increase dmg
}


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


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Maze_Load()
{
	std::cout << "Maze:Load" << std::endl;
	
	wall_art = AEGfxTextureLoad("Wall.png");
	AE_ASSERT_MESG(wall_art, "Failed to create wall texture!\n");

	path_art = AEGfxTextureLoad("Pond.png");
	AE_ASSERT_MESG(path_art, "Failed to create path texture!\n");

	main_character_art = AEGfxTextureLoad("Map duck.png");
	AE_ASSERT_MESG(main_character_art, "Failed to create path texture!\n");
}







/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Maze_Initialize()
{
	AEToogleFullScreen(systemsettings.fullscreen); // R: added

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
	
	
	MAZE_CreateMESH_MazeWindow2(pMeshMazeWindow, Maze, 0xFF0000);
	MAZE_CreateMESH_CellOutline2(pMeshCellOutline, Maze, 0xFFFFFFFF);
	MAZE_CreateSolidCell2(pMeshSolidSquare_WALL, Maze, 0x000000);
	MAZE_CreateSolidCell2(pMeshSolidSquare_PATH, Maze, 0x808080);
	MAZE_CreateMainCharacter(pMesh_MainCharacter, Maze->specifications.cellHeight, Maze->specifications.cellWidth);

	MC_positionX = Maze->specifications.MazeWindowStart_X + (Maze->specifications.cellWidth / 2) + (curr_X_GRIDposition * Maze->specifications.cellWidth);

	MC_positionY = Maze->specifications.MazeWindowStart_Y + (Maze->specifications.cellHeight / 2) + (curr_Y_GRIDposition * Maze->specifications.cellHeight);
	std::cout << "X : " << MC_positionX << " --- Y : " << MC_positionY << std::endl;

	MAZE_SetPosAsEmpty(Maze, curr_X_GRIDposition, curr_Y_GRIDposition);

	
	
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Maze_Update()
{
	//std::cout << "Maze:Update" << std::endl;

	

	AEGfxGetCamPosition(&cam_x, &cam_y);

	if (AEInputCheckTriggered(AEVK_F11)) {		// R: added
		if (systemsettings.fullscreen == 0) {	// FOR TESTING: TO BE REPLACED WITH PAUSE MENU BUTTON
			systemsettings.fullscreen = 1;
			AEToogleFullScreen(systemsettings.fullscreen);
		}

		else if (systemsettings.fullscreen == 1) {
			systemsettings.fullscreen = 0;
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}

	if (AEInputCheckTriggered(AEVK_W))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(1, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
		{
			MC_positionY += Maze->specifications.cellHeight;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";

			Maze_CameraAdjustment(1);
			//AEGfxSetCamPosition(cam_x, cam_y + Maze->specifications.cellHeight);
		}
	}

	if (AEInputCheckTriggered(AEVK_S))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(3, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
		{
			MC_positionY -= Maze->specifications.cellHeight;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";


			Maze_CameraAdjustment(3);
			//AEGfxSetCamPosition(cam_x, cam_y - Maze->specifications.cellHeight);
		}
	}


	if (AEInputCheckTriggered(AEVK_A))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(2, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
		{

			MC_positionX -= Maze->specifications.cellWidth;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";


			Maze_CameraAdjustment(2);
			//AEGfxSetCamPosition(cam_x- Maze->specifications.cellWidth, cam_y);
		}
	}

	if (AEInputCheckTriggered(AEVK_D))
	{
		if (MAZE_CharMoveCHECK_NEXT_POS(4, Maze, curr_X_GRIDposition, curr_Y_GRIDposition) == 1)
		{

			MC_positionX += Maze->specifications.cellWidth;
			std::cout << "Current mc XY position " << MC_positionX << "\t\t" << MC_positionY <<
				"\t\t" << curr_X_GRIDposition << "\t\t" << curr_Y_GRIDposition << "\n";
		
			Maze_CameraAdjustment(4);
			//AEGfxSetCamPosition(cam_x + Maze->specifications.cellWidth, cam_y);
		}
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

	MAZE_StepOntoSpecialCell(curr_X_GRIDposition,curr_Y_GRIDposition);



	AEGfxGetCamPosition(&cam_x, &cam_y);

//	std::cout << "Cam X is " << cam_x << " Cam Y is " << cam_y << std::endl;

}


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Maze_Draw()
{
	//std::cout << "Maze:Draw" << std::endl;

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
	sprintf_s(strBuffer, "Press Q to go back to the main menu");
	AEGfxPrint(fontId, strBuffer, -0.25f, -0.9f, 1.0f, 1.f, 1.f, 1.f);
}


/*
	Cleans game object instances.
*/
void Maze_Free()
{
	std::cout << "Maze:Free" << std::endl;
	AEGfxMeshFree(pMeshCellOutline);
	AEGfxMeshFree(pMeshMazeWindow);
	AEGfxMeshFree(pMeshSolidSquare_PATH);
	AEGfxMeshFree(pMeshSolidSquare_WALL);
	AEGfxMeshFree(pMesh_MainCharacter);


	delete(Maze);
}


/*
	Unload game assets. Frees and releases memory
*/
void Maze_Unload()
{
	std::cout << "Maze:Unload" << std::endl;
	AEGfxTextureUnload(wall_art);
	AEGfxTextureUnload(path_art);
	AEGfxTextureUnload(main_character_art);
}
