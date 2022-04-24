//
// Created by cytech on 24/04/22.
//

#include <cmath>
#include "WorldGeneration.h"
#include <iostream>


WorldGeneration::WorldGeneration() : world(World()){
	int_noise = new int*[getHeight()];
	for (int i = 0; i < getHeight(); ++i) {
		int_noise[i] = new int[getWidth()];
		for (int j = 0; j < getWidth(); ++j) {
			int_noise[i][j] = 0;
		}
	}
}

WorldGeneration::~WorldGeneration() {
	for (int i = 0; i < getHeight(); ++i) {
		delete int_noise[i];
	}
	delete int_noise;
}


int WorldGeneration::getHeight() const {
	return height;
}

int WorldGeneration::getWidth() const {
	return width;
}

int WorldGeneration::getMaxDuneHeight() const {
	return max_dune_height+1;
}

void WorldGeneration::normalize() {
	int max_value = 255;
	int step = floor(((double)max_value) / ((double) getMaxDuneHeight()));
	for (int i = 0; i < getHeight(); ++i) {
		for (int j = 0; j < getWidth(); ++j) {
			int_noise[i][j] /= step;
		}
	}
}

void WorldGeneration::setWorld() {
	int mid_x = floor(((double) getWidth()) / ((double) 2) );
	int mid_z = floor(((double) getHeight()) / ((double) 2) );
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
	for (int i = 0; i < getHeight(); ++i) {
		for (int j = 0; j < getWidth(); ++j) {
			for (int k = 1; k <= int_noise[i][j]; ++k) {
				position.x = i - mid_x;
				position.y = k;
				position.z = j - mid_z;
				world.add_block(Block("dirt"),position);
			}
		}
	}
}

void WorldGeneration::generate(unsigned int seed, World *initial_world) {
	double x,y,n;
	PerlinNoise pn(seed);

	for (int i = 0; i < getHeight(); ++i) {
		for (int j = 0; j < getWidth(); ++j) {
			x = ((double) j)/((double) getWidth());
			y = ((double) i)/((double) getHeight());
			n = pn.noise(x,y,0.8);
			int_noise[i][j] = floor(255 * n);
		}
	}
	normalize();
	setWorld();
	*initial_world = world;
}

std::ostream &operator<<(std::ostream &os, const WorldGeneration &generation) {
	for (int i = 0; i < generation.getHeight(); ++i) {
		for (int j = 0; j < generation.getWidth(); ++j) {
			os << generation.int_noise[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}