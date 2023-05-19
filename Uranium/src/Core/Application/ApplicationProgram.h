#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Graphics::UI {
	class Cursor;
	class CursorShape;
}

namespace Uranium::Input::Callbacks {
	class WindowCallback;	
	class MouseCallback;	
	class KeyboardCallback;	
	class CursorCallback;	
}

namespace Uranium::Scenes {
	class Scene;
	class SceneMaster;
}

namespace Uranium::Core::Application {

	class Application;

	class ApplicationProgram {
	public:
		/*
		* custom alias
		*/
		using Scene				= Uranium::Scenes::Scene;
		using SceneMaster		= Uranium::Scenes::SceneMaster;
		using Cursor			= Uranium::Graphics::UI::Cursor;
		using CursorShape		= Uranium::Graphics::UI::CursorShape;
		using Window			= Uranium::Graphics::Display::Window;
		using WindowCallback	= Uranium::Input::Callbacks::WindowCallback;
		using MouseCallback		= Uranium::Input::Callbacks::MouseCallback;
		using KeyboardCallback	= Uranium::Input::Callbacks::KeyboardCallback;
		using CursorCallback	= Uranium::Input::Callbacks::CursorCallback;

	public:
		ApplicationProgram();
		virtual ~ApplicationProgram();

	public:
		/*
		* Public methods
		*/
		Cursor* getCursor();
		std::shared_ptr<Window> getWindow();
		
		SceneMaster* getSceneMaster();

		WindowCallback* getWindowCallback();
		CursorCallback* getCursorCallback();
		MouseCallback* getMouseCallback();
		KeyboardCallback* getKeyboardCallback();

	protected:
		/*
		* Pure virtual methods
		*/
		void virtual init() = 0;
		void virtual dispose() = 0;

		void push(std::shared_ptr<Window> window, std::shared_ptr<Scene> scene);

	private:
		/*
		* Friend with other classes
		*/
		friend Window;
		friend Application;

	private:
		/*
		* Private methods
		*/
		bool hasWindow();

		void initMembers();	
		void disposeMembers();

		void updateProgram();

		void pollEvents();

	private:
		/*
		* Private members
		*/
		WindowCallback* windowCallback;	   // 
		CursorCallback* cursorCallback;	   // Primitive callbacks for this
		MouseCallback* mouseCallback;	   // Application-program
		KeyboardCallback* keyboardCallback; // 

		Cursor* cursor;				 
		SceneMaster* sceneMaster;

		std::shared_ptr<Scene> scene;
		std::shared_ptr<Window> window;
	};
}