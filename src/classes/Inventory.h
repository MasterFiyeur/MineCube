//
// Created by Theo Julien on 02/03/2022.
//

#pragma once
#include "Block.h"

struct Item{
	Block* block;
	Vector2 g_position; //Graphic position in item bar
};

class Inventory {
private:
	//Inventory
	Item items[6]; //Array of item (item bar)
	Item* currentItem; //Selected item
	bool inventoryMenu = false; //Menu opened
	const unsigned short bar_size = 6; //Size of the item bar

	//Graphic informations
	const int g_screenWidth = 960;
	const int g_screenHeight = 540;
	const int g_inventoryMargin = 10; //Margin around all items in item bar
	const int g_itemSquare = 40; //Item size
	const int g_itemMargin = 10; //Margin between items
	Vector2 tempItemOldPosition; //Position (x,y) of a selected item in inventory menu
	Item* changingItemPosition; //pointer on the selected item


public:
	Inventory();
	virtual ~Inventory();

	//Getters and Setters
	Item *getCurrentItem() const;
	Item* getItem(unsigned short p_position);
	void setItem(unsigned short p_position, Block &block);
	unsigned short getBarSize() const{return bar_size;};
	const Item *getItems() const;
	bool isInventoryMenu() const;
	void setInventoryMenu(bool p_inventoryMenu);

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
