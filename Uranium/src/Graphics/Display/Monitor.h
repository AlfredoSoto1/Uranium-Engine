#pragma once

#include <vector>
#include <memory>

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Graphics::Display {

	class Monitor {
	public:
		/// 
		/// static getter functions:
		/// getPrimaryMonitor() - returns the primary monitor
		/// getConnectedMonitors() - returns a vector containing all
		/// monitors that are connected to the PC. and are registered
		/// by the GPU.
		/// 
		static std::shared_ptr<Monitor> getPrimaryMonitor();
		static std::vector<std::shared_ptr<Monitor>> getConnectedMonitors();

	public:
		Monitor();
		virtual ~Monitor();

		operator GLFWmonitor* ();

		int getWidth();
		int getHeight();
		int getRefreshRate();

	private:
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;

		Monitor(GLFWmonitor* monitor);
	};
}