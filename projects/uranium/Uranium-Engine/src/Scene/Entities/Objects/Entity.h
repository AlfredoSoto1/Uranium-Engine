#pragma once

#include <memory>

#include "Graphics/Meshes/Model.h"
#include "Graphics/Meshes/RigidBody.h"
#include "Graphics/Shaders/LoadableShader.h"

namespace Uranium::Graphics::Shaders {
	class ShaderMaterial;
}

namespace Uranium::Scenes::Objects {

	class Entity : public Graphics::Shaders::LoadableShader {
	public:
		/*
		* custom alias
		*/
		using Model = Graphics::Meshes::Model;
		using RigidBody = Graphics::Meshes::RigidBody;
		using ShaderMaterial = Graphics::Shaders::ShaderMaterial;

	public:
		/*
		* default constructor
		*/
		Entity(std::shared_ptr<Model> model, std::shared_ptr<ShaderMaterial> shaderMaterial);
		
		/*
		* copy constructor
		*/
		Entity(const Entity& copy);
		
		/*
		* move constructor
		*/
		Entity(Entity&& move) noexcept;
		
	public:
		/*
		* getters and setters
		*/
		RigidBody& getRigidBody();

		/*
		* Returns the current model attached 
		* to 'this' Entity instance
		*/
		std::shared_ptr<Model> getModel();

		/*
		* Returns a reference of the current shader
		* material of 'this' instance
		*/
		std::shared_ptr<ShaderMaterial> getShaderMaterial();

		/*
		* emplace / move a rigid body to 'this'
		* entity instance
		*/
		void setRigidBody(RigidBody&& rigidbody);
		
		/*
		* copy a rigid body to 'this' entity instance
		*/
		void setRigidBody(const RigidBody& rigidbody);

		/*
		* change the existing model
		*/
		void setShaderMaterial(std::shared_ptr<Model> model);

		/*
		* Set the new current shader material reference 
		* for this entity
		*/
		void setShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial);

	protected:
		/*
		* Protected members
		*/
		RigidBody rigidbody;

		std::shared_ptr<Model> model;
		std::shared_ptr<ShaderMaterial> shaderMaterial;
	};
}