export module Uranium.Program.Context;

import <memory>;
import <thread>;

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

		/*
		* Sets a display for the current
		* context created. This only works when
		* *this* context is created with a ThreadType
		* of OpenGL support.
		*/
		void setDisplay();

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
	};
}