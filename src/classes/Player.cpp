//
// Created by Arthur Blaise on 07/03/2022.
//

#include "Player.h"


Player::Player() {
    inventory.setItem(0,*(new Block("dirt")));
    inventory.setItem(1,*(new Block("stone")));
    inventory.setItem(2,*(new Block("glass")));
    inventory.setItem(4,*(new Block("sponge")));
    inventory.setItem(5,*(new Block("soul_soil")));
}

void Player::drawInventory() {
    inventory.drawInventory();
}

void Player::handleInventoryGestures() {
    inventory.deviceManagement();
}

bool Player::hasInventoryOpen() {
    return inventory.isInventoryMenu();
}

Vector3 Player::getPosition() {
    return position;
}

void Player::setPosition(Vector3 pos) {
    this->position = pos;
}

void Player::move(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
}

Item *Player::getCurrentItem(){
    return inventory.getCurrentItem();
}
