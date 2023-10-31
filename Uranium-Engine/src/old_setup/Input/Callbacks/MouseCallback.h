#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Mouse Callback
	*/
	class MouseCallback : public EventCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;
		using Application = Uranium::Core::Application::Application;
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

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
		friend Application;
		friend ApplicationProgram;

	private:
		/*
		* Private methods
		*/
		MouseCallback() = delete;
		MouseCallback(const MouseCallback&) = delete;
		MouseCallback(const MouseCallback&&) = delete;
		
		MouseCallback(std::shared_ptr<Window> window);

	private:
		/*
		* Private members
		*/
		bool* mouseButtons;
	};
}