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
	const int g_itemSquare = (int) (g_screenWidth/24); //Item size
	const int g_itemMargin = 10; //Margin between items
	Vector2 tempItemOldPosition; //Position (x,y) of a selected item in inventory menu
	Item* changingItemPosition; //pointer on the selected item


public:
	/**
	*\brief Construct a new Inventory object
	*/
	Inventory();

	//Getters and Setters

	/**
	*\brief Get the selectionned item in the inventory bar
	*
	*\return Item* Pointer on the item selectionned
	*/
	Item *getCurrentItem() const;
	/**
	*\brief Get an item using its inventory bar position
	*
	*\param p_position Position of the item in the inventory bar
	*\return Item* Pointer on the item
	*/
	Item* getItem(unsigned short p_position);
	/**
	*\brief Add an item to the inventory bar
	*
	*\param p_position Position of the item that we want to add
	*\param block Block to add to the inventory bar
	*/
	void setItem(unsigned short p_position, Block &block);
	/**
	*\brief Get the Bar Size int
	*
	*\return unsigned short size of inventory bar
	*/
	unsigned short getBarSize() const{return bar_size;};
	/**
	*\brief Get all items from the inventory bar
	*
	*\return const Item* Array that contains all items stored in the inventory bar
	*/
	const Item *getItems() const;
	/**
	*\brief Boolean that indicates if the menu is opened
	*
	*\return true if opened
	*\return false if closed
	*/
	bool isInventoryMenu() const;
	/**
	*\brief Open of close the inventory menu
	*
	*\param p_inventoryMenu Boolean to open or close inventory
	*/
	void setInventoryMenu(bool p_inventoryMenu);

	//Peripheral device management (keyboard,mouse)

	/**
	*\brief Change the position of the selected item in the inventory bar
	*
	*/
	void changeSelectedItem();
	/**
	*\brief Display the inventory menu or close it if it was already opened
	*
	*/
	void inventoryDisplay();
	/**
	*\brief Once the inventory menu, this method is called for echange items position
	*
	*/
	void changeItem();
	/**
	*\brief Management between inventory and Keyboard/Mouse
	*
	*/
	void deviceManagement();//Global management

	//Drawing, graphic part

	/**
	*\brief Update graphics that show the selected item
	*
	*/
	void updateSelectedItemPos();
	/**
	*\brief Draw graphics of in-game inventory 
	*
	*/
	void inGameInventory();
	/**
	*\brief General method called for draw inventory
	*
	*/
	void drawInventory();

};
