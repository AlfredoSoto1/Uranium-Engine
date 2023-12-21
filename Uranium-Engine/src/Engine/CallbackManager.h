#pragma once

namespace Uranium::Input::Callbacks {
	class WindowCallback;
	class MonitorCallback;
	class MouseCallback;
	class CursorCallback;
	class KeyboardCallback;
}

namespace Uranium::Engine {

	class CallbackManager final {
	public:
		friend class BaseEngine;

	public:
		~CallbackManager();

		/*
		* Delete the copy/move constructors
		* we just need one render manager instance inside the engine
		*/
		CallbackManager(CallbackManager&) = delete;
		CallbackManager(CallbackManager&&) = delete;
		CallbackManager& operator=(const CallbackManager&) = delete;

	private:
		/*
		* Creates and controls all the callbacks of the application
		*/
		explicit CallbackManager() noexcept;

	private:
		using WindowCallback   = Input::Callbacks::WindowCallback;
		using MonitorCallback  = Input::Callbacks::MonitorCallback;
		using MouseCallback    = Input::Callbacks::MouseCallback;
		using CursorCallback   = Input::Callbacks::CursorCallback;
		using KeyboardCallback = Input::Callbacks::KeyboardCallback;

		WindowCallback*   windowCallback;
		MonitorCallback*  monitorCallback;
		MouseCallback*    mouseCallback;
		CursorCallback*   cursorCallback;
		KeyboardCallback* keyboardCallback;
	};
}