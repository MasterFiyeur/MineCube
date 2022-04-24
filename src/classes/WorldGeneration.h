//
// Created by cytech on 24/04/22.
//

#ifndef RAYLIB_KELAWIN_WORLDGENERATION_H
#define RAYLIB_KELAWIN_WORLDGENERATION_H

#include <ostream>
#include "World.h"
#include "external/PerlinNoise.h" //External library got at https://github.com/sol-prog/Perlin_Noise

class WorldGeneration {
private:
	World world; //World that we'll generate
	int** int_noise; // 2D array symbolize world map, int correspond to number of blocks (height)

	int noise_height = 200; // Noise generated height
	int noise_width = 200; // Noise generated width
	int map_height = 50; // added blocks to the world on X-axis (must be inferior to noise_height)
	int map_width = 50; // added blocks to the world on Z-axis (must be inferior to noise_width)

	int max_dune_height = 15; //Maximum is 255
public:
	/**
	*\brief Construct a new World Generation object
	*
	*/
	WorldGeneration();
	/**
	*\brief Destroy the World Generation object
	*
	*/
	virtual ~WorldGeneration();

	/**
	*\brief noise_height getter
	*
	*\return int noise_height value
	*/
	int getNoiseHeight() const;
	/**
	*\brief noise_width getter
	*
	*\return int noise_width value
	*/
	int getNoiseWidth() const;
	/**
	*\brief map_height getter
	*
	*\return int map_height value
	*/
	int getMapHeight() const;
	/**
	*\brief map_width getter
	*
	*\return int map_width value
	*/
	int getMapWidth() const;
	/**
	*\brief max_dune_height getter, adding +1 for don't count the max_value (255)
	*
	*\return int max_dune_height value
	*/
	int getMaxDuneHeight() const;

	/**
	*\brief Normalize the int_noise array. It transform value between 0 and 255 to value between 0 and max_dune_height
	*
	*/
	void normalize();
	/**
	*\brief Create a world from the int_noise array
	*
	*/
	void setWorld();
	/**
	*\brief Generate a world of blocks using seed parameter
	*
	*\param seed Value to make the generation not random
	*\param initial_world World that we will generate
	*\param player_pos Player position that we will set from the highest block on (0,0)
	*/
	void generate(unsigned int seed, World *initial_world, Vector3 *player_pos);

	/**
	*\brief To string operator (display int_noise array)
	*
	*\param os Stream
	*\param generation WorldGeneration object
	*\return std::ostream& int_noise to string
	*/
	friend std::ostream &operator<<(std::ostream &os, const WorldGeneration &generation);
};


#endif //RAYLIB_KELAWIN_WORLDGENERATION_H
