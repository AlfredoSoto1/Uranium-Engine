#pragma once

#include <memory>

namespace Uranium::Graphics::Shaders {
	class ShaderProgram;
}

namespace Uranium::Graphics::Renderer {

	/*
	* Blueprint of Abstract Renderer object
	* 
	* This class operates and controls how renderable objects
	* should be rendered on to the screen
	*/
	class Renderer {
	public:
		/*
		* Custom Alias
		*/
		using ShaderProgram = Shaders::ShaderProgram;

	public:
		/*
		* This method is incharge of drawing
		* the object in the scene.
		*/
		virtual void draw() const = 0;

		/*
		* Binds all resources before drawing
		*/
		virtual void bindResources() const = 0;

		/*
		* Prepares the states before rendering
		*/
		virtual void prepareRenderStates() const = 0;

		/*
		* Resets the rendering states back to
		* default, so that they dont conflic with
		* possible next render call from another renderer
		*/
		virtual void cleanUpRenderStates() const = 0;
	
	private:
		/*
		* Protected members
		*/
		bool renderOnWireframe;

	};
}