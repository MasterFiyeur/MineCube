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

	int noise_height = 250; // Noise generated height
	int noise_width = 250; // Noise generated width
	int map_height = 250; //Must be inferior to noise_height
	int map_width = 250; //Must be inferior to noise_width

	int max_dune_height = 10; //Maximum is 255
public:
	WorldGeneration();
	virtual ~WorldGeneration();

	int getNoiseHeight() const;
	int getNoiseWidth() const;
	int getMapHeight() const;
	int getMapWidth() const;
	int getMaxDuneHeight() const;

	void normalize();
	void setWorld();
	void generate(unsigned int seed, World *initial_world, Vector3 *player_pos);

	friend std::ostream &operator<<(std::ostream &os, const WorldGeneration &generation);
};


#endif //RAYLIB_KELAWIN_WORLDGENERATION_H
