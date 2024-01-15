#pragma once

#include "Core/CoreMacros.h"

struct GLFWmonitor;

namespace Uranium::Input::Callbacks {

	URANIUM_API class MonitorCallback final {
	private:
		/*
		* @brief gets called when a monitor event happens.
		*/
		static void monitor_callback(GLFWmonitor* monitor, int event) noexcept;

	public:
		~MonitorCallback() noexcept = default;

		/*
		* @brief
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		MonitorCallback(MonitorCallback&) = delete;
		MonitorCallback(MonitorCallback&&) = delete;
		MonitorCallback& operator=(const MonitorCallback&) = delete;

	public:
		/*
		* @brief
		* Monitor Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit MonitorCallback() noexcept;
	};
}