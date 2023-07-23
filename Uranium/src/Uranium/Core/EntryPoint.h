#pragma once

#ifdef UR_PLATFORM_WINDOWS

// Declare the entry point for the application
namespace Uranium {
	Core::Application* createApplication();
}

// Tell the compiler that there is an implementation of
// the create application function somewhere in the client
// application.
extern Uranium::Core::Application* Uranium::createApplication();

// Create and define entry point for the main
// engine framework.
auto main() -> int {

	// Call the defined in client entry point
	// to launch the application
	auto application = Uranium::createApplication();
	
	// Free all resources allocated by the application
	delete application;
}

#endif
