#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include "Item.h"
#include "Armor.h"
#pragma once
using namespace std;
enum directions { right, left, up, down };
enum tile {empty, wall, hardWall};
enum enemyTypes { greenSlime, blueSlime, purpleSlime, redSlime, zombie, bat, skeleton };

class Map;

class Enemy
{
public:
	int health;
	int x;
	int y;
	short eIndex;
	virtual int update(Map* board, int plx, int ply) { return 0; };
	virtual void die(Map* board);
	virtual int typeOf() { return -1; }
	virtual int takeDamage(int damage, Map* board) { return 0; };
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
		health = 2;
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
		health = 2;
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
		health = 2;
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
		health = 2;
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
	int height;
	int length;	
	vector <vector<Cell>> m;
	vector <Enemy*> e;
	vector <Item*> it;
	Map() {}
	Map(string File);
	void saveFile() {
		
	}
};


class Weapon : public Item 
{
public:
	int damage;
	string name;
	virtual bool attack(int dir, Map* board, int x, int y) { return 0; };
	virtual string getName() { return name; };
	void dealDamage(int x, int y, Map* board) {
		int index = board->m[x][y].enemy->eIndex;
		if (board->m[x][y].enemy->takeDamage(damage, board)) {
			board->m[x][y].enemy = nullptr;
			board->e[index] = nullptr;
		}
	}
	short type() override { return itemTypes::weapon; };
};

class Testweapon : public Weapon {
public:
	short typeOf() override { return items::testSword; };
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
	Testweapon() {
		damage = 1;
		name = "Test sword";
	}
	Testweapon(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 1;
		iIndex = i;
		held = false;
		name = "Test sword";
	}
};

class IronSword : public Weapon {
public:
	short typeOf() override { return items::ironSword; };
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
	IronSword() {
		damage = 3;
		name = "Iron sword";
	}
	IronSword(int x, int y, int i) {
		this->x = x;
		this->y = y;
		damage = 3;
		iIndex = i;
		held = false;
		name = "Iron sword";
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


void Enemy::die(Map* board){
	cout << "umer\n";
	board->m[this->x][this->y].gold += 10;
	delete(this);
}

int BlueSlime::update(Map* board, int plx, int ply){
	std::cout << "updating blue slime\n";
	switch (state)
	{
	case 1:
		if (y > 0 && board->m[x][max(y - 1, 0)].tile != wall && board->m[x][max(y - 1, 0)].enemy == nullptr) {

			if (plx == x && y - 1 == ply) {
				return 1;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			state++;
		}
		break;
	case 3:
		if (y < board->height - 1 && board->m[x][min(y + 1, board->height)].tile != wall && board->m[x][min(y + 1, board->height)].enemy == nullptr) {
			if (plx == x && y + 1 == ply) {
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
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
			if (plx == x + 1 && y == ply) {
				return 1;
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
				return 1;
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

			if (plx == x - 1 && y == ply) {
				return 1;
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
				return 1;
			}
			board->m[x][y].enemy = nullptr;
			board->m[x][y - 1].enemy = this;
			y--;
			}
			state++;
			break;
		case 1:
			if (y < board->height - 1 && board->m[min(x + 1, board->height)][y].tile != wall && board->m[min(x + 1, board->height)][y].enemy == nullptr) {
				if (plx == x + 1 && y == ply) {
					return 1;
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
					return 1;
				}
				board->m[x][y].enemy = nullptr;
				board->m[x][y + 1].enemy = this;
				y++;
			}
			state++;
			break;
		case 3:
			if (y > 0 && board->m[max(x - 1, 0)][y].tile != wall && board->m[max(x - 1, 0)][y].enemy == nullptr) {

				if (plx == x - 1 && y == ply) {
					return 1;
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
					return 1;
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
				if (plx == x + 1 && y == ply) {
					return 1;
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
					return 1;
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
				if (plx == x - 1 && y == ply) {
					return 1;
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




Map::Map(string File) {

	ifstream f(File);
	if (!f.is_open()) cout << "file is not open";
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


	
	int num;
	f >> num;
	e.resize(num);
	int type, x, y;
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
		default:
			break;
		}
		e[i] = m[x][y].enemy;
	}
	f >> num;
	it.resize(num);
	for (int i = 0; i < num; i++) {
		f >> type >> x >> y;
		switch (type)
		{
		case items::testSword: 
			m[x][y].item = new Testweapon(x, y, i);
			break;
		case items::testArmor: 
			m[x][y].item = new TestArmor(x, y, i);
			break;
		case items::ironSword: 
			m[x][y].item = new IronSword(x, y, i);
			break;		
		default:
			break;
		}
		it[i] = m[x][y].item;
	}
}
