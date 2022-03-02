//
// Created by cytech on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"

Inventory::Inventory() : Items{{Block("dirt")},{Block("dirt")},{Block("dirt")},{Block("dirt")},{Block("dirt")},{Block("dirt")}}{
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
	if(position > getBarSize()-1){
		std::cout << "The biggest position is " << getBarSize()-1 << std::endl;
	}else{
		return &Items[position];
	}
}

const unsigned short Inventory::getBarSize() const {
	return bar_size;
}

void Inventory::drawInventory() {
	DrawRectangle((screenWidth/2), 50, 50, 50, ColorAlpha(LIGHTGRAY,0.7));
}
