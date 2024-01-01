#include <GL/glew.h>
#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include "BaseEngine.h"

#include "StateManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ThreadManager.h"

namespace Uranium::Engine {

	BaseEngine::BaseEngine() noexcept :
		stateManager(nullptr),
		sceneManager(nullptr),
		renderManager(nullptr),
		callbackManager(nullptr)
	{
		
	}

	BaseEngine::~BaseEngine() {
		
	}

	Scene::Scene& BaseEngine::getPrimaryScene() {
		return *sceneManager->primaryScene;
	}

	void BaseEngine::init() {

		initializeManagers();
	}

	void BaseEngine::dispose() {
		disposeManagers();
	}

	void BaseEngine::initializeManagers() {
		stateManager = new StateManager();
		sceneManager = new SceneManager();
		renderManager = new RenderManager();
	}

	void BaseEngine::disposeManagers() {
		delete stateManager;
		delete sceneManager;
		delete renderManager;
		delete callbackManager;
	}

	void BaseEngine::start() {

		//int width, height;
		//glfwGetFramebufferSize(*display, &width, &height);
		//glViewport(0, 0, width, height);

		//renderManager->render();

		//glfwPollEvents();
	}
}