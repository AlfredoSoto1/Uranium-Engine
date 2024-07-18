#pragma once

#include <memory>
#include <thread>

namespace Uranium::Scene {
	class Scene;
}

namespace Uranium::Engine {

	class SceneManager final {
	public:
		friend class BaseEngine;

	public:
		~SceneManager();

		/*
		* Delete the copy/move constructor since
		* there must be one scene manager instance
		* recognized by the engine
		*/
		SceneManager(SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

	private:
		/*
		* Creates center crontrol that manages
		* all scenes in our Application program
		*/
		explicit SceneManager() noexcept;
		
	private:
		/*
		* This gets in charge of loading and
		* unloading a scene in memory
		*/
		void handleSceneLoading();

		/*
		* This method gets called when program 
		* has ended. The reason is to free resources
		* from last scene before closing program
		*/
		void unloadCurrentScene();

		/*
		* This executes all tasks that the current scene has
		*/
		void executeSceneTasks();

		/*
		* Updates the current scene in the appropiate thread
		*/
		void updateCurrentScene();

	private:
		double lastTick;
		double lastMeasuredTick;
		double elapsedTickingTime;

		unsigned int tickTime;
		unsigned int targetTicks;

		volatile bool isTaskThreadAlive;
		volatile bool isTickingThreadAlive;

		std::thread taskThread;
		std::thread tickingThread;

		std::shared_ptr<Scene::Scene> primaryScene;
		std::shared_ptr<Scene::Scene> currentScene;
	};
}