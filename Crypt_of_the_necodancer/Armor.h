#pragma once
#include <string>
#include "Item.h"

class Armor :public Item 
{
public:
	short defence;
	//std::string name;
	short type() override { return itemTypes::armor; };
	
};

class LetherArmor :public Armor {
public:
	LetherArmor() {
		defence = 1;
		name = "Lether armor";
		price = 0;
	}
	LetherArmor(int x, int y, int i) {
		this->x = x;
		this->y = y;
		defence = 1;
		iIndex = i;
		held = false;
		name = "Lether armor";
		price = 0;
	}
	LetherArmor(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		defence = 1;
		iIndex = i;
		held = false;
		name = "Lether armor";
		price = p;
	}
	short typeOf() override { return items::letherArmor; };
};
class ChainArmor :public Armor {
public:
	ChainArmor() {
		defence = 2;
		name = "Chain-mail armor";
		price = 0;
	}
	ChainArmor(int x, int y, int i) {
		this->x = x;
		this->y = y;
		defence = 2;
		iIndex = i;
		held = false;
		name = "Chain-mail armor";
		price = 0;
	}	
	ChainArmor(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		defence = 2;
		iIndex = i;
		held = false;
		name = "Chain-mail armor";
		price = p;
	}

	short typeOf() override { return items::chainArmor; };
};
class PlateArmor :public Armor {
public:
	PlateArmor() {
		defence = 3;
		name = "Plate armor";
		price = 0;
	}
	PlateArmor(int x, int y, int i) {
		this->x = x;
		this->y = y;
		defence = 3;
		iIndex = i;
		held = false;
		name = "Plate armor";
		price = 0;
	}
	PlateArmor(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		defence = 3;
		iIndex = i;
		held = false;
		name = "Plate armor";
		price = p;
	}
	short typeOf() override { return items::plateArmor; };
};
class NoArmor :public Armor {
public:
	short typeOf() override { return items::noArmor; };
	NoArmor() {
		held = true;
		defence = 0;
		name = "No armor";
	}

};

