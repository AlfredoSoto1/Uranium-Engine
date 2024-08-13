#pragma once

#include "core/URAPI.h"

struct GLFWmonitor;

namespace uranium::io::callbacks {

	URANIUM_API class MonitorCallback final {
	public:
		explicit MonitorCallback() noexcept;
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

	private:
		/*
		* @brief 
		* Gets called when a monitor event happens.
		*/
		static void monitor_callback(GLFWmonitor* monitor, int event) noexcept;
	};
}