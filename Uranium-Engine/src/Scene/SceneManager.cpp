#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include "Scene.h"
#include "SceneManager.h"

namespace Uranium::Scene {

	SceneManager::SceneManager() noexcept:
		frameCount(0),
		updateCount(0),
		lastFrame(0),
		lastUpdate(0),
		renderTimer(0),
		updateTimer(0)
	{

	}

	SceneManager::~SceneManager() {
	
	}

	void SceneManager::renderOutTime() {
		// perform render logic instantly
		currentScene->render();
	
	#ifdef UR_DEBUG
		// increase udpate count
		frameCount++;
		// display framerate
		if (glfwGetTime() * 1000.0 > lastFrame + 1000.0) {
			std::cout << "FPS: " << frameCount << std::endl;

			frameCount = 0;
			// set last time refreshed to ~new time
			lastFrame = glfwGetTime() * 1000.0;
		}
	#endif // UR_DEBUG
	}

	void SceneManager::renderInTime() {
		// calculate elapse time
		double currentFrame = glfwGetTime();
		double elapsedTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// update render timer
		renderTimer += elapsedTime;

		// check if it's time to render
		if (renderTimer >= currentScene->getFrameTime()) {
			// perform rendering logic in time
			currentScene->render();
			// reset rendering timer
			renderTimer = 0.0;

	#ifdef UR_DEBUG
			// Display framerate
			++frameCount;
			if (frameCount == currentScene->getTargetFramerate()) {
				std::cout << "FPS: " << frameCount << std::endl;
				frameCount = 0;
			}
	#endif // UR_DEBUG
		}
	}

	void SceneManager::render() {

		// if no scene is linked, 
		// skip any process
		if (currentScene == nullptr)
			return;
	
		// check if the target framerate
		// must be done instantly
		if (currentScene->getTargetFramerate() == 0) {
			renderOutTime();
		}
		else {
			renderInTime();
		}
	}

	void SceneManager::handleSceneLoading() {

		// check if it needs to change to next scene
		if (currentScene->nextScene != nullptr) {
			// copy next scene ref
			std::shared_ptr<Scene> next = currentScene->nextScene;
			// reset the pointer from current
			// of next
			currentScene->nextScene = nullptr;
			// unload the scene content
			currentScene->unload();
			// update flag
			//currentScene->is_loaded = false;

			// change scene
			currentScene = next;
		}

		// check if it needs to load the scene
		//if (!currentScene->is_loaded) {
		//	// load new current scene
		//	currentScene->load();
		//	// update flag
		//	currentScene->is_loaded = true;
		//}
	}

	void SceneManager::updateInTime() {
		// calculate elapse time
		double currentUpdate = glfwGetTime();
		double elapsedTime = currentUpdate - lastUpdate;
		lastUpdate = currentUpdate;

		// update udpate timer
		updateTimer += elapsedTime;

		// check if it's time to update
		if (updateTimer >= currentScene->getUpdateTime()) {

			// perform update logic in time
			currentScene->update();

			// reset udpate timer
			updateTimer = 0.0;

			// increase udpate count
			++updateCount;

			// display updates
			if (updateCount == currentScene->getTargetUpdates()) {
				std::cout << "TPS : " << updateCount << std::endl;
				updateCount = 0;
			}
		}
	}

	void SceneManager::updateOutTime() {
		// perform update logic instantly
		currentScene->update();

		// increase udpate count
		updateCount++;

		// display updates
		if (glfwGetTime() * 1000.0 > lastUpdate + 1000.0) {
			std::cout << "TPS : " << updateCount << std::endl;
			updateCount = 0;
			// set last time refreshed to ~new time
			lastUpdate = glfwGetTime() * 1000.0;
		}
	}

	void SceneManager::update() {

		// if no scene is linked, 
		// skip any process
		if (currentScene == nullptr)
			return;

		// handle scene loading
		// when changing is requested
		handleSceneLoading();

		// check if the target updates
		// must be done instantly
		if (currentScene->getTargetUpdates() == 0) {
			updateOutTime();
		}
		else {
			updateInTime();
		}
	}

	void SceneManager::unloadCurrentScene() {
		// unlink from any posible next scene
		currentScene->nextScene = nullptr;
		// unload the scene content
		currentScene->unload();
		// update flag
		//currentScene->is_loaded = false;
	}
}

