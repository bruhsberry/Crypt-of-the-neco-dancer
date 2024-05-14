#pragma once
#include <string>
#include <SFML/Graphics.hpp>
enum itemTypes{armor, weapon, torch};
enum items { noWeapon, noArmor, noTorch, ironSword, titaniumSword, goldSword, woodenTorch,
steelTorch, magicTorch, ironBroadsword, titaniumBroadsword, goldBroadsword, ironSpear, 
titaniumSpear, goldSpear, letherArmor, chainArmor, plateArmor
};
class Item
{
public:
	sf::Texture text;
	short iIndex;
	short x;
	short y;
	short price;
	bool held;
	virtual short type() = 0;
	sf::Sprite loadSprite() {
		sf::Sprite temp;
		temp.setTexture(text);
		temp.setPosition(x * 64, y * 64);
		return temp;
	}
	sf::Sprite loadIcon() {
		sf::Sprite temp;
		temp.setOrigin(32, 32);
		temp.setScale(0.5, 0.5);
		temp.setTexture(text);
		return temp;
	}
};


