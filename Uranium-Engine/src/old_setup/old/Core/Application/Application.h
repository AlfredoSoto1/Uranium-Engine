#pragma once

namespace Uranium::Core::Application {
	
	namespace UApp = Uranium::Core::Application;
	namespace USenes = Uranium::Scenes;
	namespace UInput = Uranium::Input;
	namespace UDisplay = Uranium::Graphics::Display;

	class UApp::AppProgram;

	class UInput::Mouse;
	class UInput::Keyboard;
	class UDisplay::Window;

	class Application {
	private:
		friend UApp::AppProgram;
		friend UInput::Mouse;
		friend UInput::Keyboard;
		friend UDisplay::Window;

		static Application* application;

		AppProgram* appProgram;

		UInput::Mouse* mouse;
		UInput::Keyboard* keyboard;
		UDisplay::Window * window;

		bool isRunning;

		Application(AppProgram* _appProgram);
		virtual ~Application();

		void run();

	public:
		static Application& get();
		static void start(AppProgram* _appProgram);
		
		Application(const Application&) = delete;
		Application(const Application&&) = delete;

		UInput::Mouse& getMouse();
		UInput::Keyboard& getKeyboard();
		UDisplay::Window& getWindow();
	};
}