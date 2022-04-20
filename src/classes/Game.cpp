//
// Created by Arthur on 23/02/2022.
//

#include <string>
#include <iostream>
#include "raylib.h"

#include "Game.h"
#include "Block.h"
#include "WorldSave.h"
#include "Player.h"
#include "Utils.h"

#define initial_square 8


Game::Game() {
    // Define the camera to look into our 3d world
    this->camera = { 0 };
    camera.target = (Vector3){ -1.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 40.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    auto save = WorldSave::load();
    this->world = save.first;
    this->player.setPosition(save.second);
    this->last_save = std::time(nullptr);
}

void Game::save() {
    std::cout << "Saving world..." << std::endl;
    WorldSave::save(this);
    this->last_save = std::time(nullptr);
    std::cout << "World saved!" << std::endl;
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
    float selection_distance = 7.0f;

    Ray mouseRay = {
            camera.position,
            normalize({camera.target.x - camera.position.x, camera.target.y - camera.position.y, camera.target.z - camera.position.z})
    };
    for (const auto& block : world.get_blocks({camera.position.x - selection_distance, camera.position.y - selection_distance, camera.position.z - selection_distance},
                                              {camera.position.x + selection_distance, camera.position.y + selection_distance, camera.position.z + selection_distance})) {
        RayCollision collision = GetRayCollisionBox(mouseRay, block.second.getBoundingBox(block.first));
        if (collision.hit && collision.distance < selection_distance) {
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
            player.getPosition().x, player.getPosition().y, player.getPosition().z,
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
        // init player position above the dirt block
        player.setPosition({0, 3, 0});
    }

	world.add_block(Block("dirt"), {0, 2, 1});
	world.add_block(Block("dirt"), {0, 3, 2});
	world.add_block(Block("dirt"), {0, 4, 3});
    // setup camera and max FPS
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

	Vector3 saved_position;

    const std::pair<const Vector3, Block>* selected_block;
    while (!WindowShouldClose()) {
        // Update camera and player position
        Vector3 oldpos = camera.position;
        if (!player.hasInventoryOpen()) {
            UpdateCamera(&camera);
        }

        if (IsKeyDown(KEY_SPACE)){
            player.jump(world);
        }
        if (oldpos.x != camera.position.x) {
            player.move(camera.position.x - oldpos.x, 0, 0);
        }
        if (oldpos.z != camera.position.z) {
            player.move(0, 0, camera.position.z - oldpos.z);
        }

		player.gravity(world);


        //Inventory keyboard and mouse management
        player.handleInventoryGestures();

        player.checkCollisions(world);

        camera.position = player.getPosition();

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        world.draw();

		DrawGrid(15, 1.0f);

        // check for block highlighting
        selected_block = getTargetedBlock();
        if (selected_block != nullptr) {
            DrawBoundingBox(selected_block->second.getBoundingBox(selected_block->first), WHITE);
        }
        EndMode3D();

        //Inventory bar
        player.drawInventory();

        drawDebugText(selected_block);
        drawCursor();

        EndDrawing();
    }

    this->save();
}

Player* Game::getPlayer() {
    return &(this->player);
}

World Game::getWorld() const {
    return this->world;
}
