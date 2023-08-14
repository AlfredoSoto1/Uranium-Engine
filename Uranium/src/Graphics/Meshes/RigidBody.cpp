#include "RigidBody.h"
#include "Math/Operation.h"

using namespace Uranium::Core::Math;

namespace Uranium::Graphics::Meshes {

	RigidBody::RigidBody() :
		scale(scale),
		position(position),
		rotation(rotation),
		transformationMatrix(transformationMatrix)
	{

	}

	void RigidBody::update() {
		transform(&transformationMatrix, position, rotation, scale);
	}
}