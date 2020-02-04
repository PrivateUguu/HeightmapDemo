#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "glm/glm.hpp"
#include <vector>

class Heightmap
{
public:
		Heightmap(float freq);
		float noiseAt(float x, float y);
private:
	const int maxFreq = 16;
	int height, width, freq;
	std::vector<std::vector<glm::vec2>> grads;

	void generateGradients();
	float lerp(float a, float b, float w);
	float smoothStep(float t);
};

#endif