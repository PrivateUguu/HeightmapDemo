#include "Heightmap.h"

#include <random>

Heightmap::Heightmap(float freqScale)
	:freq(freqScale),
	width(50),
	height(50)
{
	generateGradients();
}

void Heightmap::generateGradients()
{
	std::random_device rd;
	std::mt19937 prng(rd());
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	grads.resize(maxFreq + 1);
	for (int i = 0; i < maxFreq + 1; i++)
	{
		grads[i].resize(maxFreq + 1);
		for (int j = 0; j < maxFreq + 1; j++)
			grads[i][j] = glm::vec2(dist(prng), dist(prng));
	}
}

float Heightmap::noiseAt(float x, float y)
{
	/*
	 *  Unit square form:
	 *      V3           V2
	 *   <x0, y1>     <x1, y1>
	 *        * - - - - *
	 *        |         |
	 *        |         |
	 *        |         |
	 *        * - - - - *
	 *   <x0, y0>     <x1, y0>
	 *      V0           V1
	 */

	float xf = x * ((float)freq / (float)width);
	float yf = y * ((float)freq / (float)height);

	int x0 = floor(xf);
	int y0 = floor(yf);
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float dx0 = xf - x0;
	float dy0 = yf - y0;
	float dx1 = xf - x1;
	float dy1 = yf - y1;

	glm::vec2 d0 = glm::vec2(dx0, dy0);
	glm::vec2 d1 = glm::vec2(dx1, dy0);
	glm::vec2 d2 = glm::vec2(dx1, dy1);
	glm::vec2 d3 = glm::vec2(dx0, dy1);

	float q0 = glm::dot(grads[x0][y0], d0);
	float q1 = glm::dot(grads[x1][y0], d1);
	float q2 = glm::dot(grads[x1][y1], d2);
	float q3 = glm::dot(grads[x0][y1], d3);

	float wx = smoothStep(dx0);
	float wy = smoothStep(dy0);
	float ix0 = lerp(q0, q1, wx);
	float ix1 = lerp(q3, q2, wx);
	float res = lerp(ix0, ix1, wy);

	res += 0.5;
	if (res > 1.0)
		res = 1.0;
	else if (res < 0.0)
		res = 0.0;

	return res;
}

float Heightmap::lerp(float a, float b, float w)
{
	return a + w * (b - a);
}

float Heightmap::smoothStep(float t)
{
	return t * t * (3 - 2 * t);
}