#include <staticSprite.hpp>

namespace Zion
{
	double  Renderable::startTime;

	SquareSprite::SquareSprite(Shader &shader, float posx, float posy, float width, float height)
	{
		GLushort indices[] = {0, 1, 2, 2, 3, 0};
		GLfloat vertices[] =
		{
			-(width / 2) + posx, (height / 2) + posy, 0, 0, 0, 0,
			(width / 2) + posx, (height / 2) + posy, 0, 1, 0, 0,
			(width / 2) + posx, -(height / 2) + posy, 0, 1, 1, 0,
			-(width / 2) + posx, -(height / 2) + posy, 0, 0, 1, 0
		};
		_shader = shader;
		_loadDataToGpu(vertices, 6 * 4, indices, 6);
	}

	SquareSprite::~SquareSprite()
	{
	}

	void SquareSprite::_loadDataToGpu(GLfloat *vertex, GLsizei vertCount, GLushort *indices, GLsizei indCount)
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
		Window::getError((char *)"square vertex buffer");
		_addVertexAttrib(sizeof(GLfloat) * 6);
		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(GLushort), indices, GL_STATIC_DRAW);
		glBindVertexArray(0);
		Window::getError((char *)"square index array buffer");
	}

	void SquareSprite::_addVertexAttrib(GLsizei stride)
	{
		GLint position = _shader.getAttribLocation((char *)"position");
		GLint matIndex = _shader.getAttribLocation((char *)"matIndex");
		GLint uv = _shader.getAttribLocation((char *)"uv");

		if (position != -1)
		{
			glEnableVertexAttribArray((GLuint)position);
			glVertexAttribPointer((GLuint)position, 3, GL_FLOAT, GL_FALSE, stride, (void *)nullptr);
		}
		if (matIndex != -1)
		{
			glEnableVertexAttribArray((GLuint)matIndex);
			glVertexAttribPointer((GLuint)matIndex, 1, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(GLfloat) * 5));
		}
		if (uv != -1)
		{
			glEnableVertexAttribArray((GLuint)uv);
			glVertexAttribPointer((GLuint)uv, 2, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(GLfloat) * 3));
		}
		Window::getError((char *)"square add vertex attrib");
	}

	void SquareSprite::render(glm::mat4 matrix)
	{
		_shader.enable();
		_material.texure.bindTexture(0);
		_shader.setUniform1i((GLchar *)"textures[0]", 0);
		_shader.setUniform1i((GLchar *)"isTexture[0]", (int)_material.texure.isLoaded());
		_shader.setUniform4f((GLchar *)"texColor[0]", _material.base_color);
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const GLvoid *)nullptr);
		glBindVertexArray(0);
		_material.texure.unbindTexture();
		_shader.disable();
	}
}