#pragma once

#include <memory>

#include "Graphics/Shaders/LoadableShader.h"

namespace Uranium::Graphics::Shaders {
	class ShaderProgram;
}

namespace Uranium::Graphics::Materials {

	/*
	* Blueprint of Material
	*
	*/
	class Material : public Shaders::LoadableShader {
	public:
		/*
		* public alias
		*/
		using ShaderProgram = Shaders::ShaderProgram;

	public:
		/*
		* Default constructor
		*/
		Material();

		/*
		* Default destructor
		*/
		virtual ~Material();

		/*
		* Binds the material resources before use
		*/
		void bindResources() const;
		
		/*
		* Unbinds the material resources before use
		*/
		void unbindResources() const;

	protected:
		/*
		* Overrided protected methods
		*/
		void preloadUniforms(std::shared_ptr<ShaderProgram> shaderProgram) override;

		void updateUniforms(std::shared_ptr<ShaderProgram> shaderProgram) override;
	
	private:
		/*
		* Private members
		*/
	};
}