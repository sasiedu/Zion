#include <renderable.hpp>

namespace Zion
{
	Renderer::Renderer(const Renderer &rhs)
	{
		*this = rhs;
	}

	Renderer& Renderer::operator=(const Renderer &rhs)
	{
		if (this != &rhs)
		{
			_models = rhs._models;
			_mats = rhs._mats;
		}
		return *this;
	}

	Renderer::~Renderer()
	{
		_models.clear();
		_mats.clear();
	}

	void Renderer::addToRender(Renderable *model, glm::mat4 mat)
	{
		_models.push_back(model);
		_mats.push_back(mat);
	}

	void Renderer::render()
	{
		for (int i = 0; i < _models.size(); i++)
			_models[i]->render(_mats[i]);
	}
}