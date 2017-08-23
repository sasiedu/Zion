#pragma once

#include <shader.hpp>
#include <window.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Zion
{
	class   Renderable
	{
	protected:
		Shader  _shader;
	protected:
		static std::string  GetFilePathExtension(const std::string &fileName)
		{
			if (fileName.find_last_of(".") != std::string::npos)
				return fileName.substr(fileName.find_last_of(".") + 1);
			return "";
		}
	public:
		static double   startTime;

		virtual void    render(glm::mat4 matrix) = 0;
	};
}