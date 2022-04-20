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
	int jump_credit = 0;

	const int added_jump_credit = 13;
	const float jump_force = 0.1f;
	const float gravity_force = -0.07f;
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
	float distance_ground_block(World world);
	void gravity(World world);
	void jump(World world);
};
