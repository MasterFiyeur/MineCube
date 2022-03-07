//
// Created by Arthur Blaise on 07/03/2022.
//

#pragma once
#include "Inventory.h"

class Player {
private:
    Inventory inventory;
    Vector3 position;
public:
    Player();
    void drawInventory();
    void handleInventoryGestures();
    bool hasInventoryOpen();

    Vector3 getPosition();
    void setPosition(Vector3 pos);
    void move(float x, float y, float z);
};
