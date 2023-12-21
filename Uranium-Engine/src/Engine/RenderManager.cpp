#include <GL/glew.h>
#include <GL/glfw3.h>

#include "RenderManager.h"

namespace Uranium::Engine {

	RenderManager::RenderManager() noexcept {

	}

	RenderManager::~RenderManager() {
	}

	/*
	* TODO:
	* This is a temporal method that just renders
	*/
	void RenderManager::render() {
		// check if window has resized
		int width, height;
		glfwGetFramebufferSize(nullptr, &width, &height);
		glViewport(0, 0, width, height);

		// render scene here
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 0.0, 0.0, 1.0);
	}

}