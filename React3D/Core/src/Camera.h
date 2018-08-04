#pragma once
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const double YAW = -90.0f;
const double PITCH = 0.0f;
const double SPEED = 6.0f;
const double SENSITIVITY = 0.25f;
const double ZOOM = 45.0f;

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	void updateCameraVectors();

public:
	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
		float _yaw = YAW, float _pitch = PITCH);
	glm::mat4 GetViewMatrix() const;
	void ProcessKeyboard(CameraMovement _direction, float _deltaTime);
	void ProcessMouseMovement(float _xOffset, float _yOffset, bool _constrainPitch = true);
	void ProcessMouseScroll(float _yOffset);
	GLfloat GetZoom() const;
};