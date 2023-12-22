#include <GL/glew.h>
#include <GL/glfw3.h>

#include "BaseEngine.h"

#include "SceneManager.h"
#include "RenderManager.h"
#include "CallbackManager.h"

#include "Platform/Display/Window.h"

namespace Uranium::Engine {

	BaseEngine::BaseEngine() noexcept :
		display(nullptr),
		threadPool(),

		sceneManager(nullptr),
		renderManager(nullptr),
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
		callbackManager = new CallbackManager();
	}

	void BaseEngine::dispose() {
		delete sceneManager;
		
		delete renderManager;
		delete callbackManager;

		delete display.release();
	}

	void BaseEngine::createDisplayContext() {

		display = createWindow();

		glfwMakeContextCurrent(*display);

		glfwSwapInterval(0);
	}

	void BaseEngine::updateDisplayContext() {
		while (!display->getEvents().shouldClose()) {
			
			int width, height;
			glfwGetFramebufferSize(*display, &width, &height);
			glViewport(0, 0, width, height);

			sceneManager->render();

			glfwPollEvents();
		}
	}

	void BaseEngine::setScene(std::shared_ptr<Scene::Scene> scene) {
		sceneManager->currentScene = scene;
	}
}