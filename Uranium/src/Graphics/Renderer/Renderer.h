#pragma once

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
	public:

	protected:
		/*
		* protected methods
		*/

		void render();

	private:
		/*
		* private methods
		*/

	private:
		/*
		* Private members
		*/
		bool renderOnWireframe;

	};
}