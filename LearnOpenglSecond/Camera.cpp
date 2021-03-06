#include "pch.h"
#include "Camera.h"
#include <cstdio>
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	WorldUp = worldup;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp);
}


void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	printf("PITCH/YAW: %f %f", Pitch, Yaw);
	Pitch += deltaY * MouseSensitivity;
	Yaw += deltaX * MouseSensitivity;
	if (Pitch > 89.0) Pitch = 89.0;
	if (Pitch < -89.0) Pitch = -89.0;
	UpdateCameraVectors();
}
