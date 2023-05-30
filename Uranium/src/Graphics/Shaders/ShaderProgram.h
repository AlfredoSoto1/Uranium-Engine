#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "ShaderTypes.h"

namespace Uranium::Scenes::Cameras {
	class Camera;
}

namespace Uranium::Graphics::Materials {
	class Material;
}

namespace Uranium::Graphics::Shaders {
	
	/*
	* These are all shader uniform enums
	* compatible with shader program. This
	* are used when setting a new uniform to
	* shader program in which it will contain
	* one of these enums. These enums prioritize how
	* they should be called in each renderer.
	*/
	enum Traits {
		POSITION_2D,
		POSITION_3D,

		TEXTURE_COORDS_2D,
		TEXTURE_COORDS_3D,

		VIEW_MATRIX,
		PROJECTION_MATRIX,

		COLOR_RGB,
		COLOR_RGBA,

		ALBEDO,
		NORMAL,
		SPECULAR,
		METAL,
		ROUGHNESS,

		MATRIX_2D,
		MATRIX_3D,
		MATRIX_4D,

		VECTOR_2D,
		VECTOR_3D,
		VECTOR_4D,

		INT,
		BYTE,
		FLOAT,
		SHORT,
		DOUBLE,
		BOOLEAN,
		UNSIGNED_INT,
		UNSIGNED_BYTE,
		UNSIGNED_SHORT,
	};

	class Shader;
	class BaseUniform;

	/*
	* Blueprint of a Shader program
	* 
	*/
	class ShaderProgram {
	public:
		/*
		* Custom alias
		*/
		using Camera = Scenes::Cameras::Camera;
		using Material = Materials::Material;

	public:
		template<class T, class... Args>
		ShaderProgram(const T& first, const Args&... args) {
			// create program
			create();

			// attach first always
			attachShader(first);

			// attach any other shader that
			// we also want
			(attachShader(args), ...);

			// initiate program
			init();
		}

		virtual ~ShaderProgram();

		/*
		* Start and stop methods that tells OpenGl
		* when to start using the shaders when rendering
		*/
		void start() const;
		void stop() const;

	public:
		/*
		* getters & setters
		*/

		/*
		* Returns the shader's program ID
		*/
		operator const Program() const;

		/*
		* Sends the base uniform generated
		* to the shader program to use with a specific
		* name given as a parameter
		*/
		void setUniform(const std::string& uniformName, std::shared_ptr<BaseUniform> baseUniform);
		
	private:
		/*
		* friends with other classes
		*/
		friend Shader;

	private:
		/*
		* private methods
		*/

		/*
		* creates the shader program
		*/
		void create();

		/*
		* links, validates and queries the uniforms
		*/
		void init();

		/*
		* attaches the target shader to 'this' program
		*/
		void attachShader(const Shader& shader);

		/*
		* detaches shader from currently bound program
		*/
		void detachShader(const Shader& shader);

		/*
		* This links the shaders with the program
		*/
		void link() const;

		/*
		* This validates the shader before using the
		* program. This method has to be called once
		* before starting the shader program
		*/
		void validate() const;
		
		/*
		* This queries the uniform locations
		* that exist inside the shader linked to this
		* shader program
		*/
		void queryUniformLocations();

	private:
		/*
		* private members
		*/
		mutable Program program;

		std::vector<std::shared_ptr<BaseUniform>> uniformVariables;
		std::unordered_map<std::string, UniformTraits> programUniforms;
	};
}