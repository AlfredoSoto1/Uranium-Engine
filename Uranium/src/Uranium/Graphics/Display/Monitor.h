#pragma once

#include <vector>

struct GLFWmonitor;
struct GLFWvidmode;

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

	public:
		// Returns the primary monitor if any
		static Monitor getPrimaryMonitor();

		// Return a vector containing all
		// the connected monitors to the PC
		// If no monitors are connected, vector will be empty
		static std::vector<Monitor> getConnectedMonitors();

	public:
		// Delete the Monitor() constructor
		// since we dont want the client to
		// be creating hollow monitor objects
		Monitor() = delete;

		// Convert an instance to a
		// GLFWmonitor pointer
		operator GLFWmonitor* () const;

		// Returns true if the current
		// instance is connected.
		bool isConnected() const;

		// Returns the monitor refreshrate in hz
		int getRefreshRate() const;

		// Returns the resolution of
		// the connected monitor
		Dimension getResolution() const;

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