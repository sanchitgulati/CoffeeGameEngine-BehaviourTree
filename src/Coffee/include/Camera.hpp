#pragma once
#include "Vector.hpp"

namespace Coffee {
	class Camera
	{
	public:
		matrix4 getCamera();
		void setCamera(matrix4 camera);

	private:
		matrix4 _camera;
	};
}