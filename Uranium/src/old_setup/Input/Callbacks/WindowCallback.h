#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Window Callback
	*/
	class WindowCallback : public EventCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;
		using Application = Uranium::Core::Application::Application;
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

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
		friend Window;
		friend Application;
		friend ApplicationProgram;
	
	private:
		/*
		* Private methods
		*/
		WindowCallback() = delete;
		WindowCallback(const WindowCallback&) = delete;
		WindowCallback(const WindowCallback&&) = delete;

		WindowCallback(std::shared_ptr<Window> window);

	private:
		/*
		* Private members
		*/
		bool has_Resized;

	};
}