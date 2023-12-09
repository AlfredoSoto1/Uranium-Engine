#pragma once

#include <vector>
#include <memory>
#include <glm/vec2.hpp>

extern struct GLFWmonitor;
extern struct GLFWvidmode;

namespace Uranium::Display {

	class Monitor final {
	public:
		/*
		* Returns the primary connected monitor.
		* If monitor is not connected it will return nullptr.
		*/
		static std::unique_ptr<Monitor> getPrimary();
		
		/*
		* Returns a vector of unique references to
		* all the monitors that are connected.
		*/
		static std::vector<std::unique_ptr<Monitor>> getConnectedMonitors();

	public:
		/*
		* The Monitor() constructor is deleted
		* because we dont want the client to create
		* new monitor objects. All monitors should exist
		* before the actual application starts running.
		*/
		Monitor() = delete;

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

	private:
		/*
		* Private monitor constructor used to create
		* a new unique instance of the connected monitors.
		*/
		explicit Monitor(GLFWmonitor* monitor) noexcept;

	private:
		/*
		* Monitor reference and video mode
		*/
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
	};
}