#pragma once

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Input {

	namespace Display = Uranium::Graphics::Display;

	class WindowCallback {
	public:

		bool hasResized();

	private:
		/*
		* Private methods
		*/
		WindowCallback(Display::Window* window);
		virtual ~WindowCallback();

	private:
		/*
		* Mutual friend classes
		*/
		friend Display::Window;

	private:
		/*
		* Private members
		*/
		Display::Window* window;

		bool has_Resized;
	};
}