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
	Item items[6];
	Item* currentItem;
	const unsigned short bar_size = 6;

	//Graphic informations
	const int g_screenWidth = 960;
	const int g_screenHeight = 540;
	const int g_inventoryMargin = 10;
	const int g_itemSquare = 40;
	const int g_itemMargin = 10;
public:
	Inventory();
	virtual ~Inventory();

	//Getters and Setters
	Item *getCurrentItem() const;
	Item* getItem(unsigned short position);
	unsigned short getBarSize() const{return bar_size;};
	const Item *getItems() const;

	void setCurrentItem(Item *currentItem);

	//Peripheral device management (keyboard,mouse)
	void deviceManagement();

	//Drawing, graphic part
	void drawInventory();

};
