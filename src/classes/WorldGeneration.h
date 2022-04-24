//
// Created by cytech on 24/04/22.
//

#ifndef RAYLIB_KELAWIN_WORLDGENERATION_H
#define RAYLIB_KELAWIN_WORLDGENERATION_H

#include <ostream>
#include "World.h"
#include "external/PerlinNoise.h"

class WorldGeneration {
private:
	World world;
	int** int_noise;

	int height = 10;
	int width = 10;
	int max_dune_height = 10; //Maximum is 255
public:
	WorldGeneration();
	virtual ~WorldGeneration();

	int getHeight() const;
	int getWidth() const;
	int getMaxDuneHeight() const;

	void normalize();
	void generate(unsigned int seed);

	friend std::ostream &operator<<(std::ostream &os, const WorldGeneration &generation);
};


#endif //RAYLIB_KELAWIN_WORLDGENERATION_H
