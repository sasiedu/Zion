#pragma once

#include <stb_image.h>
#include <iostream>
#include <window.hpp>
#include <glm/glm.hpp>

namespace Zion
{
	class   Texture
	{
	private:
		GLuint  _textId;
		bool    _loaded = false;
		int     _width;
		int     _height;
		int     _channel;
	private:
		bool    _loadImageToGPU(unsigned char *data);
	public:
		Texture() = default;
		Texture(const char *path);
		Texture(const Texture & rhs);
		Texture&    operator=(const Texture & rhs);
		~Texture();

		bool    loadTextureFromPath(const char *path);
		bool    loadTextureFromData(unsigned char *data, size_t len);
		bool    isLoaded() const;
	};

	struct      Material
	{
		Texture     texure;
		glm::vec4   base_color;
		glm::vec4   spec_color;
	};
}