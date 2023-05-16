#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include "AppProgram.h"
#include "Application.h"
#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowSettings.h"
#include "Scenes/Scene.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"

using namespace Uranium::Input;
using namespace Uranium::Core::Application;
using namespace Uranium::Graphics::Display;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

Application* Application::application;

Application& Application::get() {
	return *application;
}

void Application::start(AppProgram* _appProgram) {
	if (_appProgram == nullptr) {
		std::cerr << "No AppProgram defined for Application context." << std::endl;
		return;
	}
	// create Application
	Application::application = new Application(_appProgram);
	// run application
	Application::get().run();
	// end aplication
	delete Application::application;
}

// Create Application
Application::Application(AppProgram* _appProgram) 
	: appProgram(_appProgram), isRunning(false)
{
	mouse = nullptr;
	window = nullptr;
	// Initiates GLFW
	if (!glfwInit()) {
		isRunning = false;
		std::cerr << "GLFW couldn't initiated correctly." << std::endl;
		return;
	}
	// set default GLFW error callback
	glfwSetErrorCallback(&error_callback);

	isRunning = true;
}

// End Application
Application::~Application() {
	if (!isRunning)
		return;
	isRunning = false;

	delete mouse;
	delete keyboard;
	delete window;
	delete appProgram;

	glfwTerminate();
}

// Run Application
void Application::run() {
	
	// initiates the application content
	window = new Window("Default", 1280, 720);
	window->init();

	glfwSetWindowUserPointer(getWindow(), this);

	// init external devices
	mouse = new Mouse(window);
	keyboard = new Keyboard(window);
	
	// init application program
	appProgram->init();

	while (!glfwWindowShouldClose(*window)) {
		// update
		appProgram->update();
		// reset viewport
		if (window->getSettings().hasResized()) {
			glViewport(0, 0, window->getSettings().getWidth(), window->getSettings().getHeight());
		}

		// draw
		appProgram->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(*window);

		// post draw
		window->getSettings().hasResized() = false;
		appProgram->afterDraw();

		// poll events
		glfwPollEvents();

		mouse->update();
		keyboard->update();
	}
	// closes the application
	appProgram->dispose();

	// disposes everything after application has ended
	window->dispose();
}

Window& Application::getWindow() {
	return *window;
}

Mouse& Application::getMouse() {
	return *mouse;
}

Keyboard& Application::getKeyboard() {
	return *keyboard;
}

