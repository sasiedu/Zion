#pragma once

#include <GL/glew.h>
#include <util.h>
#include <glm/glm.hpp>

namespace Zion
{
	class Shader
	{
	private:
		GLuint      _programId = 0;
		bool        _isEnabled = false;
	private:
		bool        _createShaders(GLuint& vert, GLuint& frag, char *vertData, char *fragData);
		bool        _compileShader(GLuint& shader, const char *name, const char *data);
		bool        _createProgram(GLuint& vert, GLuint& frag, char *vertData, char *fragData);
	public:
		Shader() = default;
		Shader(const char *vertPath, const char *fragPath);
		~Shader();

		bool    initShader(const char *vertPath, const char *fragPath);
		void    enable();
		void    disable();
		GLint   getAttribLocation(char *name);
	};
}