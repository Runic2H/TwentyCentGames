#pragma once


	extern AEGfxVertexList* EnemyGridIdle;
	extern AEGfxVertexList* EnemyGridAttack;
	extern AEGfxVertexList* EnemyMesh;

	enum EnemyPos { IDLE, ATTACK };

	struct E_StatSheet
	{
		int health;
		int damage;
		int EnemyState;
		float EnemyCD;
		float positionX;
		float positionY;
		bool is_attacking;
		float AttackCD;
	};

	extern AEGfxVertexList* Player1Grid;
	extern AEGfxVertexList* Player2Grid;
	extern AEGfxVertexList* Player3Grid;
	extern AEGfxVertexList* Player4Grid;
	extern AEGfxVertexList* Player5Grid;
	extern AEGfxVertexList* PlayerMesh;


	struct c_statsheet
	{
		float positionX;
		float positionY;
		int positionID;
		int SAFEGRID;
		int health;
		int damage;
		int playerCD;
		bool is_attacking;
		bool is_dmgtaken;
	};


	c_statsheet* c_initialize();

	void CombatMesh(int RGBcounter);

	void RenderPlayerGrid(AEGfxVertexList* PlayerMesh);

	void FreePlayerMesh();

	int PlayerMovement(int& x, c_statsheet* player);

	void playerrender(c_statsheet* player, AEGfxVertexList* playermesh);


	//void PlayerAttack(c_statsheet* Player, Enemy::E_StatSheet* Enemy);

	void RGBloop(int& RGBcounter);

	void GridCheck(int& counter, int& x, c_statsheet* Player, E_StatSheet* Enemy);

	//void CameraShake(float camX, float camY);
	//int Playerdamage(c_statsheet* player, int SAFEGRID);


	//struct e_statsheet {
	//	int health;
	//	int damage;
	//	bool is_attacking;
	//};




	E_StatSheet* EnemyInitialize();

	void EnemyCombatMesh();

	void RenderEnemyGrid(AEGfxVertexList* EnemyMesh);

	void FreeEnemyMesh();

	void UpdateEnemyState(E_StatSheet* Enemy, c_statsheet* Player);

	void RenderEnemy(AEGfxVertexList* EnemyMesh, E_StatSheet* Enemy);