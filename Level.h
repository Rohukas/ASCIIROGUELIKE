#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
using namespace std;
class Level
{
public:
	Level();
	void loadLevel(string fileName, Player &player);
	void print();

	void MovePlayer(char input, Player &player);
	void updateEnemies(Player &player);


	//getters
	char getTile(int x, int y);
	//setters
	void setTile(int x, int y, char tile);
private:
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void processPlayerMove(Player &player, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);
	vector<string> _levelData;
	vector <Enemy> _enemies;
};

