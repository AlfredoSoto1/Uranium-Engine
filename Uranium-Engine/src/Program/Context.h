#pragma once

#include <memory>
#include <thread>

namespace Uranium::Display {
	extern class Window;
}

namespace Uranium::Program {
	
	class Context {
	public:
		/*
		* This constructs a context that references
		* a virtual thread where an OpenGL context exists
		*/
		explicit Context() noexcept;

		virtual ~Context();

		/*
		* Delete the copy constructor,
		* because we dont want more instances of
		* a context that must be unique.
		*/
		Context(Context&) = delete;
		Context(const Context&) = delete;

	private:
		/*
		* Friend with other classes
		*/
		friend extern class Application;

	public:
		/*
		* Getters and Setters
		*/
		bool isActive() const;
		bool exitRequested() const;

	public:
		/*
		* Public modifiers
		*/
		void exit() const;

	protected:
		/*
		* Protected modifiers
		*/

		/*
		* Creates a window inside the context.
		* If the function returns nullptr, then
		* no window will be created inside this context
		* making it behave like a regular thread.
		*/
		//virtual std::shared_ptr<Display::Window> createWindow();

	private:
		/*
		* Private modifiers
		*/

		/*
		* Starts *this* context in a thread
		*/
		void start();

		/*
		* Ends *this* context from virtual thread
		*/
		void end();

	private:
		/*
		* Private members
		*/
		volatile mutable bool contextActive;
		volatile mutable bool hasExitRequested;

		mutable std::thread contextThread;

		std::shared_ptr<Display::Window> display;
	};
}