#include "Terrain.h"

#include "glad.h"
#include "glm/gtc/matrix_transform.hpp"

Terrain::Terrain(int w, int h)
	:width(w),
	height(h),
	heightmap(Heightmap(4))
{
	generateTerrain();
	initTerrainBuffers();
}

void Terrain::initTerrainBuffers()
{
	// We need to know how many cubes we'll render before generating the buffer!
	if (!modelMats.size())
		generateTerrain();

	unsigned int vertSize = vertices.size() * sizeof(float);
	unsigned int colSize = color.size() * sizeof(float);
	unsigned int vecSize =  sizeof(glm::vec4);
	unsigned int bufferSize = vertSize + colSize + 4 * vecSize * width * height;

	glGenVertexArrays(1, &tVao);
	glBindVertexArray(tVao);

	glGenBuffers(1, &tVbo);
	glBindBuffer(GL_ARRAY_BUFFER, tVbo);
	
	glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize, vertices.data());
	glBufferSubData(GL_ARRAY_BUFFER, vertSize, colSize, color.data());
	glBufferSubData(GL_ARRAY_BUFFER, vertSize + colSize, modelMats.size() * 4 * vecSize, modelMats.data());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(vertSize));
	glVertexAttribDivisor(1, 1);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vecSize, (void*)(vertSize + colSize));
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vecSize, (void*)(vertSize + colSize + vecSize));
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vecSize, (void*)(vertSize + colSize + 2 * vecSize));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vecSize, (void*)(vertSize + colSize + 3 * vecSize));
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);
	
	glBindVertexArray(0);
}

void Terrain::generateTerrain()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			float cHeight = clampedHeight(i, j);

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(i, cHeight, j));
			modelMats.push_back(model);

			color.insert(color.end(), { 0.0f, cHeight / maxHeight, 1 - (cHeight / maxHeight) });
		}
	}
}

int Terrain::clampedHeight(int x, int y)
{
	return heightmap.noiseAt(x, y) * maxHeight;
}

void Terrain::drawTerrain()
{
	glBindVertexArray(tVao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, width * height);
	glBindVertexArray(0);
}