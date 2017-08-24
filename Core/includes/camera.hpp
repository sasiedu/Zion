#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Zion
{
	class   Camera
	{
	private:
		glm::vec3   _position;
		glm::vec3   _direction;
		glm::vec3   _target;
		glm::vec3   _up;
		glm::vec3   _right;
		glm::vec3   _front = glm::vec3(0.0f, 0.0f, -1.0f);
		float       _pitch;
		float       _yaw;
		float       _roll;
		glm::mat4   _viewMatrix;
	private:
		void        _updateCamera();
	public:
		Camera(glm::vec3 position = glm::vec3(0, 0, 3), glm::vec3 target = glm::vec3(0, 0, 0),
		       float pitch = 0.0f, float yaw = 0.0f);
		Camera(const Camera & rhs);
		Camera&     operator=(const Camera& rhs);
		~Camera();

		glm::mat4       getViewMatrix() const;
		void            moveLeft(float val);
		void            moveRight(float val);
		void            moveUp(float val);
		void            moveDown(float val);
		void            moveIn(float val);
		void            moveOut(float val);
	};
}