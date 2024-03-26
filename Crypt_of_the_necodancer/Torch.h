#pragma once
#include "Item.h"
class Torch : public Item
{
public:
    short power;
	short type() override { return itemTypes::torch; };
};
class NoTorch : public Torch
{
public:
	short typeOf() override { return items::noTorch; };
	NoTorch() {
		power = 3;
		held = true;
		name = "No torch";
	}
};
class WoodenTorch : public Torch
{
public:
	WoodenTorch() {
		power = 5;
		name = "Wooden Torch";
		price = 0;
	}
	WoodenTorch(int x, int y, int i) {
		this->x = x;
		this->y = y;
		power = 5;
		iIndex = i;
		held = false;
		name = "Wooden Torch";
		price = 0;
	}
	WoodenTorch(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		power = 5;
		iIndex = i;
		held = false;
		name = "Wooden Torch";
		price = p;
	}
	short typeOf() override { return items::woodenTorch; };
};
class SteelTorch : public Torch
{
public:
	SteelTorch() {
		power = 6;
		name = "Steel Torch";
		price = 0;
	}
	SteelTorch(int x, int y, int i) {
		this->x = x;
		this->y = y;
		power = 6;
		iIndex = i;
		held = false;
		name = "Steel Torch";
		price = 0;
	}
	SteelTorch(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		power = 6;
		iIndex = i;
		held = false;
		name = "Steel Torch";
		price = p;
	}
	short typeOf() override { return items::steelTorch; };
};
class MagicTorch : public Torch
{
public:
	MagicTorch() {
		power = 7;
		name = "Magic Torch";
		price = 0;
	}
	MagicTorch(int x, int y, int i) {
		this->x = x;
		this->y = y;
		power = 7;
		iIndex = i;
		held = false;
		name = "Magic Torch";
		price = 0;
	}
	MagicTorch(int x, int y, int i, int p) {
		this->x = x;
		this->y = y;
		power = 7;
		iIndex = i;
		held = false;
		name = "Magic Torch";
		price = p;
	}
	short typeOf() override { return items::magicTorch; };
};

