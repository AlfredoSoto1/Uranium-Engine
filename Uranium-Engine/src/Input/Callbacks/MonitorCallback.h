#pragma once

namespace Uranium::Core {
	class UnitProgram;
}

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	/*
	* Monitor callback blueprint
	* 
	*/
	class MonitorCallback {
	public:
		/*
		* Custom alias
		*/
		using Window = Graphics::Display::Window;

	public:
		/*
		* Delete the move/copy constructors
		* since we dont want the client to instantiate this class
		*/
		MonitorCallback(MonitorCallback& copy) = delete;
		MonitorCallback(MonitorCallback&& move) = delete;
		MonitorCallback(const MonitorCallback& copy) = delete;
		MonitorCallback(const MonitorCallback&& move) = delete;

	private:
		/*
		* Friends with other classes
		*/
		friend Core::UnitProgram;

	private:
		/*
		* Private static methods
		*/
		static void monitorCallback(GLFWmonitor* monitor, int event);

	private:
		/*
		* Private modifiers
		*/
		explicit MonitorCallback(Window* window);

	private:
		/*
		* Private members
		*/
		Window* window;

	};
}