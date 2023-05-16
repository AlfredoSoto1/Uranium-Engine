#include "Application.h"

using namespace Uranium::Core::Application;

Application* Application::mainApplication;

void Application::start(std::shared_ptr<ApplicationProgram> program) {
	// create application
	Application::mainApplication = new Application(program);
	// run application
	Application::mainApplication->run();
	// destroy application
	delete Application::mainApplication;
}

Application::Application(std::shared_ptr<ApplicationProgram> program) :
	program(program)
{

}

void Application::run() {

}