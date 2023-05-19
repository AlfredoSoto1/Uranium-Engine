#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Mouse Callback
	*/
	class MouseCallback : public EventCallback {
	public:
		virtual ~MouseCallback();

		bool isButtonDown(int _button);
		int isMouseToggled(int _button);
	
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
		MouseCallback() = delete;
		MouseCallback(Display::Window* window);

	private:
		/*
		* Private members
		*/
		bool* mouseButtons;
	};
}