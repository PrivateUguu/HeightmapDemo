#ifndef GRID_H
#define GRID_H

#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Grid
{
public:
	Grid(int w, int h);
	~Grid();
	void initGrid();
	void drawGrid();

private:
	unsigned int gridVao, gridVbo, gridEbo;
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec3> indices;
	
	const float width;
	const float height;
	const int numCells;
};

#endif