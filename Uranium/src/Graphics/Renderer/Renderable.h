#pragma once

namespace Uranium::Graphics::Renderer {
	
	/*
	* Renderable interface
	* This declares the methods required
	* to be implemented in order for an object
	* be renderable by the renderer
	*/
	class Renderable {
	protected:
		/*
		* friends with other classes
		*/
		friend class GroupRenderer;

	protected:
		/*
		* This draw() method is called inside the
		* desired renderer
		*/
		virtual void draw() = 0;

		/*
		* This loads the required uniforms to the shader program
		*/
		virtual void loadUniforms() = 0;

		/*
		* Binds the resources like:
		* materials, assets, textures, etc...
		*/
		virtual void bindResources() = 0; 

	};
}