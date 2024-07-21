#include "RenderableObject.h"

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Shaders;
using namespace Uranium::Graphics::Renderer;
using namespace Uranium::Graphics::Materials;

std::shared_ptr<Model> RenderableObject::getModel() const {
	return model;
}

std::shared_ptr<Assets> RenderableObject::getAssets() const {
	return assets;
}

std::shared_ptr<Material> RenderableObject::getMaterial() const {
	return material;
}

std::shared_ptr<ShaderProgram> RenderableObject::getShaderProgram() const {
	return shaderProgram;
}

void RenderableObject::setModel(std::shared_ptr<Model> model) {
	this->model = model;
}

void RenderableObject::setAssets(std::shared_ptr<Assets> assets) {
	this->assets = assets;
}

void RenderableObject::setMaterial(std::shared_ptr<Material> material) {
	this->material = material;
}

void RenderableObject::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
	this->shaderProgram = shaderProgram;
}
