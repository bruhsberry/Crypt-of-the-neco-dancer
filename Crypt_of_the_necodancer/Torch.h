#pragma once
#include "Item.h"
class Torch : public Item
{
public:
    short power;
	short type() override { return itemTypes::torch; };
	Torch(int x, int y, int i, int p, int power,  std::string texrureFile) {
		this->x = x;
		this->y = y;
		this->power = power;
		iIndex = i;
		held = false;
		price = p;
		text.loadFromFile(texrureFile);
	}

};
class TorchFactory {
public:
	static Torch* createWoodenTorch(int x, int y, int i, int p) {
		return new Torch(x, y, i, p, 5, "Sprites\\wooden torch.png");
	}
	static Torch* createSteelTorch(int x, int y, int i, int p) {
		return new Torch(x, y, i, p, 6, "Sprites\\steel torch.png");
	}
	static Torch* createMagicTorch(int x, int y, int i, int p) {
		return new Torch(x, y, i, p, 7, "Sprites\\magic torch.png");
	}
};
