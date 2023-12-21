#pragma once

#include <memory>
#include <vector>

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Engine {

	class RenderManager;
	class CallbackManager;

	class BaseEngine {
	public:
		friend Core::Application;

	public:
		virtual ~BaseEngine();

		/*
		* Delete the move/copy constructors. 
		* This is because there must be one instance of
		* the base engine throught the lifetime of the program
		*/
		BaseEngine(BaseEngine&) = delete;
		BaseEngine& operator=(const BaseEngine&) = delete;

	protected:
		/*
		* Constructor for initialization of the engine
		*/
		explicit BaseEngine() noexcept;
		
	protected:
		Platform::Display::Window& getWindow();

		/*
		* Creates a unique instance of a window that
		* the engine manages throught the life time of the
		* program. In this window is where the scenes will be rendered
		*/
		virtual std::unique_ptr<Platform::Display::Window> createWindow() = 0;

	private:
		void init();
		void dispose();

		void createDisplayContext();
		void updateDisplayContext();

	private:
		std::unique_ptr<Platform::Display::Window> display;

		/*
		* Engine managers
		*/
		Engine::RenderManager* renderManager;
		Engine::CallbackManager* callbackManager;
	};
}