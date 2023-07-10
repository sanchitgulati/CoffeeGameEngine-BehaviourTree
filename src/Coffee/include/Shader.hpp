#pragma once

#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#include <string>
#include <SDL_opengl.h>
#include "Vector.hpp"
#include <glm/ext.hpp>


namespace Coffee {
	// TODO: Refactor shaders to be apart of the renderer
	class Shader
	{
	private:
		GLuint _programId;
		GLuint compileShader(GLuint shaderType, const std::string& source);

	public:
		Shader();
		Shader(const std::string& vertexSource, const std::string& FragmentSource);
		Shader(const GLuint programId);
		Shader(const std::string& vertexFilename, const std::string& FragmentFilename,bool isFile);
		~Shader();
		void useShader() const;
		void disableShader() const;
		unsigned int getProgramId();
		unsigned int getAttribLocation(const std::string& attributeName);
		unsigned int getUniform(const std::string& uniformName);

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMatrix4(const std::string& name, matrix4 value) const;
		void setVector3(const std::string& name, glm::vec3 value) const;
	};
}
