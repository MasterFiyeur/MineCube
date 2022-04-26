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

#define initial_square 100

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif
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
    CHUNK chunk =  world.get_chunk_coo(player_position);
    sprintf(upperText, "FPS: %d\nPosition: %.1f, %.1f, %.1f  (%d %d)\nLooking at: %.1f, %.1f, %.1f (%s)",
            GetFPS(),
            player_position.x, player_position.y, player_position.z,
            chunk.x, (int) chunk.z,
            camera.target.x, camera.target.y, camera.target.z, this->getCameraDirection().c_str()
    );
    if (selected_block != nullptr) {
        sprintf(upperText, "%s\nTargeted block: %.1f %.1f %.1f (%s)",upperText,
                selected_block->first.x,  selected_block->first.y,  selected_block->first.z, selected_block->second->getName().c_str());
    }
    return upperText;
}

void Game::blockPlace(const std::pair<const Vector3, Block>* target) {
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
        world.add_block(Block(player.getCurrentItem()->block->getName()), place);
    }
}

void Game::blockBreak(const std::pair<const Vector3, Block*>* target) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (target != nullptr)){
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

        auto tulip = new Flower("white_tulip");
        world.add_block(tulip, player_initial_pos - (Vector3){0, 2, 0});

		// Print seed value used
		std::cout << "The seed used for generation is : " << seed << std::endl;
    } else {
        camera.position = player.getPosition();
        camera.target = player.getOrientation();

    }

    // setup camera and max FPS
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

    // Sky clouds image
    Image img_sky = LoadImage("../assets/sun.png");
    Texture2D sun = LoadTextureFromImage(img_sky);
    UnloadImage(img_sky);
	Texture2D clouds = LoadTextureFromImage(LoadImage("../assets/clouds.png"));

    Shader shader = LoadShader(TextFormat("../assets/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("../assets/shaders/glsl%i/fog.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    TexturesManager::setShader(&shader);

    int ambientLoc = GetShaderLocation(shader, "ambient");
    float ambientColor[4] = {1.0f, 1.0f, 1.0f, 1.0f };
    SetShaderValue(shader, ambientLoc, ambientColor, SHADER_UNIFORM_VEC4);

    float fogDensity = 0.03f;
    int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
    SetShaderValue(shader, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);
    float fogColor[4] = {0.4f, 0.75f, 1.0f, 1.0f }; // skyblue color
    int fogColorLoc = GetShaderLocation(shader, "fogColor");
    SetShaderValue(shader, fogColorLoc, fogColor, SHADER_UNIFORM_VEC4);

//    How to add a light point
//    CreateLight(LIGHT_POINT, (Vector3){ 0, 4, 6 }, {0, 1, 0}, BLUE, shader);

    const std::pair<const Vector3, Block*>* selected_block = nullptr;
    std::string debugText = getDebugText(selected_block);

    while (!WindowShouldClose()) {

        if (!player.hasInventoryOpen()) {
            // Update camera and player position
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
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position, SHADER_UNIFORM_VEC3);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        // Draw clouds and sun in sky
        DrawCubeTexture(sun,{-140,240,240},250,0.1,250,YELLOW);
        DrawCubeTexture(clouds, {0,200,0}, 3000.0, 0.1, 3000.0, WHITE); // Draw cube textured

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
