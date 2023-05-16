#pragma once

#include <memory>
#include <string>

struct GLFWwindow;

namespace Uranium::Input {
	class WindowCallback;
}

namespace Uranium::Graphics::Display {

	namespace Input = Uranium::Input;

	class Monitor;
	class WindowProps;

	class Window {
	public:
		Window(const std::string& title, unsigned int width, unsigned int height);
		virtual ~Window();

		void setMonitor(std::shared_ptr<Monitor> monitor);
		
		operator GLFWwindow* ();
		
		WindowProps& getProperties();
		
		std::shared_ptr<Monitor> getMonitor();
		
		bool init();
		void exit(int errorCode);
		void close();
		void dispose();
		void run();
		
		void focus();
		void restore();
		void maximize();
		void minimize();
		void requestAttention();
		void centerWindow();

		// set fullscreen with a resolution
		void fullscreen(unsigned int width, unsigned int height);
		
	private:
		/*
		* Private methods
		*/
		void prepareWindowHints();
		void prepareWindowGLVersion();

		void prepareContextHints();

		void createWindow();

	private:
		/*
		* Private members
		*/
		GLFWwindow* window;

		WindowProps* windowProps;
		Input::WindowCallback* callback;

		std::shared_ptr<Monitor> monitor;
	};
}