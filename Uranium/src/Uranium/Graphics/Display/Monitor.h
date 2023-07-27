#pragma once

#include <vector>
#include <memory>

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Utils {
	struct Dimension;
}

namespace Uranium::Graphics::Display {

	/*
	* Monitor class
	* 
	*/
	class Monitor {
	public:
		/*
		* custom alias
		*/
		using Dimension = Utils::Dimension;
		using Application = Core::Application;

	public:
		// Delete the Monitor() constructor
		// since we dont want the client to
		// be creating hollow monitor objects
		Monitor() = delete;

		// Convert an instance to a
		// GLFWmonitor pointer
		operator GLFWmonitor* ();

		bool isConnected();

		int getRefreshRate();

		Dimension getDimensions();

	private:
		/*
		* firends with other classes
		*/
		friend Application;

	private:
		/*
		* private methods
		*/
		Monitor(GLFWmonitor* monitor);

	private:
		/*
		* private members
		*/
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
	};
}