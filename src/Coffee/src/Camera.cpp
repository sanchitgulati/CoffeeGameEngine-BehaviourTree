#include "../include/Camera.hpp"


namespace Coffee {
	matrix4 Camera::getCamera()
	{
		return _camera;
	}

	void Camera::setCamera(matrix4 camera)
	{
		_camera = camera;
	}

}
