#pragma once

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Graphics::UI {
	class Cursor;
	class CursorShape;
}

namespace Uranium::Input::Callbacks {
	class WindowCallback;	   // 
	class MouseCallback;	   // Program Callbacks (interfaces)
	class KeyboardCallback;	   // 
	class CursorCallback;	   // 
}

namespace Uranium::Core::Application {

	namespace UI = Uranium::Graphics::UI;				// 
	namespace Display = Uranium::Graphics::Display;		// Namespace declarations
	namespace Callbacks = Uranium::Input::Callbacks;	// 

	class Application;

	class ApplicationProgram {
	public:
		ApplicationProgram();
		virtual ~ApplicationProgram();

	public:
		/*
		* Public methods
		*/
		UI::Cursor* getCursor();
		Display::Window* getWindow();

		Callbacks::WindowCallback* getWindowCallback();
		Callbacks::CursorCallback* getCursorCallback();
		Callbacks::MouseCallback* getMouseCallback();
		Callbacks::KeyboardCallback* getKeyboardCallback();

	protected:
		/*
		* Pure virtual methods
		*/
		void virtual init() = 0;
		void virtual dispose() = 0;

		void setWindow(Display::Window* window);

	private:
		/*
		* Friend with other classes
		*/
		friend Application;
		friend Display::Window;

	private:
		/*
		* Private methods
		*/
		bool hasWindow();

		void createCallbacks();	
		void disposeCallbacks();

		void updateProgram();

	private:
		/*
		* Private members
		*/
		Callbacks::WindowCallback* windowCallback;	   // 
		Callbacks::CursorCallback* cursorCallback;	   // Primitive callbacks for this
		Callbacks::MouseCallback* mouseCallback;	   // Application-program
		Callbacks::KeyboardCallback* keyboardCallback; // 

		UI::Cursor* cursor;				 
		Display::Window* window;		 
	};
}