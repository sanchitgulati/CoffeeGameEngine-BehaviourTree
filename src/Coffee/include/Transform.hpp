#pragma once
#include "Vector.hpp"


namespace Coffee {
	struct Transform2D
	{
	public:
		vector2 position;
		vector2 scale;
		float rotation;

		Transform2D() {
			position = vector2(0, 0);
			scale = vector2(1, 1);
			rotation = 0;

		}
	};
}