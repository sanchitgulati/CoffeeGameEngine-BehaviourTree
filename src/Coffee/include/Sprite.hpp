#pragma once


#include "GameObject.hpp"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.hpp"
#include "Shader.hpp"
#include "Vector.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "SDLUtils.hpp"
#include "TextureManager.hpp"
#include "Color.hpp"

namespace Coffee {
	class Sprite : public GameObject
	{
	public:
		static std::shared_ptr<Sprite> createWithFile(const std::string& filePath);
		virtual void initWithFile(const std::string& filePath);
		virtual void draw(matrix4& projection);
		virtual void remove();
		void setColor(Color color);
		void setColor(int r, int g, int b);
	protected:
		void setDefaultShader();
		void init();
		void initRenderData();
		void loadTexture(const std::string& path);
		Color _color;
		static GLuint _VAO;
		GLuint _glTexture;
		std::unique_ptr<Shader> _shader;
		static const char* _defaultVertexShaderFileName;
		static const char* _defaultFragmentShaderFileName;
	private:
		static int compiledDefaultShader;
		//do this properly
	};
}