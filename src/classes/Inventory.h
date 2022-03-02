//
// Created by Theo Julien on 02/03/2022.
//

#pragma once
#include "Block.h"

struct Item{
	Block block;
	int number;
};

class Inventory {
private:
	//Inventory
	Item Items[6];
	Item* current_Item;
	const unsigned short bar_size = 6;

	//Graphic informations
	const int g_screenWidth = 960;
	const int g_screenHeight = 540;
	const int g_inventoryMargin = 10;
	const int g_itemSquare = 50;
	const int g_itemMargin = 10;
public:
	Inventory();
	virtual ~Inventory();

	const unsigned short getBarSize() const;
	Item *getCurrentItem() const;
	Item* getItem(unsigned short position);

	void setCurrentItem(Item *currentItem);

	void drawInventory();

};
