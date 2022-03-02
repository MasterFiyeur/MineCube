//
// Created by cytech on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"
#include "TexturesManager.h"

Inventory::Inventory() : Items{{Block("dirt")},{Block("stone")},{Block("glass")},{Block("sponge")},{Block("dirt")},{Block("stone")}}{
	current_Item = &Items[0];
}

Inventory::~Inventory() {
	setCurrentItem(nullptr);
}

Item *Inventory::getCurrentItem() const {
	return current_Item;
}

void Inventory::setCurrentItem(Item *currentItem) {
	current_Item = currentItem;
}

Item* Inventory::getItem(unsigned short position){
	if(position > bar_size-1){
		std::cout << "The biggest position is " << getBarSize()-1 << std::endl;
	}else{
		return &Items[position];
	}
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
	/*for (int i = 0; i < MAX_FRAME_SPEED; i++)
	{
		if (i < framesSpeed) DrawRectangle(250 + 21*i, 205, 20, 20, RED);
		DrawRectangleLines(250 + 21*i, 205, 20, 20, MAROON);
	}*/

	Texture2D item_texture;
	for (int i = 0; i < bar_size; ++i) {
		//Items border
		DrawRectangleLines(
			(g_screenWidth-(bar_size*g_itemSquare+(bar_size-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin)-1,
			g_screenHeight-(g_itemSquare+g_inventoryMargin)-1,
			g_itemSquare+2,
			g_itemSquare+2,
			DARKGRAY
		);

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
