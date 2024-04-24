#include "Map.h"
//#include <iostream>
#pragma once
class Player
{
public:
	float x;
	float y;
	int gold;
	Weapon *weapon;
	Armor *armor;
	Torch* torch;
	bool facingLeft;
	int health;
	int maxhealth;
	bool gameover;
	int lastAttackDir;
	void gameOver() {
		gameover = true;
	}
	void takeDamage(int damage) {

		std::cout << "\n\nPLAYER TOOK " << max(damage - armor->defence, 1) << " DAMAGE\n\n";
		health -= max(damage - armor->defence, 1);
		if (health < 0) health = 0;
		if (health <= 0) gameOver();
	}

	Player(){}
	Player(int x, int y) {
		gameover = false;
		this->x = x;
		this->y = y;
		health = 5;
		maxhealth = 5;
		facingLeft = false;
		weapon = new NoWeapon;
		armor = new NoArmor;
		torch = new NoTorch;
		gold = 0;
		lastAttackDir = 0;
	}
};
