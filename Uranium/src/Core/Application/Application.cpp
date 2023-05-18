#include <GLFW/glfw3.h>

#include "UraniumApi.h"
#include "Application.h"
#include "Graphics/Display/Window.h"

using namespace Uranium::Core::Application;
using namespace Uranium::Graphics::Display;

Application* Application::appSingleton;

Application* Application::get() {
	return appSingleton;
}

void Application::start(std::shared_ptr<ApplicationProgram> program) {
	// create application
	Application::appSingleton = new Application(program);
	
	Application::appSingleton->run();

	// destroy application
	delete Application::appSingleton;
}

Application::Application(std::shared_ptr<ApplicationProgram> program) :
	program(program),
	hasInitiated(false),
	isRunning(false)
{

}

void Application::error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

bool Application::isProgramRunnning() {
	return isRunning;
}

bool Application::hasProgramInitiated() {
	return hasInitiated;
}

void Application::run() {

	// Initiate GLFW Library
	if (!glfwInit()) {
		std::cerr << "Failed to initiate GLFW" << std::endl;
		hasInitiated = false;
		return;
	}

	// set default GLFW error callback
	glfwSetErrorCallback(&Application::error_callback);

	// set initiated flag to true if no error has happened
	hasInitiated = true;

	// Running flag maintain false until loop
	isRunning = false;

	// initialize program in GLFW
	program->init();

	// this is for JUST ONE WINDOW
	// to handle more windows, this WOULD BE DIFFERENT
	// in other words, this implementation is TEMPORARELY
	if (program->hasWindow()) {
		// 
		// after checking a window exists in current
		// program, we can initialize the rest that
		// lives inside the program that depends on
		// the existance of a window context 
		// 

		program->createComponents();
		program->createCallbacks();

		// set isRunning flag to true
		isRunning = true;

		// update window here
		program->updateProgram();

		// set isRunning flag to false
		isRunning = false;
	}

	// dispose program in GLFW
	program->dispose();

	// Terminate GLFW Library
	glfwTerminate();

	// set isRunning flag to false since Application has ended
	isRunning = false;
}
