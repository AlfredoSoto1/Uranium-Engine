#pragma once

#include <memory>
#include <thread>
#include <functional>

namespace Uranium::Core::Engine {

	class ThreadContext final {
	public:
		friend class BaseEngine;
	
	public:
		/*
		* This constructs a context that references
		* a virtual thread where an OpenGL context exists
		*/
		explicit ThreadContext() noexcept;

		~ThreadContext() = default;

	private:
		/*
		* Starts the thread
		*/
		void start(std::function<void()> run);

		/*
		* Disposes *this* context and frees memory
		*/
		void dispose();

	private:
		std::thread contextThread;
	};
}