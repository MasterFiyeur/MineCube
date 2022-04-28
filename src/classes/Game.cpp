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
#include "TexturesManager.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"


Game::Game() {
    // Define the camera to look into our 3d world
    this->camera = { 0 };
//    camera.target = (Vector3){ -1.0f, 0.0f, 0.0f };      // Camera looking at point
//    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 40.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    auto save = WorldSave::load();
    this->world = save.world;
    this->player.setPosition(save.playerPosition);
    this->player.setOrientation(save.playerOrientation);
    this->player.applyGravity(!save.playerIsFlying);
    this->last_save = std::time(nullptr);

    camera.up = player.getUp();
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
    Vector3 direction = player.getDirection();
    if (std::abs(direction.x) < 0.01) {
        n_s = "";
    } else if (direction.x > 0) {
        n_s = "N";
    } else {
        n_s = "S";
    }
    if (std::abs(direction.z) < 0.01) {
        e_w = "";
    } else if (direction.z > 0) {
        e_w = "E";
    } else {
        e_w = "W";
    }
    return n_s + e_w;
}

const std::pair<const Vector3, Block*>* Game::getTargetedBlock() const {
    const std::pair<const Vector3, Block*>* selected_block = nullptr;
    float selection_distance = 7.0f;

    Ray mouseRay = {
            player.getPosition(),
            player.getDirection()
    };
    for (const auto& block : world.get_blocks({camera.position.x - selection_distance, camera.position.y - selection_distance, camera.position.z - selection_distance},
                                              {camera.position.x + selection_distance, camera.position.y + selection_distance, camera.position.z + selection_distance})) {
        RayCollision collision = GetRayCollisionBox(mouseRay, block.second->getBoundingBox(block.first));
        if (collision.hit && collision.distance < selection_distance) {
            selected_block = &block;
            selection_distance = collision.distance;
        }
    }

    return selected_block;
}

std::string Game::getDebugText(const std::pair<const Vector3, Block*>* selected_block) const {
    char upperText[200];
    Vector3 player_position = player.getPosition();
    sprintf(upperText, "FPS: %d\nPosition: %.1f, %.1f, %.1f\nLooking at: %.1f, %.1f, %.1f (%s)\nHour: %d:%d",
            GetFPS(),
            player_position.x, player_position.y, player_position.z,
            camera.target.x, camera.target.y, camera.target.z, this->getCameraDirection().c_str(),
            getDayHour(), getDayMinute()
    );
    if (selected_block != nullptr) {
        sprintf(upperText, "%s\nTargeted block: %.1f %.1f %.1f (%s)",upperText,
                selected_block->first.x,  selected_block->first.y,  selected_block->first.z, selected_block->second->getName().c_str());
    }
    return upperText;
}

void Game::blockPlace(const std::pair<const Vector3, Block*>* target) {
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && target != nullptr && player.getCurrentItem()->block != nullptr) {
        Vector3 place;
        RayCollision collision;
        Ray mouseRay = {
                camera.position,
                normalize({camera.target.x - camera.position.x, camera.target.y - camera.position.y, camera.target.z - camera.position.z})
        };
        Vector3 p1 = {target->first.x - 0.5f, target->first.y - 0.5f, target->first.z - 0.5f};
        Vector3 p2 = {target->first.x + 0.5f, target->first.y + 0.5f, target->first.z + 0.5f};
        BoundingBox object_bounding_box = {p1, p2};
        collision = GetRayCollisionBox(mouseRay, object_bounding_box);
        if (abs(collision.point.x - (target->first.x - 0.5f)) < .01f) {
            place = {target->first.x - 1, target->first.y, target->first.z};
        }
        else if (abs(collision.point.x - (target->first.x + 0.5f)) < .01f) {
            place = {target->first.x + 1, target->first.y, target->first.z};
        }
        else if (abs(collision.point.y - (target->first.y - 0.5f)) < .01f) {
            place = {target->first.x, target->first.y - 1, target->first.z};
        }
        else if (abs(collision.point.y - (target->first.y + 0.5f)) < .01f) {
            place = {target->first.x, target->first.y + 1, target->first.z};
        }
        else if (abs(collision.point.z - (target->first.z - 0.5f)) < .01f) {
            place = {target->first.x, target->first.y, target->first.z - 1};
        }
        else if (abs(collision.point.z - (target->first.z + 0.5f)) < .01f) {
            place = {target->first.x, target->first.y, target->first.z + 1};
        }
        else {
            return;
        }
        std::string block_name = player.getCurrentItem()->block->getName();
        audio.playSound(AudioManager::getSoundTypePlace(block_name));
        add_block_by_name(world, block_name, place);
    }
}

