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
	int difficulty;
	Game(string file) {
		board = Map(file); 
		player = Player(board.playerStartX, board.playerStartY);
		nextLevel = board.nextLevel;
		firstLevel = file;
		difficulty = 0;
		player.weapon->killing = false;
		player.weapon->killingAnswer = false;
	}
	void Restart() {
		board = Map(firstLevel);
		player = Player(board.playerStartX, board.playerStartY);
		nextLevel = board.nextLevel;
	}
	void NextLevel() {
		board = Map(nextLevel);
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
		difficulty++;
		board.difficulty = difficulty;

	}
};

