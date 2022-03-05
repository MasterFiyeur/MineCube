//
// Created by cytech on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"
#include "TexturesManager.h"

Inventory::Inventory() : items{{Block("dirt"),5},{Block("stone"),5},{Block("glass"),5},{Block("sponge"),5},{Block("dirt"),5},{Block("stone"),5}}{
	currentItem = &items[0];
	changingItemPosition = nullptr;
	for (int i = 0; i < bar_size; ++i) {
		items[i].g_position.x = (g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin);
		items[i].g_position.y = g_screenHeight-(g_itemSquare+g_inventoryMargin);
	}
}

Inventory::~Inventory() {
	currentItem = nullptr;
}

Item *Inventory::getCurrentItem() const {
	return currentItem;
}

Item* Inventory::getItem(unsigned short position){
	if (position > bar_size-1){
		std::cout << "The biggest position is " << getBarSize()-1 << std::endl;
		return nullptr;
	}else{
		return &items[position];
	}
}

const Item *Inventory::getItems() const {
	return items;
}

bool Inventory::isInventoryMenu() const {
	return inventoryMenu;
}

void Inventory::setInventoryMenu(bool inventoryMenu) {
	Inventory::inventoryMenu = inventoryMenu;
}

void Inventory::changeSelectedItem() {
	if (GetMouseWheelMove() < 0) {
		if (getItem(getBarSize() - 1) == getCurrentItem()) {
			currentItem = &items[0];
		} else {
			*currentItem++;
		}
	} else {
		if (getItem(0) == getCurrentItem()) {
			currentItem = &items[getBarSize() - 1];
		} else {
			*currentItem--;
		}
	}
}

void Inventory::inventoryDisplay() {
	setInventoryMenu(isInventoryMenu()?false:true);
	if (isInventoryMenu()){
		EnableCursor();
		std::cout << "Menu opened" << std::endl;
	}else{
		//Check if an item was selected for changing position
		if(changingItemPosition != nullptr){
			changingItemPosition->g_position = tempItemOldPostition;
			changingItemPosition = nullptr;
		}
		DisableCursor();
		std::cout << "Menu closed" << std::endl;
		//Close menu and resume camera et cacher le curseur
	}
}

void Inventory::changeItem() {

}

void Inventory::deviceManagement() {
	//Mouse management
	if (GetMouseWheelMove()) {
		changeSelectedItem();
	}

	if (IsKeyPressed(KEY_I)){
		inventoryDisplay();
	}

	if(isInventoryMenu() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && changingItemPosition == nullptr){
		for (int i = 0; i < bar_size; ++i) {
			//Check if Click on item in the item bar
			if(CheckCollisionPointRec(
				{(float) GetMouseX(),(float) GetMouseY()},
				{
					getItem(i)->g_position.x,
					getItem(i)->g_position.y,
					(float) g_itemSquare,
					(float) g_itemSquare
				}
				)
			){
				changingItemPosition = &items[i];
				tempItemOldPostition = {getItem(i)->g_position.x, getItem(i)->g_position.y};
				std::cout << "Element " << i << " pressed !" << std::endl;
			}
		}
	}
}


void Inventory::updateSelectedItemPos() {
	(*changingItemPosition).g_position.x = GetMouseX()-g_itemSquare/2;
	(*changingItemPosition).g_position.y = GetMouseY()-g_itemSquare/2;
}

void Inventory::inGameInventory() {
	//Inventory background
	DrawRectangle(
			(g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2,
			g_screenHeight-(g_itemSquare+2*g_inventoryMargin),
			bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin,
			g_itemSquare+2*g_inventoryMargin,
			ColorAlpha(LIGHTGRAY,0.7)
	);

	Texture2D item_texture;
	for (int i = 0; i < bar_size; ++i) {
		//Items border
		if (getCurrentItem()==getItem(i)) {
			//Selected Item
			DrawRectangleLinesEx(
					(Rectangle){
							(float) ((g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin)-4),
							(float) (g_screenHeight-(g_itemSquare+g_inventoryMargin)-4),
							(float) (g_itemSquare+8),
							(float) (g_itemSquare+8)
					},
					3,
					BLACK
			);
		}else{
			DrawRectangleLines(
					(g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin)-1,
					g_screenHeight-(g_itemSquare+g_inventoryMargin)-1,
					g_itemSquare+2,
					g_itemSquare+2,
					DARKGRAY
			);
		}
		//Items inventory
		item_texture = TexturesManager::getTexture(getItem(i)->block.getName());
		item_texture.height = g_itemSquare;
		item_texture.width = g_itemSquare;
		DrawTexture(
				item_texture,
				getItem(i)->g_position.x,
				getItem(i)->g_position.y,
				WHITE
		);
	}
}


void Inventory::drawInventory() {
	if (isInventoryMenu() && changingItemPosition != nullptr) {
		updateSelectedItemPos();
	}
		inGameInventory();
}
