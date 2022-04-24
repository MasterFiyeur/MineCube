//
// Created by cytech on 24/04/22.
//

#include <cmath>
#include "WorldGeneration.h"
#include <iostream>


WorldGeneration::WorldGeneration() : world(World()){
	int_noise = new int*[getNoiseHeight()];
	for (int i = 0; i < getNoiseHeight(); ++i) {
		int_noise[i] = new int[getNoiseWidth()];
		for (int j = 0; j < getNoiseWidth(); ++j) {
			int_noise[i][j] = 0;
		}
	}
}

WorldGeneration::~WorldGeneration() {
	for (int i = 0; i < getNoiseHeight(); ++i) {
		delete int_noise[i];
	}
	delete int_noise;
}


int WorldGeneration::getNoiseHeight() const {
	return noise_height;
}

int WorldGeneration::getNoiseWidth() const {
	return noise_width;
}

int WorldGeneration::getMapHeight() const {
	return map_height;
}

int WorldGeneration::getMapWidth() const {
	return map_width;
}

int WorldGeneration::getMaxDuneHeight() const {
	return max_dune_height+1;
}

void WorldGeneration::normalize() {
	int max_value = 255;
	int step = floor(((double)max_value) / ((double) getMaxDuneHeight()));
	for (int i = 0; i < getNoiseHeight(); ++i) {
		for (int j = 0; j < getNoiseWidth(); ++j) {
			int_noise[i][j] /= step;
		}
	}
}

void WorldGeneration::setWorld() {
	int mid_x = floor(((double) getMapHeight()) / ((double) 2) );
	int mid_z = floor(((double) getMapWidth()) / ((double) 2) );
	Vector3 start, end, position = {0,0,0};

	/* Fill the bedrock */
	start.x = -mid_x;
	start.y = 0;
	start.z	= -mid_z;
	end.x = mid_x-1;
	end.y = 0;
	end.z = mid_z-1;
	world.fill(Block("stone"),start,end);

	/* Make the terrain */
	for (int i = 0; i < getMapHeight(); ++i) {
		for (int j = 0; j < getMapWidth(); ++j) {
			for (int k = 1; k <= int_noise[i][j]; ++k) {
				position.x = i - mid_x;
				position.y = k;
				position.z = j - mid_z;
				world.add_block(Block("dirt"),position);
			}
		}
	}
}

void WorldGeneration::generate(unsigned int seed, World *initial_world, Vector3 *player_pos) {
	double x,y,n;
	PerlinNoise pn(seed);

	for (int i = 0; i < getNoiseHeight(); ++i) {
		for (int j = 0; j < getNoiseWidth(); ++j) {
			x = ((double) j)/((double) getNoiseWidth());
			y = ((double) i)/((double) getNoiseHeight());
			n = pn.noise(x,y,0.8);
			int_noise[i][j] = floor(255 * n);
		}
	}
	normalize();
	setWorld();
	*initial_world = world;
	Vector3 player_position;
	player_position.x = 0;
	player_position.z = 0;
	player_position.y = (float) (
		int_noise[
				(int) floor(((double) getMapWidth()) / ((double) 2) )
		][
			(int) floor(((double) getMapWidth()) / ((double) 2) )
		]+3 //Player size (1.8) + 1 block for security
	);
	*player_pos = player_position;
}

std::ostream &operator<<(std::ostream &os, const WorldGeneration &generation) {
	for (int i = 0; i < generation.getNoiseHeight(); ++i) {
		for (int j = 0; j < generation.getNoiseWidth(); ++j) {
			os << generation.int_noise[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}