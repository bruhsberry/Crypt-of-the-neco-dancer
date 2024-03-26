#include <iostream>
#include <vector>
#include <utility>

#include <fstream>
#include "Item.h"
#include "Torch.h"
#include "Armor.h"
#include "Windows.h"
#pragma once
using namespace std;
enum directions { right, left, up, down };
enum tile {empty, exitDoor, wall, hardWall};
enum enemyTypes { greenSlime, blueSlime, purpleSlime, 
	redSlime, zombie, bat, skeleton, chest };

class Map;

class Enemy
{
public:
	int health;
	bool facingLeft;
	int x;
	int y;
	short eIndex;
	virtual int update(Map* board, int plx, int ply) { return 0; };
	virtual void die(Map* board);
	virtual int typeOf() { return -1; }
	virtual int takeDamage(int damage, Map* board) { return 0; };
};

class Chest :public Enemy {
public:
	Item* itCarry;
	void die(Map* board) override;
	int typeOf() override { return enemyTypes::chest; }
	int update(Map* board, int plx, int ply) override { return 0; };
	Chest(int x, int y, int index, int itemId);
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
};

class GreenSlime : public Enemy {
public:
	int typeOf() override { return enemyTypes::greenSlime; }

	//void die(Map* board) override;
	int update(Map* board, int plx, int ply) override {
		return 0;
	};

	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	GreenSlime(int x, int y, int i) {
		health = 2;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class BlueSlime : public Enemy {
public:
	short state;
	int typeOf() override { return enemyTypes::blueSlime; }

	//void die(Map* board) override;
	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage\n";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	BlueSlime(int x, int y, int i) {
		srand(time(NULL));
		health = 2;
		state = rand() % 4;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class PurpleSlime : public Enemy {
public:
	short state;
	int typeOf() override { return enemyTypes::purpleSlime; }

	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage\n";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	PurpleSlime(int x, int y, int i) {
		srand(time(NULL));
		health = 3;
		state = rand() % 4;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class RedSlime : public Enemy {
public:
	short state;
	int typeOf() override { return enemyTypes::redSlime; }

	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage\n";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	RedSlime(int x, int y, int i) {
		srand(time(NULL));
		health = 4;
		state = rand() % 4;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class Zombie : public Enemy {
public:
	short state;
	int typeOf() override { return enemyTypes::zombie; }

	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage\n";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	Zombie(int x, int y, int i) {
		srand(time(NULL));
		health = 4;
		state = rand() % 8;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class Bat : public Enemy {
public:
	short state;
	int typeOf() override { return enemyTypes::bat; }

	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage\n";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	Bat(int x, int y, int i) {
		srand(time(NULL));
		health = 2;
		state = rand() % 2;
		eIndex = i;
		this->x = x;
		this->y = y;
	}
};

class Skeleton : public Enemy {
public:
	int typeOf() override { return enemyTypes::skeleton; }
	short state;
	//void die(Map* board) override;
	int update(Map* board, int plx, int ply) override;
	int takeDamage(int damage, Map* board) override {
		std::cout << "enemy took damage";
		health -= damage;
		if (health <= 0) {
			die(board);
			return 1;
		}
		else return 0;
	}
	Skeleton(int x, int y, int i) {
		facingLeft = false;
		health = 3;
		eIndex = i;
		state = 0;
		this->x = x;
		this->y = y;
	}
};




struct Cell {
	short  tile;
	Enemy* enemy;
	Item* item;
	short gold;
};

class Map
{
public:
	int difficulty;
	int playerStartX;
	int playerStartY;
	int height;
	int length;	
	vector <vector<Cell>> m;
	vector <Enemy*> e;
	vector <Item*> it;
	Map() {}
	string nextLevel;
	Map(string File);
	void saveFile() {
		
	}
};


class Weapon : public Item 
{
public:
	int damage;
	bool killing, killingAnswer;
	virtual bool attack(int dir, Map* board, int x, int y) { return 0; };
	virtual string getName() { return name; };
	void dealDamage(int x, int y, Map* board) {
		killing = false;
		int index = board->m[x][y].enemy->eIndex;
		killing = true;
		while (!killingAnswer) Sleep(0.1);
		if (board->m[x][y].enemy->takeDamage(damage, board)) {
			
			board->e[index] = nullptr;
			board->m[x][y].enemy = nullptr;

		}
		killing = false;
		killingAnswer = false;
	}
	short type() override { return itemTypes::weapon; };
};

class Sword :public Weapon {
public:
	bool attack(int dir, Map* board, int x, int y) override {
		std::cout << "attack initiated\n";
		switch (dir)
		{
		case directions::right:
			if (board->m[x + 1][y].enemy != nullptr) {
				dealDamage(x + 1, y, board);
				return 1;
			}
			break;

		case directions::left:
			if (board->m[x - 1][y].enemy != nullptr) {
				dealDamage(x - 1, y, board);
				return 1;
			}
			break;

		case directions::up:
			if (board->m[x][y - 1].enemy != nullptr) {
				dealDamage(x, y - 1, board);
				return 1;
			}
			break;

		case directions::down:
			if (board->m[x][y + 1].enemy != nullptr) {
				dealDamage(x, y + 1, board);
				return 1;
			}
			break;

		default:
			break;
		}
		return 0;
	}
};

class IronSword : public Sword {
public:
	short typeOf() override { return items::ironSword; };
	IronSword() {
		damage = 1;
		name = "Iron sword";
		price = 0;
	}
	IronSword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron sword";
		price = 0;
	}
	IronSword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron sword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class TitaniumSword : public Sword {
public:
	short typeOf() override { return items::titaniumSword; };
	
	TitaniumSword() {
		damage = 2;
		name = "Titanium sword";
		price = 0;
	}
	TitaniumSword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium sword";
		price = 0;
	}
	TitaniumSword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium sword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class GoldSword : public Sword {
public:
	short typeOf() override { return items::goldSword; };
	GoldSword() {
		damage = 1;
		name = "Gold sword";
		price = 0;
	}
	GoldSword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold sword";
		price = 0;
	}
	GoldSword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold sword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class NoWeapon : public Weapon {
public:
	bool attack(int dir, Map* board, int x, int y) override {
		std::cout << "cant attack\n";
		switch (dir)
		{
		case directions::right:
			if (board->m[x + 1][y].enemy != nullptr) {
				return 1;
			}
			break;

		case directions::left:
			if (board->m[x - 1][y].enemy != nullptr) {
				return 1;
			}
			break;

		case directions::up:
			if (board->m[x][y - 1].enemy != nullptr) {
				return 1;
			}
			break;

		case directions::down:
			if (board->m[x][y + 1].enemy != nullptr) {
				return 1;
			}
			break;

		default:
			break;
		}
		return 0;
	}
	NoWeapon() {
		held = true;
		damage = 0;
		name = "No weapon";
	}
	NoWeapon(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 0;
		iIndex = i;
		name = "Test sword";
	}
};

class Broadsword :public Weapon {
public:
	bool attack(int dir, Map* board, int x, int y) override {
		bool hit = false;
		std::cout << "attack initiated\n";
		switch (dir)
		{
		case directions::right:
			if (board->m[x + 1][y].enemy != nullptr) {
				dealDamage(x + 1, y, board);
				hit = true;
			}
			if (y < board->height - 1 && board->m[x + 1][y + 1].enemy != nullptr) {
				dealDamage(x + 1, y + 1, board);
				hit = true;
			}
			if (y > 0 && board->m[x + 1][y - 1].enemy != nullptr) {
				dealDamage(x + 1, y - 1, board);
				hit = true;
			}
			break;
		case directions::left:
			if (board->m[x - 1][y].enemy != nullptr) {
				dealDamage(x - 1, y, board);
				hit = true;
			}
			if (y < board->height - 1 && board->m[x - 1][y + 1].enemy != nullptr) {
				dealDamage(x - 1, y + 1, board);
				hit = true;
			}
			if (y > 0 && board->m[x - 1][y - 1].enemy != nullptr) {
				dealDamage(x - 1, y - 1, board);
				hit = true;
			}
			break;
		case directions::up:
			if (board->m[x][y - 1].enemy != nullptr) {
				dealDamage(x, y - 1, board);
				hit = true;
			}
			if (x < board->length - 1 && board->m[x + 1][y - 1].enemy != nullptr) {
				dealDamage(x + 1, y - 1, board);
				hit = true;
			}
			if (x > 0 && board->m[x - 1][y - 1].enemy != nullptr) {
				dealDamage(x - 1, y - 1, board);
				hit = true;
			}
			break;
		case directions::down:
			if (board->m[x][y + 1].enemy != nullptr) {
				dealDamage(x, y + 1, board);
				hit = true;
			}
			if (x < board->length - 1 && board->m[x + 1][y + 1].enemy != nullptr) {
				dealDamage(x + 1, y + 1, board);
				hit = true;
			}
			if (x > 0 && board->m[x - 1][y + 1].enemy != nullptr) {
				dealDamage(x - 1, y + 1, board);
				hit = true;
			}
			break;
		default:
			break;
		}
		if (hit) return 1;
		return 0;
	}
};

class IronBroadsword : public Broadsword {
public:
	short typeOf() override { return items::ironBroadsword; };
	IronBroadsword() {
		damage = 1;
		name = "Iron broadsword";
		price = 0;
	}
	IronBroadsword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron broadsword";
		price = 0;
	}
	IronBroadsword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron broadsword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class TitaniumBroadsword : public Broadsword {
public:
	short typeOf() override { return items::titaniumBroadsword; };
	TitaniumBroadsword() {
		damage = 2;
		name = "Titanium broadsword";
		price = 0;
	}
	TitaniumBroadsword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium broadsword";
		price = 0;
	}
	TitaniumBroadsword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium broadsword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class GoldBroadsword : public Broadsword {
public:
	short typeOf() override { return items::goldBroadsword; };
	GoldBroadsword() {
		damage = 3;
		name = "Gold broadsword";
		price = 0;
	}
	GoldBroadsword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold broadsword";
		price = 0;
	}
	GoldBroadsword(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold broadsword";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class Spear : public Weapon {
	bool attack(int dir, Map* board, int x, int y) override {
		bool hit = false;
		std::cout << "attack initiated\n";
		switch (dir)
		{
		case directions::right:
			if (board->m[x + 1][y].enemy != nullptr) {
				dealDamage(x + 1, y, board);
				hit = true;
			}
			if (x < board->length - 2 && board->m[x + 2][y].enemy != nullptr) {
				dealDamage(x + 2, y, board);
				hit = true;
			}
			break;
		case directions::left:
			if (board->m[x - 1][y].enemy != nullptr) {
				dealDamage(x - 1, y, board);
				hit = true;
			}
			if (x > 1 && board->m[x - 2][y].enemy != nullptr) {
				dealDamage(x - 2, y, board);
				hit = true;
			}
			break;
		case directions::up:
			if (board->m[x][y - 1].enemy != nullptr) {
				dealDamage(x, y - 1, board);
				hit = true;
			}
			if (y > 1 && board->m[x][y - 2, 0].enemy != nullptr) {
				dealDamage(x,  y - 2, board);
				hit = true;
			}
			break;
		case directions::down:
			if (board->m[x][y + 1].enemy != nullptr) {
				dealDamage(x, y + 1, board);
				hit = true;
			}
			if (y < board->height - 2 && board->m[x][y + 2].enemy != nullptr) {
				dealDamage(x, y + 2, board);
				hit = true;
			}

			break;
		default:
			break;
		}
		if (hit) return 1;
		return 0;
	}
};

class IronSpear :public Spear {
public:
	short typeOf() override { return items::ironSpear; };
	IronSpear() {
		damage = 1;
		name = "Iron spear";
		price = 0;
	}
	IronSpear(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron spear";
		price = 0;
	}
	IronSpear(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Iron spear";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class TitaniumSpear :public Spear {
public:
	short typeOf() override { return items::titaniumSpear; };
	TitaniumSpear() {
		damage = 2;
		name = "Titanium spear";
		price = 0;
	}
	TitaniumSpear(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium spear";
		price = 0;
	}
	TitaniumSpear(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 2;
		iIndex = i;
		held = false;
		name = "Titanium spear";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

class GoldSpear :public Spear {
public:
	short typeOf() override { return items::goldSpear; };
	GoldSpear() {
		damage = 3;
		name = "Gold spear";
		price = 0;
	}
	GoldSpear(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold spear";
		price = 0;
	}
	GoldSpear(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Gold spear";
		price = p;
		killing = false;
		killingAnswer = false;
	}
};

void Enemy::die(Map* board){
	cout << "umer\n";
	board->m[this->x][this->y].gold += 1;
	delete(this);
}

int BlueSlime::update(Map* board, int plx, int ply){
	std::cout << "updating blue slime\n";
	switch (state)
	{
	case 1:
		if (y > 0 && board->m[x][max(y - 1, 0)].tile != tile::wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {

			if (plx == x && y - 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			state++;
		}
		break;
	case 3:
		if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != tile::wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
			if (plx == x && y + 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y + 1].enemy = this;
			y++;
			state = 0;
		}
		break;
	default:
		state++;
		break;
	}
	return 0;
}

int PurpleSlime::update(Map* board, int plx, int ply) {
	//std::cout << "updating purple slime\n";
	switch (state)
	{
	case 1:
		if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {

			if (plx == x - 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x - 1][y].enemy = this;
			x--;
			state++;
		}
		break;
	case 3:
		if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
			if (plx == x + 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x + 1][y].enemy = this;
			x++;
			state = 0;
		}
		break;
	default:
		state++;
		break;
	}
	return 0;
}

int RedSlime::update(Map* board, int plx, int ply) {
	switch (state)
	{
	case 1:
		if (y > 0 && board->m[x][max(y - 1, 0)].tile != wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {

			if (plx == x && y - 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			state++;
		}
		break;
	case 3:
		if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
			if (plx == x + 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x + 1][y].enemy = this;
			x++;
			state++;
		}
		break;
	case 5:
		if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
			if (plx == x && y + 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y + 1].enemy = this;
			y++;
			state++;
		}
		break;
	case 7:
		if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {

			if (plx == x - 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x - 1][y].enemy = this;
			x--;
			state = 0;
		}
		break;

	default:
		state++;
		break;
	}
	return 0;
}

int Zombie::update(Map* board, int plx, int ply) {
	switch (state)
	{
	case 0:
		if (y > 0 && board->m[x][max(y - 1, 0)].tile != wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {
			if (plx == x && y - 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			state++;
		}
		else state = 5;
		break;
	case 1:
		state--;
		break;
	case 2:
		if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
			facingLeft = false;
			if (plx == x + 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x + 1][y].enemy = this;
			x++;
			state++;
		}
		else state = 7;
		break;
	case 3:
		state--;
		break;
	case 4:
		if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
			if (plx == x && y + 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y + 1].enemy = this;
			y++;
			state++;
		}
		else state = 1;
		break;
	case 5:
		state--;
		break;
	case 6:
		if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {
			facingLeft = true;
			if (plx == x - 1 && y == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x - 1][y].enemy = this;
			x--;
			state++;
		}
		else state = 3;
		break;
	case 7:
		state--;
		break;
	}
	return 0;
}

int Bat::update(Map* board, int plx, int ply) {
	switch (state)
	{
	case 0:
		switch (rand()%4)
		{
		case 0:
			if (y > 0 && board->m[x][max(y - 1, 0)].tile != wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {
			if (plx == x && y - 1 == ply) {
				return board->difficulty;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			}
			state++;
			break;
		case 1:
			if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
				facingLeft = false;
				if (plx == x + 1 && y == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x + 1][y].enemy = this;
				x++;
			}
			state++;
			break;
		case 2:
			if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
				if (plx == x && y + 1 == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x][y + 1].enemy = this;
				y++;
			}
			state++;
			break;
		case 3:
			if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {
				facingLeft = true;
				if (plx == x - 1 && y == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x - 1][y].enemy = this;
				x--;
			}
			state++;
			break;
		}
		break;
	case 1:
		state--;
		break;
	}
	return 0;
}

int Skeleton::update(Map* board, int plx, int ply) {
	switch (state)
	{
	case -1:
		break;
	case 0:
		
		if (plx <= x && ply < y) { rand() % 2 ? state = 1 : state = 7; }
		if (plx > x && ply <= y) { rand() % 2 ? state = 1 : state = 3; }
		if (plx >= x && ply > y) { rand() % 2 ? state = 5 : state = 3; }
		if (plx < x && ply >= y) { rand() % 2 ? state = 5 : state = 7; }
		break;
	case 1: // up
		if (ply < y) {
			if (y > 0 && board->m[x][max(y - 1, 0)].tile != wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {

				if (plx == x && y - 1 == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x][y - 1].enemy = this;
				y--;
				state++;
			}
			else if (plx < x) state = 7;
			else state = 3;
		}
		else if (plx < x) state = 7;
		else state = 3;
		break;
	case 2: 
		state--;
		break;
	case 3://right
		if (plx > x) {
			if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
				facingLeft = false;
				if (plx == x + 1 && y == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x + 1][y].enemy = this;
				x++;
				state++;
			}
			else if (ply > y) state = 5;
			else state = 1;
		}
		else if (ply > y) state = 5;
		else state = 1;
		break;
	case 4:
		state--;
		break;
	case 5://down
		if (ply > y) {
			if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
				if (plx == x && y + 1 == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x][y + 1].enemy = this;
				y++;
				state++;
			}
			else if (plx < x) state = 7;
			else state = 3;
		}
		else if (plx < x) state = 7;
		else state = 3;
		break;
	case 6:
		state--;
		break;
	case 7://left
		if (plx < x) {
			if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {
				facingLeft = true;
				if (plx == x - 1 && y == ply) {
					return board->difficulty;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x - 1][y].enemy = this;
				x--;
				state++;
			}
			else if (ply > y) state = 5;
			else state = 1;
		}
		else if (ply > y) state = 5;
		else state = 1;
		break;
	case 8:
		state--;
		break;
	}

	
	return 0;
}

void Chest::die(Map* board) {
	itCarry->x = x;
	itCarry->y = y;
	itCarry->held = false;
	itCarry->iIndex = board->it.size();
	board->m[x][y].item = itCarry;
	board->it.push_back(itCarry);
}
Chest::Chest(int x, int y, int index, int itemId) {
	health = 1;
	eIndex = index;
	this->x = x;
	this->y = y;
	switch (itemId)
	{
	case items::ironSword:
		itCarry = new IronSword();
		break;
	case items::titaniumSword:
		itCarry = new TitaniumSword();
		break;
	case items::goldSword:
		itCarry = new GoldSword();
		break;
	case items::woodenTorch:
		itCarry = new WoodenTorch();
		break;
	case items::steelTorch:
		itCarry = new SteelTorch();
		break;
	case items::magicTorch:
		itCarry = new MagicTorch();
		break;
	case items::ironBroadsword:
		itCarry = new IronBroadsword();
		break;
	case items::titaniumBroadsword:
		itCarry = new TitaniumBroadsword();
		break;
	case items::goldBroadsword:
		itCarry = new GoldBroadsword();
		break;
	case items::ironSpear:
		itCarry = new IronSpear();
		break;
	case items::titaniumSpear:
		itCarry = new TitaniumSpear();
		break;
	case items::goldSpear:
		itCarry = new GoldSpear();
		break;
	case items::letherArmor:
		itCarry = new LetherArmor();
		break;
	case items::chainArmor:
		itCarry = new ChainArmor();
		break;
	case items::plateArmor:
		itCarry = new PlateArmor();
		break;
	default:
		break;
	}
}


Map::Map(string File) {
	difficulty = 0;
	ifstream f(File);
	if (!f.is_open()) cout << "file is not open";
	f >> playerStartX >> playerStartY;
	f >> length >> height;
	m.resize(length);
	for (int i = 0; i < length; i++)
	{
		m[i].resize(height);
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; ++j) {
			f >> m[j][i].tile;
		}
	}
	int num, type, x, y, price;
	f >> num;
	e.resize(num);
	for (int i = 0; i < num; i++)
	{
		f >> type >> x >> y;
		switch (type)
		{
		case enemyTypes::greenSlime: 
			m[x][y].enemy = new GreenSlime(x, y, i);
			break;		
		case enemyTypes::blueSlime: 
			m[x][y].enemy = new BlueSlime(x, y, i);
			break;
		case enemyTypes::purpleSlime: 
			m[x][y].enemy = new PurpleSlime(x, y, i);
			break;
		case enemyTypes::redSlime:
			m[x][y].enemy = new RedSlime(x, y, i);
			break;
		case enemyTypes::zombie:
			m[x][y].enemy = new Zombie(x, y, i);
			break;
		case enemyTypes::bat:
			m[x][y].enemy = new Bat(x, y, i);
			break;
		case enemyTypes::skeleton:
			m[x][y].enemy = new Skeleton(x, y, i);
			break;
		case enemyTypes::chest:
			short item;
			f >> item;
			m[x][y].enemy = new Chest(x, y, i, item);
			break;
		default:
			break;
		}
		e[i] = m[x][y].enemy;
	}
	f >> num;
	it.resize(num);
	for (int i = 0; i < num; i++) {
		f >> type >> x >> y >> price;
		switch (type)
		{
		case items::ironSword: 
			m[x][y].item = new IronSword(x, y, i, price);
			break;
		case items::titaniumSword: 
			m[x][y].item = new TitaniumSword(x, y, i, price);
			break;	
		case items::goldSword:
			m[x][y].item = new GoldSword(x, y, i, price);
			break;
		case items::woodenTorch:
			m[x][y].item = new WoodenTorch(x, y, i, price);
			break;
		case items::steelTorch:
			m[x][y].item = new SteelTorch(x, y, i, price);
			break;
		case items::magicTorch:
			m[x][y].item = new MagicTorch(x, y, i, price);
			break;
		case items::ironBroadsword:
			m[x][y].item = new IronBroadsword(x, y, i, price);
			break;
		case items::titaniumBroadsword:
			m[x][y].item = new TitaniumBroadsword(x, y, i, price);
			break;
		case items::goldBroadsword:
			m[x][y].item = new GoldBroadsword(x, y, i, price);
			break;
		case items::ironSpear:
			m[x][y].item = new IronSpear(x, y, i, price);
			break;
		case items::titaniumSpear:
			m[x][y].item = new TitaniumSpear(x, y, i, price);
			break;
		case items::goldSpear:
			m[x][y].item = new GoldSpear(x, y, i, price);
			break;
		case items::letherArmor:
			m[x][y].item = new LetherArmor(x, y, i, price);
			break;
		case items::chainArmor:
			m[x][y].item = new ChainArmor(x, y, i, price);
			break;
		case items::plateArmor:
			m[x][y].item = new PlateArmor(x, y, i, price);
			break;
		default:
			break;
		}
		it[i] = m[x][y].item;
	}
	f >> nextLevel;
}
