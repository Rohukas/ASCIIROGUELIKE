#include "GameSystem.h"
#include <iostream>
#include <conio.h>
using namespace std;

//constructor sets up the game
GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);



	_level.loadLevel(levelFileName, _player);
	_level.print();
	//Bad practice. real bad.
	system("PAUSE");
}


void GameSystem::playGame() {


	bool isDone = false;

	while (isDone != true) {
		_level.print();
		playerMove();
		_level.updateEnemies(_player);
	}

}
void GameSystem::playerMove() {
	char input;
	printf("Enter a move command(w/s/a/d: ");
	input = _getch();

	_level.MovePlayer(input, _player);
}