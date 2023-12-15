
#ifdef UR_DEBUG
#include <iostream>
#endif

#include "Application.h"
#include "Engine/BaseEngine.h"

/*
* Define a custom entry point where
* the application can start without the need of
* a main function. With this the application can handle
* efficiently the lifetime of the Application.
*/
extern std::unique_ptr<Uranium::Core::Engine::BaseEngine> createApplication();

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
		Application::application = new Application();

		// Pass all the arguments from the terminal to the application
		for (int i = 0; i < argc; i++)
			Application::application->addArgument(argv[i]);

		// Set the new base engine
		Application::application->baseEngine = std::move(createApplication());

		try {
			Application::application->init();
		} catch (std::exception& e) {
#ifdef UR_DEBUG
			std::cout << e.what() << std::endl;
#endif
			// Delete the application if fails initiating
			delete Application::application;
			
			// Exit application
			return;
		}
		
		Application::application->run();

		// Delete before exiting the applicaiton
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
	Uranium::Core::buildApplication(argc, argv);

	return 0; // Exit success
}