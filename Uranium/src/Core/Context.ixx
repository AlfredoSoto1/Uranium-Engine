#pragma once 

export module Uranium.Core.Context;

import <memory>;
import <thread>;

namespace Uranium::Core {
	
	class Context {
	public:
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
		void endContext() const;

	private:
		/*
		* Private modifiers
		*/
		void startContext();

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