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
	* Window Callback
	*/
	class WindowCallback {
	public:
		virtual ~WindowCallback();

		bool hasResized();

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

		Display::Window* window;

	};
}