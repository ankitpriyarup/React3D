#include "Camera.h"
#include <iostream>

void Camera::updateCameraVectors()
{
	glm::vec3 _front;
	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(_front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch) :
	front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY)
{
	position = _position;
	worldUp = _up;
	yaw = _yaw;
	pitch = _pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(CameraMovement _direction, double _deltaTime)
{
	float velocity = (float)(movementSpeed * _deltaTime);
	switch (_direction)
	{
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case RIGHT:
		position += right* velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	}
}

void Camera::ProcessMouseMovement(float _xOffset, float _yOffset, bool _constrainPitch)
{
	_xOffset *= mouseSensitivity;
	_yOffset *= mouseSensitivity;

	yaw += _xOffset;
	pitch += _yOffset;

	if (_constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;

		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessPanMovement(float _xOffset, float _yOffset)
{
	position -= right  * _xOffset * mouseSensitivity * 0.1f;
	position -= up * _yOffset * mouseSensitivity * 0.1f;
}
