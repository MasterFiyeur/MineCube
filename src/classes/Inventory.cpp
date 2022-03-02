//
// Created by cytech on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"
#include "TexturesManager.h"

Inventory::Inventory() : items{{Block("dirt")},{Block("stone")},{Block("glass")},{Block("sponge")},{Block("dirt")},{Block("stone")}}{
	currentItem = &items[0];
}

Inventory::~Inventory() {
	setCurrentItem(nullptr);
}

Item *Inventory::getCurrentItem() const {
	return currentItem;
}

void Inventory::setCurrentItem(Item *currentItem) {
	currentItem = currentItem;
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

void Inventory::drawInventory() {
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

void Inventory::deviceManagement() {
	//Mouse management
	if(GetMouseWheelMove()) {
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
}

