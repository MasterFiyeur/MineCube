//
// Created by Arthur Blaise on 07/03/2022.
//

#pragma once
#include <map>
#include "Inventory.h"
class World;

class Player {
private:
    Inventory inventory; // Inventory of the player
    Vector3 position; // Position of the player
    Vector3 orientation; // Orientation of the player (where he's looking at)
    int jump_credit = 0; // Jump credit for gain Y position
    bool apply_gravity = true; // If player should jump or fly

	const int added_jump_credit = 13; //Number of frame that the player.y will up
	const float jump_force = 0.1f; //Y-axis number the player will gain for each jump credit
	const float gravity_force = -0.1f; //Y-axis number the player will lose for each frame
public:
    /**
    *\brief Construct a new Player object
    *
    */
    Player();
    /**
    *\brief Draw inventory on the screen
    *
    */
    void drawInventory();
    /**
    *\brief Management of the inventory with keyoard and mouse
    *
    */
    void handleInventoryGestures();
    /**
    *\brief Check if the inventory is open
    *
    *\return true if opened
    *\return false if closed
    */
    bool hasInventoryOpen();

    /**
    *\brief Get the Bounding Box of this player
    *
    *\return BoundingBox of the player
    */
    [[nodiscard]] BoundingBox getBoundingBox() const;
    /**
    *\brief Management of collision between player and world
    *
    *\param world World where are the player
    */
    void checkCollisions(World *world);
    /**
    *\brief Get the player position
    *
    *\return Vector3 Position of the player
    */
    [[nodiscard]] Vector3 getPosition() const;
    /**
    *\brief Define a new position for the player
    *
    *\param pos New player position
    */
    void setPosition(Vector3 pos);
    /**
    *\brief Move the player position from its initial position
    *
    *\param x X-axis move
    *\param y Y-axis move
    *\param z Z-axis move
    */
    void move(float x, float y, float z);

    /**
    *\brief Get the player orientation (where the player is looking at)
    *
    *\return Vector3 Orientation of the player
    */
    [[nodiscard]] Vector3 getOrientation() const;
    /**
    *\brief Define a new orientation for the player
    *
    *\param pos New player orientation
    */
    void setOrientation(Vector3 target);

    /**
    *\brief Get distance betweek player's foot and floor
    * Result is between 0 and 1 (if there is no block, it will be 1)
    *
    *\param world World where are the player
    *\return float [0;1] Distance with the floor
    */
	[[nodiscard]] float distance_ground_block(World *world) const;
  
    void applyGravity(bool apply);
  
    [[nodiscard]] bool shouldApplyGravity() const;
  
    /**
    *\brief Management of the player gravity and jump credit to move the player on Y-axis
    *
    *\param world World where are the player
    */
	void gravity(World *world);
    /**
    *\brief Make the player jump (by adding jump credit)
    *
    *\param world World where are the player
    */
	void jump(World *world);

    Item *getCurrentItem();
};
