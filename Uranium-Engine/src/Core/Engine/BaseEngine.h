#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <functional>

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Scene {
	class SceneManager;
}

namespace Uranium::Platform::Display {
	class Window;
	class WindowManager;
}

namespace Uranium::Input::Callbacks {
	class CallbackManager;
}

namespace Uranium::Core::Engine {

	class ThreadContext;

	class BaseEngine {
	public:
		friend Core::Application;

	public:
		/*
		* Constructor for initialization of the engine
		*/
		explicit BaseEngine() noexcept;

		virtual ~BaseEngine();

		/*
		* Delete the copy constructor,
		* because it doesn't make sense to
		* have more instances of a base engine.
		*/
		BaseEngine(BaseEngine&) = delete;
		BaseEngine(const BaseEngine&) = delete;

	private:
		/*
		* Runs the engine
		*/
		void run();

		void initManagers();
		void disposeManagers();

	private:
		/*
		* Engine Threads
		*/
		std::vector<ThreadContext> renderThreads;
		std::vector<ThreadContext> updateThreads;

		std::vector<std::shared_ptr<Platform::Display::Window>> windows;

		/*
		* Engine Managers
		*/
		Platform::Display::WindowManager* windowManager;
		Input::Callbacks::CallbackManager* callbackManager;
	};
}