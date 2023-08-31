#pragma once

#include <mutex>
#include <thread>
#include <memory>

namespace Uranium::Input::Callbacks {
	/*
	* UI callback delcaration
	*/
	class CursorCallback;    
	class WindowCallback;    
	
	/*
	* Peripheral callback declaration
	*/
	class MouseCallback;    
	class MonitorCallback;   
	class KeyboardCallback;  
}

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Core {

	class Application;

	/*
	* WorkingUnit class
	* 
	* This class creates a WorkingUnit inside a thread
	* from the thread pool of the application. The
	* WorkingUnit created from an instance of this class
	* will be incharged of managing everything related to:
	* 
	* - Window opening/closing and updating
	* - WorkingUnit update workflow
	* - WorkingUnit rendering workflow
	*/
	class UnitProgram {
	public:
		/*
		* Custom alias
		*/
		using Thread = std::thread;
		using Window = Graphics::Display::Window;

		using CursorCallback   = Input::Callbacks::CursorCallback;
		using WindowCallback   = Input::Callbacks::WindowCallback;
		using MouseCallback    = Input::Callbacks::MouseCallback;
		using MonitorCallback  = Input::Callbacks::MonitorCallback;
		using KeyboardCallback = Input::Callbacks::KeyboardCallback;

	public:
		/*
		* 
		*/
		explicit UnitProgram();
		
		virtual ~UnitProgram();
	
	public:
		/*
		* public methods
		*/
		auto getCursorCallback() -> CursorCallback&;
		auto getWindowCallback() -> WindowCallback&;

		auto getMouseCallback()    -> MouseCallback&;
		auto getMonitorCallback()  -> MonitorCallback&;
		auto getKeyboardCallback() -> KeyboardCallback&;
		
	private:
		/*
		* friends with other classes
		*/
		friend Application;

	private:
		/*
		* private methods
		*/

		/*
		* Create/Free all callbacks
		* for this current unit program
		*/
		void initCallbacks();
		void freeCallbacks();

		/*
		* Initiate GLEW for the current context
		*/
		void initGlew();

		void pollEvents();
		void join();
		void update();
		void reserve();

	private:
		/*
		* private members
		*/
		Thread workingUnit;

		std::shared_ptr<Window> window;

		// Display related callbacks
		CursorCallback* cursorCallback;
		WindowCallback* windowCallback;

		// Peripheral related callbacks
		MouseCallback*    mouseCallback;
		MonitorCallback*  monitorCallback;
		KeyboardCallback* keyboardCallback;
	};
}