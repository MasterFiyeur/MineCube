//
// Created by Arthur on 23/02/2022.
//

#include <string>
#include <iostream>
#include "raylib.h"

#include "Game.h"
#include "Block.h"
#include "WorldSave.h"

#define initial_square 8


Game::Game() {
    // Define the camera to look into our 3d world
    this->camera = { 0 };
    camera.position = (Vector3){ 0.0f, 3.0f, 0.0f }; // Camera position
    camera.target = (Vector3){ -1.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 40.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    this->world = WorldSave::load();
}

std::string Game::getCameraDirection() const {
    std::string n_s, e_w;
    if (std::abs(camera.target.x - camera.position.x) < 0.01) {
        n_s = "";
    } else if (camera.target.x > camera.position.x) {
        n_s = "N";
    } else {
        n_s = "S";
    }
    if (std::abs(camera.target.z - camera.position.z) < 0.01) {
        e_w = "";
    } else if (camera.target.z > camera.position.z) {
        e_w = "E";
    } else {
        e_w = "W";
    }
    return n_s + e_w;
}


void Game::start() {
    if (world.isempty()) {
        std::cout << "Initializing world...." << std::endl;
        // fill world with static blocks
        world.fill(Block("stone"), {-initial_square, 0, -initial_square}, {initial_square, 0, initial_square});

        Block dirt = Block("dirt");
        world.add_block(dirt, {0, 1, 0});
    }

    // setup camera and max FPS
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

    Vector3 playerPosition = camera.position;

    char upperText[200];

    while (!WindowShouldClose()) {
        // Update
        UpdateCamera(&camera);

        if (IsKeyDown(KEY_SPACE)){
            playerPosition.y += 0.1f;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)){
            playerPosition.y -= 0.1f;
        }
        camera.position.y = playerPosition.y;

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        world.draw();

        DrawGrid(15, 1.0f);

        DrawCubeWires(camera.target, 0.1f, 0.1f, 0.1f, WHITE);

        EndMode3D();

        sprintf(upperText, "Position: %.1f, %.1f, %.1f\nLooking at: %.1f, %.1f, %.1f (%s)",
                camera.position.x, camera.position.y, camera.position.z,
                camera.target.x, camera.target.y, camera.target.z, this->getCameraDirection().c_str());
        DrawText(upperText, 10, 10, 15, DARKGRAY);

        EndDrawing();
    }

    this->world.save();
}
