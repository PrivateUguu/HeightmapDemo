#include "Grid.h"

#include "glm/glm.hpp"

Grid::Grid(int w, int h)
	:width(w),
	height(h),
	numCells((w - 1) * (h - 1))
{
	initGrid();
}

void Grid::initGrid()
{
	
	//TODO: Make this less brute force-ish. Also stop doing push_back. Will be awful for large grids.
	for (float z = 0.0f; z < height; z++)
	{
		for (float x = 0.0f; x < width; x++)
		{
			vertices.push_back(glm::vec3(x - (width/2), -0.5f, (height/2) - z));

			if (x < width - 1 && z < height - 1)
			{
				unsigned int botLeft = height * z + x;
				unsigned int botRight = height * z + x + 1;
				unsigned int topLeft = height * z + height + x;
				unsigned int topRight = height * z + height + x + 1;

				indices.push_back(glm::uvec3(botLeft, botRight, topRight));
				indices.push_back(glm::uvec3(botLeft, topRight, topLeft));
			}
		}
	}

	glGenVertexArrays(1, &gridVao);
	glBindVertexArray(gridVao);

	glGenBuffers(1, &gridVbo);

	glBindBuffer(GL_ARRAY_BUFFER, gridVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
		vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &gridEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec3),
		indices.data(), GL_STATIC_DRAW);
}

void Grid::drawGrid()
{
	glBindVertexArray(gridVao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEbo);
	glDrawElements(GL_TRIANGLES, 6 * numCells, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Grid::~Grid()
{
	glBindVertexArray(gridVao);
	glDeleteBuffers(1, &gridVbo);
	glDeleteBuffers(1, &gridEbo);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &gridVao);
}