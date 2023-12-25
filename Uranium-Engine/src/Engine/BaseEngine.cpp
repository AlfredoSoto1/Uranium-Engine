#include <GL/glew.h>
#include <GL/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

#include <GL/glfw3.h>

#include "BaseEngine.h"

#include "SceneManager.h"
#include "RenderManager.h"
#include "ThreadManager.h"
#include "CallbackManager.h"

#include "Platform/Display/Window.h"

namespace Uranium::Engine {

	BaseEngine::BaseEngine() noexcept :
		display(nullptr),
		threadPool(),

		sceneManager(nullptr),
		renderManager(nullptr),
		threadManager(nullptr),
		callbackManager(nullptr)
	{
		
	}

	BaseEngine::~BaseEngine() {
		
	}

	Platform::Display::Window& BaseEngine::getWindow() {
		return *display;
	}

	void BaseEngine::init() {
		sceneManager = new SceneManager();
		renderManager = new RenderManager();
		threadManager = new ThreadManager();
		callbackManager = new CallbackManager();

		// Must be called from access modifier method from base engine abstract object
		threadManager->createThreadPool(1);
	}

	void BaseEngine::dispose() {
		delete sceneManager;
		delete renderManager;
		delete threadManager;
		delete callbackManager;

		display.reset();
	}

	void BaseEngine::createDisplayContext() {

		display = createWindow();

		glfwMakeContextCurrent(*display);

		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW could not initiate correctly!");

		std::cout << glGetString(GL_VERSION) << std::endl;

		glfwSwapInterval(0);
	}

	void BaseEngine::run() {
		while (!display->getEvents().shouldClose()) {
			
			int width, height;
			glfwGetFramebufferSize(*display, &width, &height);
			glViewport(0, 0, width, height);

			renderManager->render();

			glfwPollEvents();
		}
	}

	void BaseEngine::setScene(std::shared_ptr<Scene::Scene> scene) {
		sceneManager->currentScene = scene;
	}
}