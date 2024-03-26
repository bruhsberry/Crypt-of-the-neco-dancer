#pragma once
#include <string>
enum itemTypes{armor, weapon, torch};
enum items { noWeapon, noArmor, noTorch, ironSword, titaniumSword, goldSword, woodenTorch,
steelTorch, magicTorch, ironBroadsword, titaniumBroadsword, goldBroadsword, ironSpear, 
titaniumSpear, goldSpear, letherArmor, chainArmor, plateArmor
};
class Item
{
public:
	short iIndex;
	short x;
	short y;
	bool held;
	short price;
	std::string name;
	//void pickUp() {};
	virtual short type() { return 0; };
	virtual short typeOf() { return 0; };
};


