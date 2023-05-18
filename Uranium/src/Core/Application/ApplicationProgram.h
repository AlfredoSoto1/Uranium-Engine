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
		

	protected:
		/*
		* Pure virtual methods
		*/
		void virtual init() = 0;
		void virtual dispose() = 0;

		void setWindow(Display::Window* window);

	protected:
		/*
		* Protected Getters
		*/
		UI::Cursor* getCursor();
		Display::Window* getWindow();

		Callbacks::WindowCallback* getWindowCallback();
		Callbacks::CursorCallback* getCursorCallback();
		Callbacks::MouseCallback* getMouseCallback();
		Callbacks::KeyboardCallback* getKeyboardCallback();

	private:
		/*
		* Friend with other classes
		*/
		friend Application;

	private:
		/*
		* Private methods
		*/
		ApplicationProgram();
		virtual ~ApplicationProgram();

		bool hasWindow();

		void createCallbacks();	   // 
		void createComponents();   // Creation and disposal of
								   // Callbacks and Components
		void disposeCallbacks();   // inside 'this' Application-program
		void disposeComponents();  // 

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