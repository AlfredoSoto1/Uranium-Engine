#pragma once

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Core::Application {
	class Application;
	class ApplicationProgram;
}

namespace Uranium::Input::Callbacks {

	namespace Display = Uranium::Graphics::Display;
	namespace Application = Uranium::Core::Application;

	/*
	* Cursor Callback abstract class
	*/
	class EventCallback {
	public:
		EventCallback(Display::Window* window) : window(window) {}

	protected:
		/*
		* Protected methods
		*/
		void virtual initCallbacks() = 0;
		void virtual updateCallbackEvent() = 0;

		Display::Window* getWindow() { 
			return window; 
		}

	private:
		/*
		* Friends with other classes
		*/
		friend Application::Application;
		friend Application::ApplicationProgram;

	private:
		/*
		* Private members
		*/
		Display::Window* window;

	};
}