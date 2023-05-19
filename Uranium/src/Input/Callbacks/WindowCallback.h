#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Window Callback
	*/
	class WindowCallback : public EventCallback {
	public:
		virtual ~WindowCallback();

		bool hasResized();

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
		friend Display::Window;
		friend Application::Application;
		friend Application::ApplicationProgram;
	
	private:
		/*
		* Private methods
		*/
		WindowCallback() = delete;
		WindowCallback(Display::Window* window);

	private:
		/*
		* Private members
		*/
		bool has_Resized;

	};
}