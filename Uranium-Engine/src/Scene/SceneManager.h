#pragma once

#include <memory>

namespace Uranium::Scene {

	class Scene;

	class SceneManager final {
	private:
		/*
		* Creates center crontrol that manages
		* all scenes in our Application program
		*/
		explicit SceneManager() noexcept;

		~SceneManager();
		
	private:
		/*
		* handles render and update of current scene
		*/
		void render();
		void update();

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
		* These manages the rendering of
		* the current scene synchronized
		*/
		void renderInTime();
		void renderOutTime();

		void updateInTime();
		void updateOutTime();

	private:
		volatile unsigned int frameCount;
		volatile unsigned int updateCount;

		volatile double lastFrame;
		volatile double lastUpdate;

		volatile double renderTimer;
		volatile double updateTimer;

		std::shared_ptr<Scene> currentScene;
	};
}