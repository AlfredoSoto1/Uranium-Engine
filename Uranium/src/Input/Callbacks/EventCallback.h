#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Core::Application {
	class Application;
	class ApplicationProgram;
}

namespace Uranium::Input::Callbacks {

	/*
	* Cursor Callback abstract class
	*/
	class EventCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;
		using Application = Uranium::Core::Application::Application;
		using ApplicationProgram = Uranium::Core::Application::ApplicationProgram;

	public:
		EventCallback(std::shared_ptr<Window> window) : window(window) {}

	protected:
		/*
		* Protected methods
		*/
		void virtual initCallbacks() = 0;
		void virtual updateCallbackEvent() = 0;

		inline std::shared_ptr<Window> getWindow() {
			return window; 
		}

	private:
		/*
		* Friends with other classes
		*/
		friend Application;
		friend ApplicationProgram;

	private:
		/*
		* Private members
		*/
		std::shared_ptr<Window> window;

	};
}