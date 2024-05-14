#pragma once
#include "Map.h"
#include "Player.h"
class Game
{
public:
	string firstLevel;
	Player player;
	Map board;
	string nextLevel;
	//int difficulty;
	Game(string file) {
		board = Map(file, 1); 
		player = Player(board.playerStartX, board.playerStartY);
		nextLevel = board.nextLevel;
		firstLevel = file;
		//difficulty = 1;
		//board.difficulty = difficulty;
		player.weapon->killing = false;
		player.weapon->killingAnswer = false;
	}
	void deleteMap() {
		for (int i = 0; i < board.e.size(); ++i) 
			delete(board.e[i]);
		for (int i = 0; i < board.it.size(); ++i) 
			delete(board.it[i]);
	}
	void Restart() {
		deleteMap();
		board = Map(firstLevel, 1);
		player = Player(board.playerStartX, board.playerStartY);
		nextLevel = board.nextLevel;
		player.weapon->killing = false;
		player.weapon->killingAnswer = false;
	}
	void NextLevel() {
		deleteMap();
		board = Map(nextLevel, board.difficulty+1);
		player.x = board.playerStartX;
		player.y = board.playerStartY;
		player.health = player.maxhealth;
		nextLevel = board.nextLevel;

		player.weapon->iIndex = board.it.size();
		board.it.push_back(player.weapon);
		player.armor->iIndex = board.it.size();
		board.it.push_back(player.armor);
		player.torch->iIndex = board.it.size();
		board.it.push_back(player.torch);
		//difficulty++;
		//board.difficulty = difficulty;
	}
};

