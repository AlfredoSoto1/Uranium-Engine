#pragma once

#include <memory>
#include <cstdint>
#include <glm/vec2.hpp>

#include "Core/CoreMacros.h"
#include "Input/Events/Event.h"

struct GLFWmonitor;
struct GLFWvidmode;

namespace Uranium::Core {
	UR_DECLARE Application;
}

namespace Uranium::Input::Callbacks {
	UR_DECLARE MonitorCallback;
}

namespace Uranium::Platform::Interface {

	URANIUM_API class Monitor final {
	public:
		using MonitorRef = std::shared_ptr<Monitor>;
		using EventCallbackFn = Input::Events::Event::EventCallbackFn;

		/*
		* If monitor is not connected it will return nullptr.
		*
		* @return primary monitor connected.
		*/
		static MonitorRef getPrimary() noexcept;

		/*
		* If no monitor connected, vector will be empty.
		* First element of the vector is the primary monitor.
		*
		* @return vector containing all the references of the connected monitors.
		*/
		static const std::vector<MonitorRef>& getConnectedMonitors() noexcept;

	public:
		/*
		* @return raw pointer reference to GLFWmonitor
		*/
		operator GLFWmonitor* () const noexcept;

	public:
		bool       isConnected()    const noexcept;
		uint32_t   gerRefreshRate() const noexcept;
		glm::ivec2 getResolution()  const noexcept;

	private:
		friend Core::Application;

		static void init();             // Initiates the monitor attributes
		static void dispose() noexcept; // Frees all the data related to all monitors

		/*
		* @brief Fetches for all available monitors that are connected.
		*
		* @param callback-event
		*
		* @throw runtime_error - no monitor available
		*/
		static void fetchAvailableMonitors(const EventCallbackFn& callbackEvent);

	private:
		/*
		* @brief
		* This constructor used to create
		* a new unique instance of the connected monitors.
		*
		* @param GLFWmonitor reference
		* @param callback event function
		*/
		explicit Monitor(GLFWmonitor* monitor, const EventCallbackFn& callbackEvent) noexcept;
		~Monitor() noexcept = default;

	private:
		friend Input::Callbacks::MonitorCallback;
		
		static std::vector<MonitorRef>* availableMonitors;
		static Input::Callbacks::MonitorCallback* callback;

	private:
		GLFWmonitor*       monitor; // Raw monitor reference
		const GLFWvidmode* vidmode; // Raw video mode from monitor

		EventCallbackFn callbackFunction; // Callback function event
		bool connected;                   // flag to indicate if monitor is connected
	};

}