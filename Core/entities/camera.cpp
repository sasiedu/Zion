#include <camera.hpp>

namespace Zion
{
	Camera::Camera(glm::vec3 positon, float pitch, float yaw)
	{
		_position = positon;
		_pitch = pitch;
		_yaw = yaw;
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
		glm::mat4   viewMat;

		viewMat = glm::rotate(viewMat, glm::radians(_pitch), glm::vec3(1, 0, 0));
		viewMat = glm::rotate(viewMat, glm::radians(_yaw), glm::vec3(0, 1, 0));
		glm::vec3 negCameraPos = _position * -1.0f;
		viewMat = glm::translate(viewMat, negCameraPos);
		_viewMatrix = viewMat;
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return _viewMatrix;
	}

	void Camera::moveLeft(float val)
	{
		_position.x -= val;
		_updateCamera();
	}

	void Camera::moveRight(float val)
	{
		_position.x += val;
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
		_position.z -= val;
		_updateCamera();
	}

	void Camera::moveOut(float val)
	{
		_position.z += val;
		_updateCamera();
	}
}