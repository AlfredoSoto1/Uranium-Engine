#ifdef UR_DEBUG
#include <iostream>
#endif

#include "Application.h"

/*
* Define a custom entry point where
* the application can start without the need of
* a main function. With this the application can handle
* efficiently the lifetime of the Application.
*/
extern std::unique_ptr<Uranium::Core::Application> createApplication();

namespace Uranium::Core {
	
	/*
	* Start application function
	* The logic behind this design is for the Application
	* singleton have access to all private members of the
	* Application class members including static functions
	* and declarations.
	*/
	void buildApplication(int argc, char* argv[]) {

		// Create a new application instance
		Application::application = createApplication();

		// Pass all the arguments from the terminal to the application
		for (int i = 0; i < argc; i++)
			Application::application->terminalArguments.push_back(argv[i]);

		// Starts the application
		Application::application->start();

		// Delete before exiting the applicaiton
		delete Application::application.release();
	}
}

/*
* Definition of the default main function
*/
auto main(int argc, char* argv[]) -> int {

	/*
	* Start application from global space
	*/
	Uranium::Core::buildApplication(argc, argv);

	return 0; // Exit success
}