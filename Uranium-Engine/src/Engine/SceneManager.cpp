#include "Scene/Scene.h"
#include "SceneManager.h"

namespace Uranium::Engine {

	SceneManager::SceneManager() noexcept :
		lastTick(0),
		lastMeasuredTick(0),
		elapsedTickingTime(0),
		tickTime(0),
		targetTicks(0),

		isTaskThreadAlive(true),
		isTickingThreadAlive(true)
	{
		//taskThread = std::thread(&SceneManager::executeSceneTasks, this);
		//tickingThread = std::thread(&SceneManager::updateCurrentScene, this);
	}

	SceneManager::~SceneManager() {
		taskThread.join();
		tickingThread.join();
	}

	void SceneManager::executeSceneTasks() {
		while (isTaskThreadAlive) {
		
		}
	}

	void SceneManager::updateCurrentScene() {
		while (isTickingThreadAlive) {

		}
	}

	void SceneManager::handleSceneLoading() {

	}

	void SceneManager::unloadCurrentScene() {

	}
}

