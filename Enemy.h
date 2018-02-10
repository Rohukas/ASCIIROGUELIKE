#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;
class Enemy
{
public:

	Enemy(string name, char tile, int level, int attack, int defense , int health, int xp);
	
	int attack();
	//setters
	void setPosition(int x, int y);
	//Getters
	void getPosition(int &x, int &y);
	string getName() { return _name; }
	int takeDamage(int attack);
	char getTile() { return _tile; }
	//Gets AI move command
	char getMove(int playerX, int playerY);
private:
	string _name;
	char _tile;


	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;
	//Position
	int _x;
	int _y;
};

