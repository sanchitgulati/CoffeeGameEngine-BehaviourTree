#include <vector>
#include <iostream>

#include "../include/Shader.hpp"
#include "../include/FileManager.hpp"


namespace Coffee {

	const char* defaultVertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";


	const char* defaultFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"} \0";

	Shader::Shader(const std::string& vertexSource, const std::string& FragmentSource)
	{
		int idx = 0;
		_programId = glCreateProgram();
		auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexSource);
		auto fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, FragmentSource);
		glAttachShader(_programId, vertexShaderId);
		glAttachShader(_programId, fragmentShaderId);
		glLinkProgram(_programId);

		GLint isLinked;
		glGetProgramiv(_programId, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			printf("ERROR::SHADER::NOTLINKED");
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	Shader::Shader(const GLuint programId)
	{
		_programId = programId;
	}


	Shader::Shader() :
		Shader(defaultVertexShaderSource, defaultFragmentShaderSource)
	{
	}


	Shader::Shader(const std::string& vertexFilename, const std::string& FragmentFilename, bool isFile)
		: Shader(FileManager.getData(vertexFilename), FileManager.getData(FragmentFilename)) {
	
	}

	Shader::~Shader()
	{
	}

	GLuint Shader::compileShader(GLuint shaderType, const std::string& source)
	{
		using std::string;

		auto vertexShaderPointer = source.c_str();
		GLint lengths{ static_cast<int>(source.size()) };

		auto shaderId = glCreateShader(shaderType);

		glShaderSource(shaderId, 1, &vertexShaderPointer, &lengths);
		glCompileShader(shaderId);
		GLint isCompiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
				GLsizei length = 100;
				std::vector<GLchar> infoLog(length);
				glGetShaderInfoLog(shaderId, length, &length, &infoLog[0]);
				std::cout << infoLog.data() << std::endl;
		}


		return shaderId;
	}

	unsigned int Shader::getAttribLocation(const std::string& attributeName)
	{
		auto location = glGetAttribLocation(_programId, attributeName.c_str());
		return location;
	}

	unsigned int Shader::getUniform(const std::string& uniformName)
	{
		auto location = glGetUniformLocation(_programId, uniformName.c_str());
		return location;
	}

	void Shader::useShader() const
	{
		glUseProgram(_programId);
	}

	void Shader::disableShader() const
	{
		glUseProgram(0);
	}

	unsigned int Shader::getProgramId()
	{
		return _programId;
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(_programId, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(_programId, name.c_str()), value);
	}
	void Shader::setMatrix4(const std::string& name, matrix4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(_programId, name.c_str()),1,GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setVector3(const std::string& name, glm::vec3 value) const
	{
		glUniform3f(glGetUniformLocation(_programId, name.c_str()),value[0],value[1],value[2]);
	}
}