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
	* Cursor Callback
	*/
	class CursorCallback {
	public:
		virtual ~CursorCallback();

	private:
		/*
		* Friends with other classes
		*/
		friend Application::Application;

	private:
		/*
		* Private methods
		*/
		CursorCallback() = delete;
		CursorCallback(Display::Window* _window);

	private:
		/*
		* Private members
		*/
	};
}