//
// Created by Arthur on 23/02/2022.
//

#include <string>
#include <iostream>
#include "raylib.h"

#include "Game.h"
#include "Block.h"
#include "WorldSave.h"

#define initial_square 16


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

void Game::drawCursor() {
    const int size = 15;
    DrawLine(GetScreenWidth()/2-size, GetScreenHeight()/2, GetScreenWidth()/2+size, GetScreenHeight()/2, WHITE);
    DrawLine(GetScreenWidth()/2, GetScreenHeight()/2-size, GetScreenWidth()/2, GetScreenHeight()/2+size, WHITE);
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

const std::pair<const Vector3, Block>* Game::getTargetedBlock() const {
    const std::pair<const Vector3, Block>* selected_block = nullptr;
    float selection_distance = 15.0f;

    Ray mouseRay = {
            camera.position,
            (Vector3){camera.target.x - camera.position.x, camera.target.y - camera.position.y, camera.target.z - camera.position.z}
    };
    for (const auto& block : world.get_blocks())
    {
        Vector3 p1 = {block.first.x - 0.5f, block.first.y - 0.5f, block.first.z - 0.5f};
        Vector3 p2 = {block.first.x + 0.5f, block.first.y + 0.5f, block.first.z + 0.5f};
        BoundingBox object_bounding_box = {p1, p2};
        RayCollision collision = GetRayCollisionBox(mouseRay, object_bounding_box);
        if (collision.hit && collision.distance < selection_distance)
        {
            selected_block = &block;
            selection_distance = collision.distance;
        }
    }

    return selected_block;
}

void Game::drawDebugText(const std::pair<const Vector3, Block>* selected_block) const {
    char upperText[200];
    sprintf(upperText, "FPS: %d\nPosition: %.1f, %.1f, %.1f\nLooking at: %.1f, %.1f, %.1f (%s)",
            GetFPS(),
            camera.position.x, camera.position.y, camera.position.z,
            camera.target.x, camera.target.y, camera.target.z, this->getCameraDirection().c_str()
            );
    if (selected_block != nullptr) {
        sprintf(upperText, "%s\nTargeted block: %.1f %.1f %.1f (%s)",upperText,
                selected_block->first.x,  selected_block->first.y,  selected_block->first.z, selected_block->second.getName().c_str());
    }
    DrawText(upperText, 10, 10, 15, DARKGRAY);
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

    player.setPosition(camera.position);

    const std::pair<const Vector3, Block>* selected_block;

    while (!WindowShouldClose()) {
        // Update
        if (!player.hasInventoryOpen()) {
            UpdateCamera(&camera);
        }

        if (IsKeyDown(KEY_SPACE)){
            player.move(0, 0.1f, 0);
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)){
            player.move(0, -0.1f, 0);
        }

        //Inventory keyboard and mouse management
        player.handleInventoryGestures();

        camera.position.y = player.getPosition().y;

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        world.draw();

        DrawGrid(15, 1.0f);

        // check for block highlighting
        selected_block = getTargetedBlock();
        if (selected_block != nullptr) {
            DrawCubeWires(selected_block->first, 1.0f, 1.0f, 1.0f, WHITE);
        }

        EndMode3D();

		    //Inventory bar
		    player.drawInventory();

        drawDebugText(selected_block);
        drawCursor();

        EndDrawing();
    }

    //this->world.save();
}
