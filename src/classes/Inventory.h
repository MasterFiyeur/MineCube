//
// Created by Theo Julien on 02/03/2022.
//

#pragma once
#include "Block.h"

struct Item{
	Block block;
	int number;
	Vector2 g_position;
};

class Inventory {
private:
	//Inventory
	Item items[6];
	Item* currentItem;
	bool inventoryMenu = false;
	const unsigned short bar_size = 6;

	//Graphic informations
	const int g_screenWidth = 960;
	const int g_screenHeight = 540;
	const int g_inventoryMargin = 10;
	const int g_itemSquare = 40;
	const int g_itemMargin = 10;
	Vector2 tempItemOldPostition;
	Item* changingItemPosition;


public:
	Inventory();
	virtual ~Inventory();

	//Getters and Setters
	Item *getCurrentItem() const;
	Item* getItem(unsigned short position);
	unsigned short getBarSize() const{return bar_size;};
	const Item *getItems() const;
	bool isInventoryMenu() const;
	void setInventoryMenu(bool inventoryMenu);

	//Peripheral device management (keyboard,mouse)
	void changeSelectedItem();
	void inventoryDisplay();
	void changeItem();
	void deviceManagement();//Global management

	//Drawing, graphic part
	void updateSelectedItemPos();
	void inGameInventory();
	void drawInventory();//Global drawing

};
