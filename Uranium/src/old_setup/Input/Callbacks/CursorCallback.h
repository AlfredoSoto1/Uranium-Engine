#pragma once

#include "EventCallback.h"

namespace Uranium::Input::Callbacks {

	/*
	* Cursor Callback
	*/
	class CursorCallback : public EventCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;
		using Application = Uranium::Core::Application::Application;
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

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
		friend Application;
		friend ApplicationProgram;

	private:
		/*
		* Private methods
		*/
		CursorCallback() = delete;
		CursorCallback(const CursorCallback&) = delete;
		CursorCallback(const CursorCallback&&) = delete;

		CursorCallback(std::shared_ptr<Window> window);

	};
}