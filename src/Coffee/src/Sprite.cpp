#include "../include/Sprite.hpp"

namespace Coffee {
	GLuint Sprite::_VAO = 0;
	const char* Sprite::_defaultVertexShaderFileName = "Shader/default.vs";
	const char* Sprite::_defaultFragmentShaderFileName = "Shader/default.fs";
	int Sprite::compiledDefaultShader = -1;

	std::shared_ptr<Sprite> Sprite::createWithFile(const std::string& filePath)
	{
		auto sprite = std::make_shared<Sprite>();
		sprite->initWithFile(filePath);
		sprite->init();
		return sprite;
	}


	void Sprite::initWithFile(const std::string& filePath) {
		loadTexture(filePath);
	}

	void Sprite::init(){
		GameObject::init();
		setDefaultShader();
		initRenderData();
		setColor(255, 255, 255);
	}

	void Sprite::setDefaultShader() {
		if (compiledDefaultShader != -1)
			_shader = std::make_unique<Shader>(compiledDefaultShader);
		else {
			_shader = std::make_unique<Shader>(_defaultVertexShaderFileName, _defaultFragmentShaderFileName, true);
			compiledDefaultShader = _shader->getProgramId();
		}
	}


	void Sprite::initRenderData()
	{
		//refactor this
		if (_VAO > 0)
			return;

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		unsigned int VBO, EBO;
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void Sprite::setColor(Color color)
	{
		_color = Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	}
	void Sprite::setColor(int r,int g,int b)
	{
		_color = Color(r / 255.0f, g/ 255.0f, b / 255.0f);
	}


	void Sprite::loadTexture(const std::string& path)
	{
		int w, h;
		_glTexture = TextureManager.getTexture(path,w,h);
		_size = vector2(w,h);
	}

	void Sprite::remove() {
		GameObject::removeChildren();
	}

	void Sprite::draw(matrix4& projection) {
		_shader->useShader();
		if (_isDirty) {
			_isDirty = false;
			matrix4 model = glm::identity<matrix4>();
			model = glm::translate(model, glm::vec3(_globalTransform.position, 0.0f));
			model = glm::rotate(model, glm::radians(_globalTransform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(_size, 1.0f));
			model = glm::scale(model, glm::vec3(_globalTransform.scale, 1.0f));
			_mTransform = model;

			auto inverseModel = glm::identity<matrix4>();
			inverseModel = glm::scale(inverseModel, glm::vec3(1.0f/ _globalTransform.scale, 1.0f));
			inverseModel = glm::rotate(inverseModel, glm::radians(-_globalTransform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			inverseModel = glm::translate(inverseModel, glm::vec3(-_globalTransform.position, 0.0f));
			_mTransformInverse = inverseModel;
		}

		_shader->setMatrix4("projection", projection);
		_shader->setMatrix4("model", _mTransform);
		_shader->setVector3("spriteColor", _color);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _glTexture);

		// render container
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		_shader->disableShader();

#ifdef DEBUG
		auto glError = glGetError();
		if (glError != GL_NO_ERROR)
			printf("SPRITE::GLError(%d)\n", glError);
#endif // DEBUG

		GameObject::draw(projection);
	}

}