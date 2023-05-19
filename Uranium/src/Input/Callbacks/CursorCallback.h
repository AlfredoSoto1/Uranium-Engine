#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Cursor Callback
	*/
	class CursorCallback : public EventCallback {
	public:
		virtual ~CursorCallback();

	protected:
		/*
		* Protected methods
		*/
		void initCallbacks();
		void updateCallbackEvent();

	private:
		/*
		* Mutual friend classes
		*/
		friend Application::Application;
		friend Application::ApplicationProgram;

	private:
		/*
		* Private methods
		*/
		CursorCallback() = delete;
		CursorCallback(Display::Window* window);

	};
}