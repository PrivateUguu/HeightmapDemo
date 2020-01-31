#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera
{
public:
	Camera();

	//TODO: Maybe switch out to be more type safe.
	enum direction { FORWARD, BACKWARD, LEFT, RIGHT };

	glm::mat4 viewMatrix();
	void updateOrientation(int xPos, int yPos);
	void updatePosition(direction dir);

private:
	float yaw;
	float pitch;

	glm::vec3 cameraPos;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraDir;

	bool firstFrame = true;
};

#endif