
#ifdef UR_DEBUG
#include <iostream>
#endif

#include "Services/Application.h"
#include "Services/BaseEngine.h"

/*
* Define a custom entry point where
* the application can start without the need of
* a main function. With this the application can handle
* efficiently the lifetime of the Application.
*/
extern std::unique_ptr<Uranium::Services::BaseEngine> createApplication();

namespace Uranium::Services {
	
	/*
	* Start application function
	* The logic behind this design is for the Application
	* singleton have access to all private members of the
	* Application class members including static functions
	* and declarations.
	*/
	void buildApplication(int argc, char* argv[]) {

		// Create a new application instance
		Application::application = new Application();

		// Pass all the arguments from the terminal to the application
		for (int i = 0; i < argc; i++)
			Application::application->addArgument(argv[i]);

		// Set the new base engine
		Application::application->baseEngine = std::move(createApplication());

		try {
			// Initiate GLFW
			Application::application->init();
		} catch (std::exception& e) {
#ifdef UR_DEBUG
			std::cout << e.what() << std::endl;
#endif
			// Delete the application once the program ends
			delete Application::application;
			
			// exit the application
			return;
		}
		
		// Run the base engine
		Application::application->run();

		// Delete the application once the program ends
		delete Application::application;
	}
}

/*
* Definition of the default main function
*/
auto main(int argc, char* argv[]) -> int {

	/*
	* Start application from global space
	*/
	Uranium::Services::buildApplication(argc, argv);

	return 0; // Exit success
}