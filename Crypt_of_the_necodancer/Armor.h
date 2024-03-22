#pragma once
#include <string>
#include "Item.h"

class Armor :public Item 
{
public:
	short defence;
	std::string name;
	short type() override { return itemTypes::armor; };
	
};

class TestArmor :public Armor {
public:
	TestArmor(int x, int y, int i) {
		this->x = x;
		this->y = y;
		defence = 1;
		iIndex = i;
		held = false;
		name = "Test armor";
	}
	short typeOf() override { return items::testArmor; };
};
class NoArmor :public Armor {
public:
	NoArmor() {
		defence = 0;
		name = "No armor";
	}

};

