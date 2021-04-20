#include "Camera.h"

namespace Camera
{
	Camera::Camera(const glm::vec3& pos, const glm::vec3& dir, const float& speed, const float& sensitivity, const float& yanglelimit)
	: direction(glm::normalize(dir)), position(pos), sensitivity(sensitivity), ylimit(yanglelimit), speed(speed) {}

	void Camera::move(const float& dt, const Direction& d)
	{
		switch (d)
		{
		case Direction::FORWARD:
			position += dt * speed * glm::normalize(glm::vec3(direction.x, 0, direction.z));
			break;
		case Direction::BACKWARD:
			position -= dt * speed * glm::normalize(glm::vec3(direction.x, 0, direction.z));
			break;
		case Direction::RIGHT:
			position += dt * speed * glm::cross(direction, glm::vec3(0, 1, 0)); // no need to normalise as both lengths are always 1.
			break;
		case Direction::LEFT:
			position -= dt * speed * glm::cross(direction, glm::vec3(0, 1, 0));
			break;
		case Direction::UP:
			position += glm::vec3(0, 1, 0);
			break;
		case Direction::DOWN:
			position -= glm::vec3(0, 1, 0);
			break;
		}
	}

	void Camera::rotate(const float& dx, const float& dy)
	{
		glm::vec2 angles = getAngles(direction);
		angles.x += dx; angles.y += dy;
		if (abs(angles.y) > ylimit) angles.y = ylimit * (abs(angles.y) / angles.y);

		direction = getDirection(angles);
	}

	void Camera::rotate(const glm::vec2& delta_angles)
	{
		glm::vec2 angles = getAngles(direction);
		angles += delta_angles;
		if (abs(angles.y) > ylimit) angles.y = ylimit * (abs(angles.y) / angles.y);

		direction = getDirection(angles);
		// use case: rotate(camera.getSensitivity() * {glm::radians(xpos - windowwidth / 2), glm::radians(windowheight / 2 - ypos)});
	}

}