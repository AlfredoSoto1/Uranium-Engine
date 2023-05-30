#pragma once

#include "Scenes/Objects/Entity.h"

using namespace Uranium::Scenes::Objects;

class Cube : public Entity {
public:

	Cube(std::shared_ptr<Model> model, std::shared_ptr<ShaderMaterial> shaderMaterial) :
		Entity(model, shaderMaterial)
	{

	}

private:

	void draw() override {

	}

	void loadUniforms() override {

	}

	void bindResources() override {

	}
};