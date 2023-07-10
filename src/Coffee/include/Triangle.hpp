#pragma once

#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#include "GameObject.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <memory>
#include "Shader.hpp"
namespace Coffee {
	class Triangle : public GameObject
	{
	public:
		void init() override;
		void draw(matrix4& projection) override;
		static std::shared_ptr<Triangle> create();
	private:
		std::unique_ptr<Shader> _shader;
		GLuint _VBO;
		GLuint _VAO;
	};
}