//
// Created by Arthur Blaise on 07/03/2022.
//

#pragma once
#include <map>
#include "Inventory.h"
class World;

class Player {
private:
    Inventory inventory;
    Vector3 position;
public:
    Player();
    void drawInventory();
    void handleInventoryGestures();
    bool hasInventoryOpen();

    [[nodiscard]] BoundingBox getBoundingBox() const;
    void checkCollisions(World world);
    [[nodiscard]] Vector3 getPosition() const;
    void setPosition(Vector3 pos);
    void move(float x, float y, float z);
	float isOnGround(World world);
	void gravity(World world);
};
