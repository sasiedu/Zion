#pragma once

#include <renderable.hpp>
#include <material.hpp>

namespace Zion
{
	class   StaticSprite : public Renderable
	{
	protected:
		GLuint      _vao;
		GLuint      _vbo;
		GLuint      _ibo;
		Material    _material;
	public:
		virtual void    render(glm::mat4 matrix) = 0;
		void            addTextureFromFile(const char *path)
		{
			_material.texure.loadTextureFromPath(path);
		}
		void            addTextureFromData(unsigned char *data, size_t len)
		{
			_material.texure.loadTextureFromData(data, len);
		}
		void            addBaseColor(glm::vec4 color)
		{
			_material.base_color = color;
		}
	};

	///struct of a square sprite
	struct   SquareSprite : public StaticSprite
	{
	private:
		void    _loadDataToGpu(GLfloat *vertex, GLsizei vertCount, GLushort *indices, GLsizei indCount);
		void    _addVertexAttrib(GLsizei stride);
	public:
		SquareSprite(Shader& shader, float posx, float posy, float width, float height);
		~SquareSprite();

		void    render(glm::mat4 matrix);
	};
}