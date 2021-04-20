#include "Camera.h"

namespace Camera
{
	Camera::Camera(const glm::vec3& pos, const glm::vec3& dir, const float& speed, const float& sensitivity, const float& yanglelimit)
	: direction(glm::normalize(dir)), position(pos), sensitivity(sensitivity), ylimit(yanglelimit), speed(speed)
	{
		yangle = asin(direction.y); xangle = asin(direction.z / cos(yangle));
	}

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

}