void Game::blockBreak(const std::pair<const Vector3, Block*>* target) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (target != nullptr)) {
        audio.playSound(AudioManager::getSoundTypeBreak(target->second->getName()));
        world.remove_block(target->first);
    }
}

void Game::start() {
    if (world.isempty()) {
        std::cout << "Initializing world...." << std::endl;

        /* Generate world */
		WorldGeneration new_world;
		Vector3 player_initial_pos;
		int seed = std::rand()%65534;
        // Generate world using random seed
		new_world.generate(seed,&world, &player_initial_pos);
        // init player position above the highest block on x=0 and z=0
        player.setPosition(player_initial_pos);
        camera.position = player_initial_pos;
        // add a single flower
        auto tulip = new Flower("white_tulip");
        world.add_block(tulip, player_initial_pos - (Vector3){0, 2, 0});
        // set hour to 6 am
        world.setTime(DAY_LENGTH/4);

		// Print seed value used
		std::cout << "The seed used for generation is : " << seed << std::endl;
    } else {
        camera.position = player.getPosition();
        if (norm(player.getPosition() - player.getOrientation()) < .1f) {
            camera.target = player.getOrientation();
        }
    }

    // init audio (load sounds)
    audio.init();

    // setup camera and max FPS
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

    // Sky clouds + sun models
    Model sun = LoadModelFromMesh(GenMeshSphere(10.0,10,20));
    sun.materials[0].shader = *TexturesManager::getClassicShader();
	Vector3 sunPos = {0,0,0};
    Model clouds = LoadModelFromMesh(GenMeshCube(3000.0, 0.1, 3000.0));
    clouds.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(TexturesManager::getTexture("clouds"));
    clouds.materials[0].shader = *TexturesManager::getClassicShader();

    TexturesManager::setShaderBrightness(getSkyBrightness());

    float fogColor[4]; // sky + fog color

//    How to add a light point
//    CreateLight(LIGHT_POINT, (Vector3){ 0, 4, 6 }, {0, 1, 0}, BLUE, shader);


    const std::pair<const Vector3, Block*>* selected_block = nullptr;
    std::string debugText = getDebugText(selected_block);

    while (!WindowShouldClose()) {
        // update music
        audio.updateMusic();

        if (!player.hasInventoryOpen()) {
            // Update camera and player position
            UpdateCamera(&camera);

            // double press SPACE to enter/leave fly mode
            if (IsKeyPressed(KEY_SPACE)) {
                if (GetTime() - last_key_space_pressed < 0.25) {
                    player.applyGravity(!player.shouldApplyGravity());
                }
                last_key_space_pressed = GetTime();
            }
            // press mouse wheel to pick a block
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && selected_block != nullptr) {
                player.editSelectedItem(selected_block->second);
            }

            // press space to go up
            if (IsKeyDown(KEY_SPACE)) {
                if (player.shouldApplyGravity())
                    player.jump(&world);
                else
                    player.move(0, 0.1f, 0);
            }
            // press left shift to go down
            if (IsKeyDown(KEY_LEFT_SHIFT) && !player.shouldApplyGravity()) {
                player.move(0, -0.1f, 0);
            }
            // update player position from camera position
            if (player.getPosition().x != camera.position.x) {
                player.move(camera.position.x - player.getPosition().x, 0, 0);
            }
            if (player.getPosition().z != camera.position.z) {
                player.move(0, 0, camera.position.z - player.getPosition().z);
            }
            player.setOrientation(camera.target);
        }

        player.gravity(&world);

        //Inventory keyboard and mouse management
        player.handleInventoryGestures();

        player.checkCollisions(&world);

        camera.position = player.getPosition();

        // check for block highlighting
        selected_block = getTargetedBlock();

        blockBreak(selected_block);
        blockPlace(selected_block);

        // Draw
        // Update the light shader with the camera view position
        TexturesManager::setShaderPosition(camera.position);
        // Update the light shader with the fog color (world time)
        colorToFloat(getSkyColor(), fogColor);
        TexturesManager::setShaderColor(fogColor);
        // update the light shader with the sky brightness
        TexturesManager::setShaderBrightness(getSkyBrightness());

        BeginDrawing();
        ClearBackground(getSkyColor());
        BeginMode3D(camera);

        // Draw clouds and sun in sky
//        DrawCubeTexture(sun,{-140,240,240},250,0.1,250,YELLOW);
//        DrawCubeTexture(clouds, {0,200,0}, 3000.0, 0.1, 3000.0, WHITE); // Draw cube textured

		sunPos.z = player.getPosition().z + 240 * cos(2 * M_PI * (getDaytime() / DAY_LENGTH_D) - M_PI/2.0f);
		sunPos.y = player.getPosition().y + 240 * sin(2 * M_PI * (getDaytime() / DAY_LENGTH_D) - M_PI/2.0f);
		DrawModel(sun,sunPos,1.0f,BLACK);
		sun.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = getSunColor();
		DrawModel(clouds, {0,200,0}, 1.0f, BLANK);

        world.draw(&player);

        DrawGrid(15, 1.0f);


        // Check for block highlighting
        selected_block = getTargetedBlock();
        if (selected_block != nullptr) {
            DrawBoundingBox(selected_block->second->getBoundingBox(selected_block->first), WHITE);
        }

        // Debug text (position, orientation, etc.)
        debugText = getDebugText(selected_block);
        EndMode3D();
        DrawText(debugText.c_str(), 10, 10, 15, {230, 220, 220, 250});
        // Player cursor
        drawCursor();

		// Inventory bar
		player.drawInventory();

        EndDrawing();
    }

