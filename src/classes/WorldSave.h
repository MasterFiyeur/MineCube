//
// Created by Arthur on 28/02/2022.
//

#pragma once

#include "World.h"

class WorldSave {

public:
    static void save(World* world);
    static World load();
};
