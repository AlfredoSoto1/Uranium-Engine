#pragma once

namespace Uranium::Core::Application {
	class Application;
}

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	namespace Display = Uranium::Graphics::Display;
	namespace Application = Uranium::Core::Application;

	/*
	* Mouse Callback
	*/
	class MouseCallback {
	public:
		virtual ~MouseCallback();

		bool isButtonDown(int _button);
		int isMouseToggled(int _button);

	private:
		/*
		* Friends with other classes
		*/
		friend Application::Application;
	private:
		/*
		* Private methods
		*/
		MouseCallback() = delete;
		MouseCallback(Display::Window* _window);

	private:
		/*
		* Private members
		*/
		bool* mouseButtons;
	};
}