#pragma once

#include <vector>
#include <memory>
#include <glm/vec2.hpp>

extern struct GLFWmonitor;
extern struct GLFWvidmode;

namespace Uranium::Services {
	extern class Application;
}

namespace Uranium::Display {

	class Monitor final {
	public:
		/*
		* Friend with other instances
		*/
		friend Services::Application;
		friend std::shared_ptr<Monitor>;

	public:
		/*
		* Returns the primary connected monitor.
		* If monitor is not connected it will return nullptr.
		*/
		static std::shared_ptr<Monitor> getPrimary();

		/*
		* Returns a vector of unique references to
		* all the monitors that are connected.
		*/
		static std::vector<std::shared_ptr<Monitor>> getConnectedMonitors();

	private:
		/*
		* Initializes and creates all avaliable monitors
		*/
		static void initMonitors();

		/*
		* Disposes all created monitors
		*/
		static void disposeMonitors();

		// list of all available monitors connected
		static std::unique_ptr<std::vector<std::shared_ptr<Monitor>>> availableMonitors;

	public:
		/*
		* This constructor used to create
		* a new unique instance of the connected monitors.
		*/
		explicit Monitor(GLFWmonitor* monitor) noexcept;

		/*
		* Prepare the default monitor destructor
		*/
		~Monitor() = default;

		/*
		* Returns the GLFWmonitor reference
		* for the overloaded-dereference operator
		*/
		operator GLFWmonitor* () const;

		/*
		* Returns true if the current monitor is connected
		*/
		bool isConnected() const;

		/*
		* Returns the monitor's refreshrate in hz
		*/
		unsigned int gerRefreshRate() const;

		/*
		* Returns the resolution of the connected monitor
		*/
		glm::ivec2 getResolution() const;

	private:
		/*
		* Monitor reference and video mode
		*/
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
	};

}