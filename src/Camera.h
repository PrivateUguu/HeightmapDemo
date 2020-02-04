#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

//TODO: Add more constructors.
class Camera
{
public:
	Camera();

	glm::mat4 viewMatrix();
	void updateOrientation(int xPos, int yPos);
	void moveForwards(float timeDelta = 1.0f);
	void moveBackwards(float timeDelta = 1.0f);
	void moveLeft(float timeDelta = 1.0f);
	void moveRight(float timeDelta = 1.0f);
	void moveUp(float timeDelta = 1.0f);
	void moveDown(float timeDelta = 1.0f);
	

private:
	float yaw;
	float pitch;

	glm::vec3 cameraPos;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraDir;

	float cameraSpeed;

	bool firstFrame = true;
};

#endif