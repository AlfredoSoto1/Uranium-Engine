#include "ShaderMaterial.h"

using namespace Uranium::Graphics::Shaders;
using namespace Uranium::Graphics::Materials;

std::shared_ptr<Assets> ShaderMaterial::getAssets() const {
	return assets;
}

std::shared_ptr<Material> ShaderMaterial::getMaterial() const {
	return material;
}

std::shared_ptr<ShaderProgram> ShaderMaterial::getShaderProgram() const {
	return shaderProgram;
}

void ShaderMaterial::setAssets(std::shared_ptr<Assets> assets) {
	this->assets = assets;
}

void ShaderMaterial::setMaterial(std::shared_ptr<Material> material) {
	this->material = material;
}

void ShaderMaterial::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
	this->shaderProgram = shaderProgram;
}
