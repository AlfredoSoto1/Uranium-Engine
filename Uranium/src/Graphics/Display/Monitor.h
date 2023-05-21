#pragma once

#include <vector>
#include <memory>

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Graphics::Display {

	class Monitor {
	public:
		/*
		* static methods
		*/

		/*
		* @return the primary monitor
		*/
		static std::shared_ptr<Monitor> getPrimaryMonitor();
		
		/*
		* @return a vector containing all
		* monitors that are connected to the PC. and are registered
		* by the GPU.
		*/
		static std::vector<std::shared_ptr<Monitor>> getConnectedMonitors();

	public:
		Monitor();
		virtual ~Monitor();

		operator GLFWmonitor* ();

		int getWidth();
		int getHeight();
		int getRefreshRate();

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