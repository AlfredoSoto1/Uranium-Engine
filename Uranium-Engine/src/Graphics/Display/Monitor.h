#pragma once

#include <glm/vec2.hpp>

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Graphics::Display {

	class Monitor final {
	public:
		/*
		* Friend with other instances
		*/
		friend class MonitorHandler;

	public:
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

	private:
		/*
		* Monitor reference and video mode
		*/
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
	};

}