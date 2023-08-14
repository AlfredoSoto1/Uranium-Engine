#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Keyboard Callback
	*/
	class KeyboardCallback : public EventCallback {
	public:
		/*
		* Custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;
		using Application = Uranium::Core::Application::Application;
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

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
		friend Application;
		friend ApplicationProgram;

	private:
		/*
		* Private methods
		*/
		KeyboardCallback() = delete;
		KeyboardCallback(const KeyboardCallback&) = delete;
		KeyboardCallback(const KeyboardCallback&&) = delete;
		
		KeyboardCallback(std::shared_ptr<Window> window);

	private:
		/*
		* Private members
		*/
		bool* keys;

		bool toggled;
		bool released;

	};
}