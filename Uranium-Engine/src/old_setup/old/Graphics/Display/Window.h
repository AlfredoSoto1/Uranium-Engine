#pragma once

struct GLFWwindow;

namespace Uranium::Graphics::Display {

	class WindowSettings;
	class Uranium::Input::WindowListener;
	class Uranium::Core::Application::Application;

	class Window {
	private:
		friend Uranium::Core::Application::Application;
		friend Uranium::Input::WindowListener;

		GLFWwindow* winPtr;

		WindowSettings* settings;
		Uranium::Input::WindowListener* listener;

		bool initGLEW();

		void init();
		void initCallback();
		void dispose();

	public:
		Window(const char* _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();
		void requestAttention();

		void setListener(Uranium::Input::WindowListener* _listener);

		WindowSettings& getSettings();
	};
}

