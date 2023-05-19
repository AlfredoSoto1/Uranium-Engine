#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Keyboard Callback
	*/
	class KeyboardCallback : public EventCallback {
	public:
		virtual ~KeyboardCallback();

		bool isKeyDown(int key);
		bool isKeyToggled(int key);
		bool isKeyReleased(int key);

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
		KeyboardCallback() = delete;
		KeyboardCallback(Display::Window* _window);

	private:
		/*
		* Private members
		*/
		bool* keys;

		bool toggled;
		bool released;

	};
}