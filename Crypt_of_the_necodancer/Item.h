#pragma once
enum itemTypes{armor, weapon};
enum items { noWeapon, testSword, testArmor, ironSword };
class Item
{
public:
	short iIndex;
	short x;
	short y;
	bool held;
	//void pickUp() {};
	virtual short type() { return 0; };
	virtual short typeOf() { return 0; };
	int aaaa;
};


