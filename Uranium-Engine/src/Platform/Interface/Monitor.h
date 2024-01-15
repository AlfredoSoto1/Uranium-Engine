#pragma once

#include <cstdint>
#include <glm/vec2.hpp>

#include "Core/CoreMacros.h"
#include "Input/Events/Event.h"

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Platform::Interface {

	URANIUM_API class Monitor final {
	public:
		~Monitor() noexcept = default;

	public:
		/*
		* @return raw pointer reference to GLFWmonitor
		*/
		operator GLFWmonitor* () const noexcept;

	public:
		/*
		* @return true if the current monitor is connected
		*/
		bool isConnected() const noexcept;

		/*
		* @return refreshrate of the monitor in hz
		*/
		uint32_t gerRefreshRate() const noexcept;

		/*
		* @return resolution of the monitor
		*/
		glm::ivec2 getResolution() const noexcept;

	private:
		/*
		* This constructor used to create
		* a new unique instance of the connected monitors.
		*/
		explicit Monitor(GLFWmonitor* monitor) noexcept;

	private:
		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;

	private:
		using Event = Input::Events::Event;

		Event::EventCallbackFn callbackFunction;
	};

}