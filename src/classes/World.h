//
// Created by Arthur on 26/02/2022.
//

#pragma once

#include <map>
#include <ctime>
#include "Block.h"
#include "raylib.h"
#include "Player.h"
#include "Utils.h"

#define RENDER_DISTANCE 30


class World {
private:
    std::map<Vector3, Block*> blocks;
    double time = 0.0;

    /**
     * @brief Check if a position in the world should be drawn according to a player camera
     * @param pos The position to check
     * @param player The player to check the position from
     * @return
     */
    [[nodiscard]] bool shouldBeDrawn(Vector3 pos, Player *player) const;

public:
    World();
    ~World();

    void add_block(Block *block, Vector3 position);
    void fill(Block *block, Vector3 start, Vector3 end);
    void remove_block(Vector3 position);
    [[nodiscard]] Block *get_block(Vector3 position);
    [[nodiscard]] std::map<Vector3, Block*> get_blocks() const;
    [[nodiscard]] std::map<Vector3, Block*> get_blocks(Vector3 start, Vector3 end) const;

    /**
     * @brief Check if the world does not contain any block
     * @return true if the world is empty
     */
    [[nodiscard]] bool isempty() const;

    /**
     * @brief Draw each block of the world using raylib functions
     */
    void draw() const;

    /**
     * @brief Draw each block of the world using raylib functions while optimizing the drawing
     */
    void draw(Player *player) const;

    /**
     * @brief Return the world time since its creation
     * One day is 1440 units (so 1 unit = 1 game minute)
     */
    [[nodiscard]] int getTime() const { return time + GetTime(); };

    void setTime(int new_time) { this->time = new_time - GetTime(); };
};
