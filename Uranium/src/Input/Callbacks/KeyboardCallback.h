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
	* Keyboard Callback
	*/
	class KeyboardCallback {
	public:
		virtual ~KeyboardCallback();

		bool isKeyDown(int key);
		bool isKeyToggled(int key);
		bool isKeyReleased(int key);

	private:
		/*
		* Friends with other classes
		*/
		friend Application::Application;

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