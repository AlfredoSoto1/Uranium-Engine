#pragma once

namespace Uranium::Graphics::Shaders {
	
	// definition of shader program
	using Program = unsigned int;

	//definition of uniform type
	using UniformType = unsigned int;

	// definition of uniform location
	using UniformLocation = int;

	// definition of Shader id
	using ShaderId = unsigned int;

	using UniformTraits = std::pair<UniformLocation, UniformType>;
}