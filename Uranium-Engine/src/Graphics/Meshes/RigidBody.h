#pragma once

#include "Math/vec3.h"
#include "Math/mat4.h"

namespace Uranium::Graphics::Meshes {

	class RigidBody {
	public:
		/*
		* Custom alias
		*/
		using vec3 = Core::Math::vec3;
		using mat4 = Core::Math::mat4;

	public:
		/*
		* default constructor
		*/
		RigidBody();

		/*
		* updates the rigid body with its
		* corresponding transformation
		*/
		void update();

	public:
		/*
		* available members
		*/
		vec3 scale;
		vec3 position;
		vec3 rotation;

		mat4 transformationMatrix;
	};
}