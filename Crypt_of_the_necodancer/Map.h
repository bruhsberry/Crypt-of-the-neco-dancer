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
	string nextLevel;
	Map(string File, int difficulty);
	Map() {}
};


class Weapon : public Item 
{
public:
	int damage;
	bool killing, killingAnswer;
	virtual bool attack(int dir, Map* board, int x, int y) =0;
	//virtual string getName() { return name; };
	void dealDamage(int x, int y, Map* board) {
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
	virtual short weaponType() { return 0; };
}; 

class Sword :public Weapon {
public:
	short weaponType() override { return 1; }
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
	Sword(int x, int y, int i, int p, int damage, std::string texrureFile) {
		this->x = x;
		this->y = y;
		this->damage = damage;
		iIndex = i;
		held = false;
		price = p;
		killing = false;
		killingAnswer = false;
		text.loadFromFile(texrureFile);
	}
};

class NoWeapon : public Weapon {
public:
	//short typeOf() { return -2; };
	short weaponType() override { return -1; }
	bool attack(int dir, Map* board, int x, int y) override {
		std::cout << "cant attack\n";
		switch (dir)
		{
		case directions::right:
			if (board->m[x + 1][y].enemy != nullptr)
				return 1;
			break;
		case directions::left:
			if (board->m[x - 1][y].enemy != nullptr) 
				return 1;
			break;
		case directions::up:
			if (board->m[x][y - 1].enemy != nullptr) 
				return 1;
			break;
		case directions::down:
			if (board->m[x][y + 1].enemy != nullptr) 
				return 1;
			break;

		default:
			break;
		}
		return 0;
	}
	NoWeapon() {
		held = true;
		damage = 0;	
		killing = false;
		killingAnswer = false;
	}
};

class Broadsword :public Weapon {
public:
	short weaponType() override { return 2; }
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
	Broadsword(int x, int y, int i, int p, int damage, std::string texrureFile) {
		this->x = x;
		this->y = y;
		this->damage = damage;
		iIndex = i;
		held = false;
		price = p;
		killing = false;
		killingAnswer = false;
		text.loadFromFile(texrureFile);
	}
};

class Spear : public Weapon {
public:
	short weaponType() override { return 3; }
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
	Spear(int x, int y, int i, int p, int damage, std::string texrureFile) {
		this->x = x;
		this->y = y;
		this->damage = damage;
		iIndex = i;
		held = false;
		price = p;
		killing = false;
		killingAnswer = false;
		text.loadFromFile(texrureFile);
	}
};

class WeaponFactory {
public:
	static Weapon* createIronSword(int x, int y, int i, int p) {
		return new Sword(x, y, i, p, 1, "Sprites\\iron sword.png");
	}
	static Weapon* createTitaniumSword(int x, int y, int i, int p) {
		return new Sword(x, y, i, p, 2, "Sprites\\titanium sword.png");
	}
	static Weapon* createGoldSword(int x, int y, int i, int p) {
		return new Sword(x, y, i, p, 3, "Sprites\\gold sword.png");
	}
	static Weapon* createIronBroadsword(int x, int y, int i, int p) {
		return new Broadsword(x, y, i, p, 1, "Sprites\\iron broadsword.png");
	}
	static Weapon* createTitaniumBroadsword(int x, int y, int i, int p) {
		return new Broadsword(x, y, i, p, 2, "Sprites\\titanium broadsword.png");
	}
	static Weapon* createGoldBroadsword(int x, int y, int i, int p) {
		return new Broadsword(x, y, i, p, 3, "Sprites\\gold broadsword.png");
	}
	static Weapon* createIronSpear(int x, int y, int i, int p) {
		return new Spear(x, y, i, p, 1, "Sprites\\iron spear.png");
	}
	static Weapon* createTitaniumSpear(int x, int y, int i, int p) {
		return new Spear(x, y, i, p, 2, "Sprites\\titanium spear.png");
	}
	static Weapon* createGoldSpear(int x, int y, int i, int p) {
		return new Spear(x, y, i, p, 3, "Sprites\\gold spear.png");
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
		if (x > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {

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
		if (x < board->length - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
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
		if (x < board->length - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
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
		if (x > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {

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
		if (x < board->length - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
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
		if (x > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {
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
			if (x < board->length - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
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
			if (x > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {
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
		itCarry = WeaponFactory::createIronSword(x, y, 0, 0);
		break;
	case items::titaniumSword:
		itCarry = WeaponFactory::createTitaniumSword(x, y, 0, 0);
		break;
	case items::goldSword:
		itCarry = WeaponFactory::createGoldSword(x, y, 0, 0);
		break;
	case items::woodenTorch:
		itCarry = TorchFactory::createWoodenTorch(x, y, 0, 0);
		break;
	case items::steelTorch:
		itCarry = TorchFactory::createSteelTorch(x, y, 0, 0);
		break;
	case items::magicTorch:
		itCarry = TorchFactory::createMagicTorch(x, y, 0, 0);
		break;
	case items::ironBroadsword:
		itCarry = WeaponFactory::createIronBroadsword(x, y, 0, 0);
		break;
	case items::titaniumBroadsword:
		itCarry = WeaponFactory::createTitaniumBroadsword(x, y, 0, 0);
		break;
	case items::goldBroadsword:
		itCarry = WeaponFactory::createGoldBroadsword(x, y, 0, 0);
		break;
	case items::ironSpear:
		itCarry = WeaponFactory::createIronSpear(x, y, 0, 0);
		break;
	case items::titaniumSpear:
		itCarry = WeaponFactory::createTitaniumSpear(x, y, 0, 0);
		break;
	case items::goldSpear:
		itCarry = WeaponFactory::createGoldSpear(x, y, 0, 0);
		break;
	case items::letherArmor:
		itCarry = ArmorFactory::createLetherArmor(x, y, 0, 0);
		break;
	case items::chainArmor:
		itCarry = ArmorFactory::createChainArmor(x, y, 0, 0);
		break;
	case items::plateArmor:
		itCarry = ArmorFactory::createPlateArmor(x, y, 0, 0);
		break;
	default:
		break;
	}
}


Map::Map(string File, int difficulty) {
	this->difficulty = difficulty;
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
			m[x][y].item = WeaponFactory::createIronSword(x, y, i, price);
			break;
		case items::titaniumSword: 
			m[x][y].item = WeaponFactory::createTitaniumSword(x, y, i, price);
			break;	
		case items::goldSword:
			m[x][y].item = WeaponFactory::createGoldSword(x, y, i, price);
			break;
		case items::woodenTorch:
			m[x][y].item = TorchFactory::createWoodenTorch(x, y, i, price);
			break;
		case items::steelTorch:
			m[x][y].item = TorchFactory::createSteelTorch(x, y, i, price);
			break;
		case items::magicTorch:
			m[x][y].item = TorchFactory::createMagicTorch(x, y, i, price);
			break;
		case items::ironBroadsword:
			m[x][y].item = WeaponFactory::createIronBroadsword(x, y, i, price);
			break;
		case items::titaniumBroadsword:
			m[x][y].item = WeaponFactory::createTitaniumBroadsword(x, y, i, price);
			break;
		case items::goldBroadsword:
			m[x][y].item = WeaponFactory::createGoldBroadsword(x, y, i, price);
			break;
		case items::ironSpear:
			m[x][y].item = WeaponFactory::createIronSpear(x, y, i, price);
			break;
		case items::titaniumSpear:
			m[x][y].item = WeaponFactory::createTitaniumSpear(x, y, i, price);
			break;
		case items::goldSpear:
			m[x][y].item = WeaponFactory::createGoldSpear(x, y, i, price);
			break;
		case items::letherArmor:
			m[x][y].item = ArmorFactory::createLetherArmor(x, y, i, price);
			break;
		case items::chainArmor:
			m[x][y].item = ArmorFactory::createChainArmor(x, y, i, price);
			break;
		case items::plateArmor:
			m[x][y].item = ArmorFactory::createPlateArmor(x, y, i, price);
			break;
		default:
			break;
		}
		it[i] = m[x][y].item;
	}
	f >> nextLevel;
}