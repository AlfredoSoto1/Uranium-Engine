#pragma once

#include <memory>

namespace Uranium::Graphics::Renderer {
	class SceneRenderer;
}

namespace Uranium::Graphics::Shaders {
	
	class ShaderProgram;

	/*
	* LoadableShader interface
	* 
	*/
	class LoadableShader {
	public:
		/*
		* Custom alias
		*/
		using SceneRenderer = Renderer::SceneRenderer;

	private:
		/*
		* friends with other classes
		*/
		friend SceneRenderer;

	protected:
		/*
		* protected methods
		*/

		/*
		* loads the uniforms before rendering
		*/
		virtual void preloadUniforms(std::shared_ptr<ShaderProgram> shaderProgram) = 0;
		
		/*
		* loads the uniforms while rendering
		*/
		virtual void updateUniforms(std::shared_ptr<ShaderProgram> shaderProgram) = 0;
	};
}