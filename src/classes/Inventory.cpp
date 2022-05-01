//
// Created by Theo Julien on 02/03/2022.
//

#include <iostream>
#include "Inventory.h"
#include "raylib.h"
#include "TexturesManager.h"

Inventory::Inventory() :
        tempItemOldPosition({0,0}),
        currentItem{&items[0]},
        changingItemPosition{nullptr}{
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        //Block in inventory position init
        items[i].block = nullptr;
        items[i].g_position.x = (float) ((float) (g_screenWidth-(INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin))/2 + (float) g_inventoryMargin + (float) i * (float)(g_itemSquare+g_itemMargin));
        items[i].g_position.y = (float) (g_screenHeight-(g_itemSquare+g_inventoryMargin));
    }
}

Inventory::~Inventory() {
    for (int i = 0; i < getBarSize(); ++i) {
        delete items[i].block;
    }
    currentItem = nullptr;
    changingItemPosition = nullptr;
}

Item *Inventory::getCurrentItem() const {
    return currentItem;
}

Item* Inventory::getItem(unsigned short p_position){
    if (p_position > INVENTORY_SIZE-1){
        std::cout << "The biggest position is " << getBarSize()-1 << std::endl;
        return nullptr;
    }else{
        return &items[p_position];
    }
}

void Inventory::setItem(unsigned short p_position, Block &block){
    if (p_position > INVENTORY_SIZE-1){
        std::cerr << "Error : The biggest position is " << getBarSize()-1 << std::endl;
    }else{
        if (items[p_position].block != nullptr) delete items[p_position].block;
        items[p_position].block = &block;
    }
}

const Item *Inventory::getItems() const {
    return items;
}

bool Inventory::isInventoryMenu() const {
    return inventoryMenu;
}

void Inventory::setInventoryMenu(bool p_inventoryMenu) {
    Inventory::inventoryMenu = p_inventoryMenu;
}

void Inventory::updateSelectedItem() {
    //Item selection in item bar
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

void Inventory::editSelectedItem(Block *block) {
    Item *olditem = nullptr;
    if (block != nullptr) {
        for (auto & item : items) {
            if (item.block != nullptr && item.block->getName() == block->getName()) {
                olditem = &item;
                break;
            }
        }
    }
    if (olditem != nullptr) {
        std::swap(olditem->block, currentItem->block);
    } else {
        currentItem->block = block;
    }
}

void Inventory::inventoryDisplay() {
    //Inventory menu for change item position in item bar
    setInventoryMenu(!isInventoryMenu());
    if (isInventoryMenu()){
        EnableCursor();
        std::cout << "Menu opened" << std::endl;
    }else{
        //Check if an item was selected for changing position
        if (changingItemPosition != nullptr){
            changingItemPosition->g_position = tempItemOldPosition;
            changingItemPosition = nullptr;
        }
        DisableCursor();
        std::cout << "Menu closed" << std::endl;
    }
}

void Inventory::changeItem() {
    //Changing item position in item bar
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        //Check if Click on item in the item bar
        if (getItem(i)!=changingItemPosition
            && CheckCollisionPointRec(
                {(float) GetMouseX(),(float) GetMouseY()},
                {
                        getItem(i)->g_position.x,
                        getItem(i)->g_position.y,
                        (float) g_itemSquare,
                        (float) g_itemSquare
                }
        )){
            if (changingItemPosition == nullptr){
                if (items[i].block == nullptr) return; //Don't select empty item in item bar
                changingItemPosition = &items[i];
                tempItemOldPosition = {getItem(i)->g_position.x, getItem(i)->g_position.y};
            }else{
                changingItemPosition->g_position = tempItemOldPosition;
                ::std::swap(items[i].g_position,changingItemPosition->g_position);
                ::std::swap(items[i],*changingItemPosition);
                changingItemPosition = nullptr;
            }
            break;
        }
    }
}

void Inventory::deviceManagement() {
    //Mouse management
    if (GetMouseWheelMove() != 0) {
        updateSelectedItem();
    }

    //Keyboard management
    if (IsKeyPressed(KEY_I)){
        inventoryDisplay();
    }

    //In menu mouse management
    if(isInventoryMenu() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        changeItem();
    }
}

