#include <staticSprite.hpp>

namespace Zion
{
	CubeSprite::CubeSprite(Shader &shader, float posx, float posy, float posz, float breadth, float length, float height)
	{
		GLushort indices[] = {0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 7, 6, 5,
		                      5, 4, 7, 4, 0, 3, 3, 7, 4, 4, 5, 1, 1, 0, 4, 3, 2, 6,
		                      6, 7, 3};
		GLfloat vertices[] =
		{
			-(length / 2) + posx, -(height / 2) + posy, (breadth / 2) + posz, 0,
			(length / 2) + posx, -(height / 2) + posy, (breadth / 2) + posz, 0,
			(length / 2) + posx, (height / 2) + posy, (breadth / 2) + posz, 0,
			-(length / 2) + posx, (height / 2) + posy, (breadth / 2) + posz, 0,
			-(length / 2) + posx, -(height / 2) + posy, -(breadth / 2) + posz, 0,
			(length / 2) + posx, -(height / 2) + posy, -(breadth / 2) + posz, 0,
			(length / 2) + posx, (height / 2) + posy, -(breadth / 2) + posz, 0,
			-(length / 2) + posx, (height / 2) + posy, -(breadth / 2) + posz, 0
		};
		_shader = shader;
		_loadDataToGpu(vertices, 4 * 8, indices, 36,  sizeof(GLfloat) * 4);
	}

	CubeSprite::~CubeSprite()
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ibo);
		glDeleteVertexArrays(1, &_vao);
	}

	void CubeSprite::_addVertexAttrib(GLsizei stride)
	{
		GLint position = _shader.getAttribLocation((char *)"position");
		GLint matIndex = _shader.getAttribLocation((char *)"matIndex");

		if (position != -1)
		{
			glEnableVertexAttribArray((GLuint)position);
			glVertexAttribPointer((GLuint)position, 3, GL_FLOAT, GL_FALSE, stride, (void *)nullptr);
		}
		if (matIndex != -1)
		{
			glEnableVertexAttribArray((GLuint)matIndex);
			glVertexAttribPointer((GLuint)matIndex, 1, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(GLfloat) * 3));
		}
	}

	void CubeSprite::render(glm::mat4 matrix)
	{
		_shader.enable();
		_material.texure.bindTexture(0);
		_shader.setUniformMat4((GLchar *)"model_matrix", matrix);
		_shader.setUniform1i((GLchar *)"textures[0]", 0);
		_shader.setUniform1i((GLchar *)"isTexture[0]", (int)_material.texure.isLoaded());
		_shader.setUniform4f((GLchar *)"texColor[0]", _material.base_color);
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (const GLvoid *)nullptr);
		glBindVertexArray(0);
		_material.texure.unbindTexture();
		_shader.disable();
	}
}