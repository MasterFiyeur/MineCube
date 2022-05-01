//
// Created by Theo Julien on 02/03/2022.
//

#pragma once
#include "Block.h"
#include "raylib.h"
#include "iostream"

#define INVENTORY_SIZE 8

struct Item{
	Block* block;
	Vector2 g_position; //Graphic position in item bar
};

class Inventory {
private:
	//Inventory
	Item items[INVENTORY_SIZE]; //Array of item (item bar)
	Item* currentItem; //Selected item
	bool inventoryMenu = false; //Menu opened

	//Graphic information
	const int g_screenWidth = GetScreenWidth();
	const int g_screenHeight = GetScreenHeight();
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
	/**
	 *\brief Destroy the Inventory object
	 */
	virtual ~Inventory();

	//Getters and Setters

	/**
	*\brief Get the selectionned item in the inventory bar
	*
	*\return Item* Pointer on the item selectionned
	*/
	[[nodiscard]] Item *getCurrentItem() const;
	/**
	*\brief Get an item using its inventory bar position
	*
	*\param p_position Position of the item in the inventory bar
	*\return Item* Pointer on the item
	*/
	[[nodiscard]] Item *getItem(unsigned short p_position);
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
	[[nodiscard]] unsigned short getBarSize() const {return INVENTORY_SIZE;};
	/**
	*\brief Get all items from the inventory bar
	*
	*\return const Item* Array that contains all items stored in the inventory bar
	*/
	[[nodiscard]] const Item *getItems() const;
	/**
	*\brief Boolean that indicates if the menu is opened
	*
	*\return true if opened
	*\return false if closed
	*/
	[[nodiscard]] bool isInventoryMenu() const;
	/**
	*\brief Open of close the inventory menu
	*
	*\param p_inventoryMenu Boolean to open or close inventory
	*/
	void setInventoryMenu(bool p_inventoryMenu);

	//Peripheral device management (keyboard,mouse)

	/**
	*\brief Change the position of the selected item in the inventory bar according to the mouse wheel move
	*
	*/
	void updateSelectedItem();

    /**
     * \brief Change the type of the block in the current slot
     * \param block The new block type
     */
    void editSelectedItem(Block* block);
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
	void deviceManagement();

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
	*\brief Draw graphics of in-menu inventory
	*
	*/
    void inMenuInventory();
	/**
	*\brief General method called for draw inventory
	*
	*/
	void drawInventory();

    [[nodiscard]] int getInventoryDrawPositionX() const {
        return (GetScreenWidth()-(INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin))/2;
    }

    [[nodiscard]] int getInventoryDrawPositionY() const {
        return GetScreenHeight()-(g_itemSquare+2*g_inventoryMargin);
    }

};
