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

namespace Uranium::Core {
	
	// Application declaration
	class Application;

	/*
	* EntryPoint class
	*/
	class EntryPoint {
	public:
		// Application ptr
		Application* application;
		
		EntryPoint() {
			// Call the defined in client entry point
			// to launch the application
			application = Uranium::createApplication();
		}
		
		~EntryPoint() {
			// Free all resources allocated by the application
			delete application;
		}

		void start() {
			// Run application
			application->run();
		}
	};
}

// Create and define entry point for the main
// engine framework.
auto main() -> int {

	Uranium::Core::EntryPoint entryPoint;

	entryPoint.start();
}

#endif
