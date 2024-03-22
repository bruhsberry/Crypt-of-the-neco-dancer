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
	int health;
	int maxhealth;
	void gameOver() {}
	void takeDamage(int damage) {

		std::cout << "\n\nPLAYER TOOK " << max(damage - armor->defence, 1) << " DAMAGE\n\n";
		health -= max(damage - armor->defence, 1);
		if (health <= 0) gameOver();
	}
	Player(){}
	Player(int x, int y) {
		this->x = x;
		this->y = y;
		health = 3;
		maxhealth = 3;
		weapon = new NoWeapon;
		armor = new NoArmor;
		gold = 0;
	}
};
