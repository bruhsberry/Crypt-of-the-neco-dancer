#pragma once
#include <string>
#include "Item.h"

class Armor :public Item 
{
public:
	short type() override { return itemTypes::armor; };
	//short typeOf() override { return typeof; };
	short defence;
	//sf::Sprite loadSprite(sf::Sprite* sprite) override {
	//	sf::Sprite temp;
	//	temp.setTexture(text);
	//	temp.setPosition(x * 64, y * 64);
	//	return temp;
	//}
	Armor(int x, int y, int i, int p, int defence,  std::string texrureFile) {
		this->x = x;
		this->y = y;
		this->defence = defence;
		iIndex = i;
		held = false;
		//this->name = name;
		price = p;
		//typeof = type;
		text.loadFromFile(texrureFile);
	}
};
class ArmorFactory {
public:
	static Armor* createLetherArmor(int x, int y, int i, int p) {
		return new Armor(x, y, i, p,  1,  "Sprites\\lether.png");
	}
	static Armor* createChainArmor(int x, int y, int i, int p) {
		return new Armor(x, y, i, p, 2,  "Sprites\\chainmail.png");
	}
	static Armor* createPlateArmor(int x, int y, int i, int p) {
		return new Armor(x, y, i, p, 3, "Sprites\\plate.png");
	}
};


