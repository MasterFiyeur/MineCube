//
// Created by cytech on 24/04/22.
//

#include <cmath>
#include "WorldGeneration.h"


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
	return max_dune_height;
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

void WorldGeneration::generate(unsigned int seed) {
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