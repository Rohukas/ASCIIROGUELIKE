#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>
Level::Level()
{
}


void Level::loadLevel(string fileName, Player &player) {

	//Loads the level
	ifstream file;
	file.open(fileName);

	if (file.fail()) {
		perror(fileName.c_str());
		//NOT RECCOMMENDED TO USE SYSTEM PAUSE! USE SOMETHING ELSE.
		system("PAUSE");
		exit(1);

	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);

	}
	file.close();

	//Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
				case '@'://player
					player.setPosition(j, i);
					break;
				case 'S'://Snake
					_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
					_enemies.back().setPosition(j, i);
					break;
				case 'g':
					_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
					_enemies.back().setPosition(j, i);
					break;
				case 'O':
					_enemies.push_back(Enemy("Ogre", tile, 4, 20, 40, 200, 500));
					_enemies.back().setPosition(j, i);
					break;
				case 'D':
					_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
					_enemies.back().setPosition(j, i);
					break;
				case 'B':
					_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
					_enemies.back().setPosition(j, i);
					break;
			}
		}
	}

}

void Level::print() {

	std::cout << string(100, '\n');

	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());


	}
	printf("\n");

}

void Level::MovePlayer(char input, Player &player ) {
	int playerX;
	int playerY;
	
	player.getPosition(playerX, playerY);



	switch (input) {
	case 'W': //up
	case 'w':

		processPlayerMove(player, playerX, playerY - 1);

		break;
	case 'S': //down
	case 's':

		processPlayerMove(player, playerX, playerY + 1);

		break;
	case 'A': // left
	case 'a':
		processPlayerMove(player, playerX - 1 , playerY);
		break;
	case 'D'://right
	case 'd':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("INVALID INPUT!\n");
		system("PAUSE");
	}

}

void Level::updateEnemies(Player &player) {
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;


	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
	
	switch (aiMove) {
	case 'w':

		processEnemyMove(player, i, enemyX, enemyY - 1);

		break;
	case 's':

		processEnemyMove(player, i, enemyX, enemyY + 1);

		break;
	case 'a':
		processEnemyMove(player, i, enemyX - 1, enemyY);
		break;
	case 'd':
		processEnemyMove(player, i , enemyX + 1, enemyY);
		break;

	}
	}
}



char Level::getTile(int x, int y){
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;

}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);

	}


}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	case '#':
		break;
	default:
		break;
	}




}

void Level::battleMonster(Player &player, int targetX, int targetY) {
	int enemyX;
	int enemyY;
	int attackRoll;
	int attackResult;
	int playerX;
	int playerY;
	string enemyName;

	player.getPosition(playerX, playerY);


	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();
		if (targetX == enemyX && targetY == enemyY) {
			//battle
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of: %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("Monster died!\n");
				
				//Remove the enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
				//the same way
				system("PAUSE");
				player.addExperience(attackResult);

				

				return;
			}
			//Monster turn!
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of: %d\n", enemyName.c_str(), attackRoll);

			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {
				
				setTile(playerX, playerY, 'X');
				printf("You died!\n");
				print();
				//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
				//the same way
				system("PAUSE");
				
				exit(0);
				return;
			}
			//Bad habit. Real bad! Seriously find an alternative. I think cin.ignore(); should work almost 
			//the same way
			system("PAUSE");

			return;
		}

	}


}
