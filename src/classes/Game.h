//
// Created by Arthur on 23/02/2022.
//

#pragma once

#include "World.h"
#include "Player.h"
#include "AudioManager.h"

class Game {
private:
    Camera3D camera{};
    World world;
    Player player;
    std::time_t last_save;
    AudioManager audio;
    double last_key_space_pressed;
    void drawCursor();
    [[nodiscard]] std::string getDebugText(const std::pair<const Vector3, Block*>* selected_block) const;
    [[nodiscard]] std::string getHelpText() const;

    [[nodiscard]] std::string getCameraDirection() const;
    [[nodiscard]] const std::pair<const Vector3, Block*>* getTargetedBlock() const;

    [[nodiscard]] float getSkyBrightness() const;
    [[nodiscard]] Color getSkyColor() const;
	[[nodiscard]] Color getSunColor() const;

    // Break the targeted block if needed (left click)
    void blockBreak(const std::pair<const Vector3, Block*> *target);

    // Place a new block next to the targeted block if needed (right click)
    void blockPlace(const std::pair<const Vector3, Block*> *target);

public:
    Game();

    /**
     * @brief Start the game and run everything until the user closes the game
     */
    void start();

    /**
     * @brief Save the game (world+player) into the world.json file
     */
    void save();

    /**
     * @brief Get the player object related to this game
     * @return
     */
    [[nodiscard]] Player* getPlayer();

    /**
     * @brief Get the world object the player is currently using
     * @return
     */
    [[nodiscard]] World getWorld() const;

    /**
     * @brief Get the current game daytime
     * @return The number of seconds elapsed, between 0 and DAY_LENGTH
     */
    [[nodiscard]] float getDaytime() const;

    /**
     * @brief Get the current day hour
     * @return The hour, between 0 and 23
     */
    [[nodiscard]] int getDayHour() const;

    /**
     * @brief Get the current day minute
     * @return The minute, between 0 and 59
     */
    [[nodiscard]] int getDayMinute() const;
};

