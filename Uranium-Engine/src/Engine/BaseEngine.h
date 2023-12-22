#pragma once

#include <memory>
#include <thread>
#include <vector>

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Scene {
	class Scene;
}

namespace Uranium::Engine {

	class SceneManager;
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

	public:
		Platform::Display::Window& getWindow();

	protected:
		/*
		* Constructor for initialization of the engine
		*/
		explicit BaseEngine() noexcept;
		
	protected:
		/*
		* Initializes and disposes all content
		*/
		virtual void init() = 0;
		virtual void dispose() = 0;

		/*
		* Creates a unique instance of a window that
		* the engine manages throught the life time of the
		* program. In this window is where the scenes will be rendered
		*/
		virtual std::unique_ptr<Platform::Display::Window> createWindow() = 0;

		/*
		* Creates and initializes all scenes
		*/
		virtual void createScenes() = 0;

		/*
		* Prepares the first scene to be rendered/updated
		*/
		void setScene(std::shared_ptr<Scene::Scene> scene);

		void createThreadPool(unsigned int threadPoolCount);

	private:
		void init();
		void dispose();

		void createDisplayContext();
		void updateDisplayContext();

	private:
		std::vector<std::thread> threadPool;

		std::unique_ptr<Platform::Display::Window> display;

		/*
		* Engine managers
		*/
		Engine::SceneManager* sceneManager;
		Engine::RenderManager* renderManager;
		Engine::CallbackManager* callbackManager;
	};
}