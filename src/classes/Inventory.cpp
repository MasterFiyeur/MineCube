//
// Created by cytech on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"
#include "TexturesManager.h"

Inventory::Inventory() : items{{Block("dirt"),5},{Block("stone"),5},{Block("glass"),5},{Block("sponge"),5},{Block("dirt"),5},{Block("stone"),5}}{
	currentItem = &items[0];
}

Inventory::~Inventory() {
	currentItem = nullptr;
}

Item *Inventory::getCurrentItem() const {
	return currentItem;
}

Item* Inventory::getItem(unsigned short position){
	if(position > bar_size-1){
		std::cout << "The biggest position is " << getBarSize()-1 << std::endl;
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

void Inventory::deviceManagement() {
	//Mouse management
	if(GetMouseWheelMove()) {
		changeSelectedItem();
	}

	if(IsKeyPressed(KEY_I)){
		setInventoryMenu(isInventoryMenu()?false:true);
		if(isInventoryMenu()){
			//Freeze camera and open menu et afficher le curseur
		}else{
			//Close menu and resume camera et cacher le curseur
		}
		std::cout << "Menu opened : " << isInventoryMenu() << std::endl;
	}
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
		if(getCurrentItem()==getItem(i)) {
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
				(g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin),
				g_screenHeight-(g_itemSquare+g_inventoryMargin),
				WHITE
		);
	}
}


void Inventory::drawInventory() {
	inGameInventory();
}