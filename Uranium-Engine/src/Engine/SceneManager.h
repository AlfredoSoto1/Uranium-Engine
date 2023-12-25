#pragma once

#include <memory>

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

	private:
		std::shared_ptr<Scene::Scene> currentScene;
	};
}