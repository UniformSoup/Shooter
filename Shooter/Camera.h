#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Camera
{

	enum class Direction
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class Camera
	{
	private:
		float sensitivity, ylimit, speed;
		glm::vec3 direction, position;

	public:

		inline static glm::vec3 getDirection(const float& dx, const float& dy)
		{
			return glm::normalize(glm::vec3(cos(dy) * cos(dx), sin(dy), cos(dy) * sin(dx)));
		}
		inline static glm::vec3 getDirection(const glm::vec2& angles)
		{
			return glm::normalize(glm::vec3(cos(angles.y) * cos(angles.x), sin(angles.y), cos(angles.y) * sin(angles.x)));
		}
		/* Assumes you werent a smoothbrain and passed a normalised vector */
		inline static glm::vec2 getAngles(const glm::vec3& dir)
		{
			return glm::vec2(asin(dir.z / cos(asin(dir.y))), asin(dir.y));
		}

		Camera(const glm::vec3& pos = glm::vec3(0, 0, 3), const glm::vec3& dir = glm::vec3(0, 0, -1),
			const float& speed = 5.f, const float& sensitivity = 0.05f, const float& yanglelimit = 1.2f);

		void move(const float& dt, const Direction& d);
		inline void move(const glm::vec3& delta) { position += delta; };

		inline float getSensitivity() const { return sensitivity; }
		inline void setSensitivity(const float& f) { sensitivity = f; }

		inline void setylimit(const float& f) { ylimit = f; }
		inline float getylimit() const { return ylimit; }

		inline void setSpeed(const float& f) { speed = f; }
		inline float getSpeed() const { return speed; }

		inline void setPos(const glm::vec3& pos) { position = pos; }
		inline glm::vec3 getPos() const { return position; }

		glm::mat4 getView() const { return glm::lookAt(position, position + direction, glm::vec3(0, 1, 0)); }
		void setView(const unsigned int& viewpos) const { glUniformMatrix4fv(viewpos, 1, GL_FALSE, glm::value_ptr(getView())); }

		inline glm::vec3 getDirection() const { return direction; }
		/* Assumes you werent a smoothbrain and passed a normalised vector */
		inline void setDirection(const glm::vec3& dir) { direction = dir; }

		void rotate(const float& dx, const float& dy)
		{
			glm::vec2 angles = getAngles(direction);
			angles.x += dx; angles.y += dy;
			if (abs(angles.y) > ylimit) angles.y = ylimit * (abs(angles.y) / angles.y);

			direction = getDirection(angles);
		}
		void rotate(const glm::vec2& delta_angles)
		{
			glm::vec2 angles = getAngles(direction);
			angles += delta_angles;
			if (abs(angles.y) > ylimit) angles.y = ylimit * (abs(angles.y) / angles.y);

			direction = getDirection(angles);
			// use case: rotate(camera.getSensitivity() * {glm::radians(xpos - windowwidth / 2), glm::radians(windowheight / 2 - ypos)});
		}
	};
}