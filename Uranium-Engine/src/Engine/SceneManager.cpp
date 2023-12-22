#include <GL/glew.h>
#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include "BaseEngine.h"
#include "Core/Application.h"
#include "Platform/Display/Window.h"

#include "Scene/Scene.h"
#include "SceneManager.h"

namespace Uranium::Engine {

	SceneManager::SceneManager() noexcept:
		frameCount(0),
		tickCount(0),
		lastFrame(0),
		lastTick(0),
		elapsedRenderTime(0),
		elapsedTickTime(0),

		lastMeasuredFrame(0),
		lastMeasuredTick(0)
	{

	}

	SceneManager::~SceneManager() {
	
	}

	void SceneManager::render() {
		// if no scene is linked, 
		// skip any process
		if (currentScene == nullptr)
			return;

		// Calculate the elapsed framerate to
		// control the time it takes for a frame to render
		double currentFrame = glfwGetTime() * 1000.0;
		double elapsedTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		elapsedRenderTime += elapsedTime;

		// check if it's time to render
		if (currentScene->getTargetFramerate() * elapsedRenderTime < 1000.0)
			return;
			
		// Render the current scene	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glfwSwapBuffers(Core::Application::instance().getBaseEngine().getWindow());

		currentScene->render();

		// reset rendering timer
		elapsedRenderTime = 0.0;

		if (!currentScene->measureFramerate)
			return;

		// Increase the frame count
		frameCount++;

		if (glfwGetTime() * 1000.0 < lastMeasuredFrame + 1000.0)
			return;

#ifdef UR_DEBUG
		std::cout << "FPS: " << frameCount << std::endl;
#endif // UR_DEBUG
			
		// Display framerate HERE

		frameCount = 0;
		// set last time refreshed to ~new time
		lastMeasuredFrame = glfwGetTime() * 1000.0;
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
		//if (currentScene->hasNoTickingLimit()) {
		//	updateOutTime();
		//}
		//else {
		//	updateInTime();
		//}
	}

	void SceneManager::handleSceneLoading() {

		// check if it needs to change to next scene
		if (currentScene->nextScene != nullptr) {
			// copy next scene ref
			std::shared_ptr<Scene::Scene> next = currentScene->nextScene;
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

	void SceneManager::unloadCurrentScene() {
		// unlink from any posible next scene
		currentScene->nextScene = nullptr;
		// unload the scene content
		currentScene->unload();
		// update flag
		//currentScene->is_loaded = false;
	}
}

