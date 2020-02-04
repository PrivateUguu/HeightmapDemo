#include "Camera.h"

#include <iostream>

Camera::Camera()
	:yaw(0.0f),
	pitch(0.0f),
	cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
	cameraRight(glm::vec3(1.0f, 0.0f, 0.0f)),
	cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraDir(glm::vec3(0.0f, 0.0f, 1.0f)),
	cameraSpeed(8.0f)
{}

glm::mat4 Camera::viewMatrix()
{
	//GLM is column major!
	glm::mat4 rotation = {
		cameraRight.x, cameraUp.x, cameraDir.x, 0.0f,
		cameraRight.y, cameraUp.y, cameraDir.y, 0.0f,
		cameraRight.z, cameraUp.z, cameraDir.z, 0.0f,
		0.0f,          0.0f,       0.0f,        1.0f
	};

	glm::mat4 translate = {
		1.0f,         0.0f,         0.0f,         0.0f,
		0.0f,         1.0f,         0.0f,         0.0f,
		0.0f,         0.0f,         1.0f,         0.0f,
		-cameraPos.x, -cameraPos.y, -cameraPos.z, 1.0f
	};

	// View matrix is formed by inverting the transformation placing the camera in WCoords.
	return rotation * translate;
}

void Camera::updateOrientation(int xDelta, int yDelta)
{
	// Stop the camera from jerking when the mouse initially enters the window.
	if (firstFrame)
	{
		firstFrame = false;
		return;
	}

	yaw += xDelta * 0.75;
	if (yaw > 360.0f)
		yaw -= 360.0f;
	else if (yaw < -360.0f)
		yaw += 360.0f;

	pitch -= yDelta * 0.75;
	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	cameraDir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraDir.y = sin(glm::radians(pitch));
	cameraDir.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraDir = glm::normalize(-cameraDir);

	glm::vec3 tempUp(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(tempUp, cameraDir));
	cameraUp = glm::normalize(glm::cross(cameraDir, cameraRight));
}

void Camera::moveForwards(float timeDelta)
{
	cameraPos -= cameraDir * cameraSpeed * timeDelta;
}

void Camera::moveBackwards(float timeDelta)
{
	cameraPos += cameraDir * cameraSpeed * timeDelta;
}

void Camera::moveLeft(float timeDelta)
{
	cameraPos -= cameraRight * cameraSpeed * timeDelta;
}

void Camera::moveRight(float timeDelta)
{
	cameraPos += cameraRight * cameraSpeed * timeDelta;
}

void Camera::moveUp(float timeDelta)
{
	cameraPos += cameraUp * cameraSpeed * timeDelta;
}

void Camera::moveDown(float timeDelta)
{
	cameraPos -= cameraUp * cameraSpeed * timeDelta;
}
