#pragma once

#include <memory>
#include <thread>
#include <vector>

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Scene {
	class Scene;
}

namespace Uranium::States {
	class State;
}

namespace Uranium::Engine {

	class StateManager;
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
		/*
		* Returns the primary scene
		*/
		Scene::Scene& getPrimaryScene();

	protected:
		/*
		* Constructor for initialization of the engine
		*/
		explicit BaseEngine() noexcept;
		
	protected:
		/*
		* Creates and initializes all scenes
		*/
		virtual std::shared_ptr<Scene::Scene> createScenes() = 0;

	private:
		/*
		* Initializes the base engine controlled by the application
		*/
		void init();

		/*
		* Disposes the initialized content
		*/
		void dispose();

		/*
		* Starts the engine after initialization
		*/
		void start();

	private:
		void initializeManagers();
		void disposeManagers();

	private:
		/*
		* Engine managers
		*/
		Engine::StateManager* stateManager;
		Engine::SceneManager* sceneManager;
		Engine::RenderManager* renderManager;
		Engine::CallbackManager* callbackManager;
	};
}