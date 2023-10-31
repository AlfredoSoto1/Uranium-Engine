export module Uranium.Program.Context;

import <memory>;
import <thread>;

namespace Uranium::Display {
	extern class Window;
}

export namespace Uranium::Program {
	
	class Context {
	public:
		/*
		* Context thread type
		*/
		enum class ThreadType {
			OPENGL_THREAD = 0,
			VIRTUAL_THREAD
		};

	public:
		/*
		* This constructs a context that references
		* a virtual thread where an OpenGL context exists
		*/
		explicit Context(ThreadType type) noexcept;

		virtual ~Context();

		/*
		* Delete the move and copy constructor,
		* because we dont want more instances of
		* a context that must be unique.
		*/
		Context(Context&) = delete;
		Context(Context&&) = delete;
		Context(const Context&) = delete;
		Context(const Context&&) = delete;

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
		bool isExitRequested() const;

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
		* This method gets called every frame
		* inside the defined contex thread.
		* For virtual threads it runs once,
		* but for the OpenGL context this method gets
		* called every frame to update the display
		*/
		virtual void run() = 0;

	private:
		/*
		* Private modifiers
		*/

		/*
		* Starts *this* context in a thread
		*/
		void startContext();

		/*
		* Ends *this* context from virtual thread
		*/
		void endContext();

	private:
		/*
		* Private members
		*/
		ThreadType type;

		volatile mutable bool contextActive;
		volatile mutable bool exitRequested;

		mutable std::thread contextThread;

		std::shared_ptr<Display::Window> currentDisplay;
	};
}