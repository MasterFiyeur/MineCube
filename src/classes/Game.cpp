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
#include "WorldGeneration.h"

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

void Game::blockPlace(const std::pair<const Vector3, Block>* target) {
    if (target != nullptr) {
        Vector3 place;
        RayCollision collision;
        Ray mouseRay{
                camera.position,
                (Vector3) {camera.target.x - camera.position.x, camera.target.y - camera.position.y,
                           camera.target.z - camera.position.z}
        };
        Vector3 p1 = {target->first.x - 0.5f, target->first.y - 0.5f, target->first.z - 0.5f};
        Vector3 p2 = {target->first.x + 0.5f, target->first.y + 0.5f, target->first.z + 0.5f};
        BoundingBox object_bounding_box = {p1, p2};
        collision = GetRayCollisionBox(mouseRay, object_bounding_box);
        if (collision.point.x == target->first.x - 0.5f) {
            place = {target->first.x - 1, target->first.y, target->first.z};
        }
        if (collision.point.x == target->first.x + 0.5f) {
            place = {target->first.x + 1, target->first.y, target->first.z};
        }
        if (collision.point.y == target->first.y - 0.5f) {
            place = {target->first.x, target->first.y - 1, target->first.z};
        }
        if (collision.point.y == target->first.y + 0.5f) {
            place = {target->first.x, target->first.y + 1, target->first.z};
        }
        if (collision.point.z == target->first.z - 0.5f) {
            place = {target->first.x, target->first.y, target->first.z - 1};
        }
        if (collision.point.z == target->first.z + 0.5f) {
            place = {target->first.x, target->first.y, target->first.z + 1};
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            world.add_block(Block(player.getCurrentItem()->block->getName()), place);
        }
    }
}

void Game::blockBreak(const std::pair<const Vector3, Block>* target) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (target != nullptr)){
        world.remove_block(target->first);
    }
}

void Game::start() {
    if (world.isempty()) {
        std::cout << "Initializing world...." << std::endl;

		WorldGeneration new_world;
		Vector3 player_initial_pos;
		new_world.generate((std::rand()%65534),&world, &player_initial_pos);
        // init player position above the dirt block
        player.setPosition(player_initial_pos);
    }

    // setup camera and max FPS
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

	// Sky clouds image
	Image img_sky = LoadImage("../assets/sun.png");
	Texture2D sun = LoadTextureFromImage(img_sky);
	UnloadImage(img_sky);
	img_sky = LoadImage("../assets/clouds.png");
	Texture2D clouds = LoadTextureFromImage(img_sky);
	UnloadImage(img_sky);


    const std::pair<const Vector3, Block>* selected_block;
    while (!WindowShouldClose()) {

        if (!player.hasInventoryOpen()) {
            // Update camera and player position
            Vector3 oldpos = camera.position;
            UpdateCamera(&camera);

            // double press SPACE to enter/leave fly mode
            if (IsKeyPressed(KEY_SPACE)) {
                if (GetTime() - last_key_space_pressed < 0.2) {
                    player.applyGravity(!player.shouldApplyGravity());
                }
                last_key_space_pressed = GetTime();
            }
            if (IsKeyDown(KEY_SPACE)) {
                if (player.shouldApplyGravity())
                    player.jump(&world);
                else
                    player.move(0, 0.1f, 0);
            }
            if (IsKeyDown(KEY_LEFT_SHIFT) && !player.shouldApplyGravity()) {
                player.move(0, -0.1f, 0);
            }
            if (oldpos.x != camera.position.x) {
                player.move(camera.position.x - oldpos.x, 0, 0);
            }
            if (oldpos.z != camera.position.z) {
                player.move(0, 0, camera.position.z - oldpos.z);
            }
        }

        player.gravity(&world);

        //Inventory keyboard and mouse management
        player.handleInventoryGestures();

        player.checkCollisions(&world);

        camera.position = player.getPosition();

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

		//Drawing coulds in sky

		DrawCubeTexture(sun,{230,140,170},250,0.1,250,YELLOW);
		DrawCubeTexture(clouds, {0,100,0}, 1000.0, 0.1, 1000.0, WHITE); // Draw cube textured


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

	UnloadTexture(sun);
	UnloadTexture(clouds);
    this->save();
}

Player* Game::getPlayer() {
    return &(this->player);
}

World Game::getWorld() const {
    return this->world;
}
