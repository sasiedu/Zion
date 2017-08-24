#include <camera.hpp>
#include <renderable.hpp>

namespace Zion
{
	Camera::Camera(glm::vec3 position, glm::vec3 target, float pitch, float yaw)
	{
		_position = position;
		_target = target;
		_direction = glm::normalize(_position - _target);
		_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction));
		_up = glm::cross(_direction, _right);
		_updateCamera();
	}

	Camera::Camera(const Camera &rhs)
	{
		*this = rhs;
	}

	Camera& Camera::operator=(const Camera &rhs)
	{
		return *this;
	}

	Camera::~Camera()
	{
	}

	void Camera::_updateCamera()
	{
		_viewMatrix = glm::lookAt(_position, _position + _front, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return _viewMatrix;
	}

	void Camera::moveLeft(float val)
	{
		_position -= glm::normalize(glm::cross(_front, _up)) * (val * Renderable::deltaTime);
		_updateCamera();
	}

	void Camera::moveRight(float val)
	{
		_position += glm::normalize(glm::cross(_front, _up)) * (val * Renderable::deltaTime);
		_updateCamera();
	}

	void Camera::moveUp(float val)
	{
	}

	void Camera::moveDown(float val)
	{
	}

	void Camera::moveIn(float val)
	{
		_position += (val * Renderable::deltaTime) * _front;
		_updateCamera();
	}

	void Camera::moveOut(float val)
	{
		_position -= (val * Renderable::deltaTime) * _front;
		_updateCamera();
	}
}