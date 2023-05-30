#include "Entity.h"
#include "Graphics/Meshes/RigidBody.h"
#include "Graphics/Shaders/ShaderMaterial.h"

using namespace Uranium::Scenes::Objects;
using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Shaders;

Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<ShaderMaterial> shaderMaterial) :
	model(model),
	shaderMaterial(shaderMaterial)
{
	
}

Entity::Entity(const Entity& copy) :
	rigidbody(copy.rigidbody),
	model(copy.model),
	shaderMaterial(copy.shaderMaterial)
{
	
}

Entity::Entity(Entity&& move) noexcept :
	rigidbody(std::move(move.rigidbody)),
	model(move.model),
	shaderMaterial(move.shaderMaterial)
{
	
}

RigidBody& Entity::getRigidBody() {
	return rigidbody;
}

std::shared_ptr<Model> Entity::getModel() {
	return model;
}

std::shared_ptr<ShaderMaterial> Entity::getShaderMaterial() {
	return shaderMaterial;
}

void Entity::setRigidBody(RigidBody&& rigidbody) {
	this->rigidbody = std::move(rigidbody);
}

void Entity::setRigidBody(const RigidBody& rigidbody) {
	this->rigidbody = rigidbody;
}

void Entity::setShaderMaterial(std::shared_ptr<Model> model) {
	this->model = model;
}

void Entity::setShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial) {
	this->shaderMaterial = shaderMaterial;
}