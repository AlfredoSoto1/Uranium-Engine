#pragma once

#include "Scenes/Objects/Entity.h"
#include "Graphics/Shaders/ShaderProgram.h"

using namespace Uranium::Scenes::Objects;
using namespace Uranium::Graphics::Shaders;

class Cube : public Entity {
public:

	Cube(std::shared_ptr<Model> model, std::shared_ptr<ShaderMaterial> shaderMaterial) :
		Entity(model, shaderMaterial)
	{

	}

private:

	void preloadUniforms(std::shared_ptr<ShaderProgram> shaderProgram) override {

	}

	void updateUniforms(std::shared_ptr<ShaderProgram> shaderProgram) override {

	}

};