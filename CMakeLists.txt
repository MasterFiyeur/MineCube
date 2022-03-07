cmake_minimum_required(VERSION 3.0)
project(raylib-kelawin)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

# Adding Raylib
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

# Adding JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(${PROJECT_NAME} src/main.cpp src/classes/Game.cpp src/classes/Block.cpp src/classes/World.cpp src/classes/TexturesManager.cpp src/classes/TexturesManager.h src/classes/WorldSave.cpp src/classes/WorldSave.h src/classes/Utils.h src/classes/Inventory.cpp src/classes/Inventory.h src/classes/Player.cpp src/classes/Player.h)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")