void Inventory::updateSelectedItemPos() {
    (*changingItemPosition).g_position.x = (float) ((float) (GetMouseX())-((float) g_itemSquare)/2);
    (*changingItemPosition).g_position.y = (float) ((float) (GetMouseY())-((float) g_itemSquare)/2);
}

void Inventory::inGameInventory() {
    //Inventory background
    DrawRectangle(
            getInventoryDrawPositionX(),
            getInventoryDrawPositionY(),
            INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin,
            g_itemSquare+2*g_inventoryMargin,
            ColorAlpha(LIGHTGRAY,0.7)
    );

    // Draw current item name
    if (getCurrentItem()->block != nullptr) {
        const std::string name = getCurrentItem()->block->getName();
        const int w = name.size() * 8;
        DrawText(name.c_str(), (GetScreenWidth() - w) / 2, getInventoryDrawPositionY() - 30, 14, {213, 195, 195, 250});
    }

    // Draw hotbar with textures
    Texture2D item_texture;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        //Items border
        Item* item;
        item = getItem(i);
        if (getCurrentItem()==item) {
            //Selected Item
            DrawRectangleLinesEx(
                    (Rectangle){
                            (float) ((float) (g_screenWidth-(INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin))/2 + (float) g_inventoryMargin + (float) i * (float) (g_itemSquare+g_itemMargin)-4),
                            (float) (g_screenHeight-(g_itemSquare+g_inventoryMargin)-4),
                            (float) (g_itemSquare+8),
                            (float) (g_itemSquare+8)
                    },
                    3,
                    BLACK
            );
        }else{
            DrawRectangleLines(
                    (g_screenWidth-(INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin)-1,
                    g_screenHeight-(g_itemSquare+g_inventoryMargin)-1,
                    g_itemSquare+2,
                    g_itemSquare+2,
                    DARKGRAY
            );
        }
        //Items inventory
        if(item->block != nullptr) {
            item_texture = *TexturesManager::getTexture(item->block->getName());
            item_texture.height = g_itemSquare;
            item_texture.width = g_itemSquare;
            DrawTexture(
                    item_texture,
                    (int) item->g_position.x,
                    (int) item->g_position.y,
                    WHITE
            );
        }
    }
}

void Inventory::inMenuInventory() {
	//Inventory background
    DrawRectangle(
    getInventoryDrawPositionX(),
    getInventoryDrawPositionY()-(7*g_itemSquare+2*g_inventoryMargin),
    INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin,
    (6*g_itemSquare+2*g_inventoryMargin),
    ColorAlpha(LIGHTGRAY,0.7)
    );

    // Draw hotbar with textures
    Texture2D item_texture;
    for (int j = 3; j < 8; ++j) {
        for (int i = 0; i < INVENTORY_SIZE; ++i) {
            //Items border
            Item* item;
            item = getItem(i);
            DrawRectangleLines(
                    (g_screenWidth-(INVENTORY_SIZE*g_itemSquare+(INVENTORY_SIZE-1)*g_itemMargin+2*g_inventoryMargin))/2 + g_inventoryMargin + i * (g_itemSquare+g_itemMargin)-1,
                    g_screenHeight-j*(g_itemSquare+g_inventoryMargin)-1,
                    g_itemSquare+2,
                    g_itemSquare+2,
                    DARKGRAY
                    );
            //Items inventory
            if(item->block != nullptr) {
                item_texture = *TexturesManager::getTexture(item->block->getName());
                item_texture.height = g_itemSquare;
                item_texture.width = g_itemSquare;
                DrawTexture(
                        item_texture,
                        (int) item->g_position.x,
                        (int) item->g_position.y,
                        WHITE
                );
            }
        }
    }
}


void Inventory::drawInventory() {
	if (isInventoryMenu() && changingItemPosition != nullptr) {
		updateSelectedItemPos();
	}
	inGameInventory();
    if (isInventoryMenu()){
        inMenuInventory();
    }
}
