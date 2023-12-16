#pragma once

#include <memory>
#include <thread>

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Scene {
	class SceneManager;
}

namespace Uranium::Platform::Display {
	class WindowManager;
}

namespace Uranium::Input::Callbacks {
	class WindowCallback;
	class MonitorCallback;
	class MouseCallback;
	class CursorCallback;
	class KeyboardCallback;
}

namespace Uranium::Core::Engine {

	class BaseEngine {
	public:
		friend Core::Application;

		using SceneManager = Scene::SceneManager;
		using WindowManager = Platform::Display::WindowManager;

		using MouseCallback = Input::Callbacks::MouseCallback;
		using CursorCallback = Input::Callbacks::CursorCallback;
		using WindowCallback = Input::Callbacks::WindowCallback;
		using MonitorCallback = Input::Callbacks::MonitorCallback;
		using KeyboardCallback = Input::Callbacks::KeyboardCallback;

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
		* Base engine working unit
		*/
		//std::unique_ptr<class WorkingUnit> workingUnit;

		/*
		* Engine Managers
		*/
		//std::unique_ptr<SceneManager> sceneManager;
		//std::unique_ptr<WindowManager> windowManager;

		/*
		* Engine callbacks
		*/
		MouseCallback*    mouseCallback;
		CursorCallback*   cursorCallback;
		WindowCallback*   windowCallback;
		MonitorCallback*  monitorCallback;
		KeyboardCallback* keyboardCallback;
	};
}