#include <GL/glew.h>
#include <GL/glfw3.h>

#include "BaseEngine.h"

#include "RenderManager.h"
#include "CallbackManager.h"

#include "Platform/Display/Window.h"

namespace Uranium::Engine {

	BaseEngine::BaseEngine() noexcept :
		display(nullptr),

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
		renderManager = new RenderManager();
		callbackManager = new CallbackManager();
	}

	void BaseEngine::dispose() {
		delete renderManager;
		delete callbackManager;

		delete display.release();
	}

	void BaseEngine::createDisplayContext() {

		display = createWindow();

		glfwMakeContextCurrent(*display);
	}

	void BaseEngine::updateDisplayContext() {
		while (!display->getEvents().shouldClose()) {
			int width, height;
			glfwGetFramebufferSize(*display, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, 0.0, 0.0, 1.0);

			glfwSwapBuffers(*display);

			glfwPollEvents();
		}
	}
}