//    UnloadTexture(sun);
//    UnloadTexture(clouds);
    UnloadModel(sun);
    UnloadModel(clouds);

    this->save();
}

Player* Game::getPlayer() {
    return &(this->player);
}

World Game::getWorld() const {
    return this->world;
}

float Game::getSkyBrightness() const {
    // calculate hour of the day
    float daytime = getDaytime();
    // calculate sky brightness
    float brightness = (float) sin((daytime - DAY_LENGTH_D / 4.0f) * 2.0f * M_PI / DAY_LENGTH_D) / 2.0f + 0.5f;
    // make the minimum a bit higher (0.1)
    brightness = brightness * 0.9f + 0.1f;
    return brightness;
}

Color Game::getSkyColor() const {
    float world_daylight = getSkyBrightness();
    // SKYBLUE = {102, 191, 255} = {0.4, 0.75, 1.0}
    float red = world_daylight * 0.4f;
    float green = world_daylight * 0.75f;
    float blue = world_daylight * 1.0f;
    float color[4] = {red, green, blue, 1.0f};
    return floatToColor(color);
}

Color Game::getSunColor() const {
	float world_daylight = getSkyBrightness();
	float red = 1.0f;
	float green = world_daylight;
	float blue = 0.0f;
	float color[4] = {red, green, blue, 1.0f};
	return floatToColor(color);
}

float Game::getDaytime() const {
    return (float) fmod(world.getTime(), DAY_LENGTH);
}

int Game::getDayHour() const {
    return (int) floor(getDaytime() * HOUR_LENGTH);
}

int Game::getDayMinute() const {
    return (int) ((getDaytime() * HOUR_LENGTH - (float) getDayHour())*60.0f);
}
