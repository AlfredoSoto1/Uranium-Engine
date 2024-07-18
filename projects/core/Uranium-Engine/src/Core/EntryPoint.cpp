#include "Application.h"

/*
* Define a custom entry point where
* the application can start without the need of
* a main function. With this the application can handle
* efficiently the lifetime of the Application.
* 
* @return unique application reference
*/
extern std::unique_ptr<Uranium::Core::Application> createApplication();

namespace Uranium::Core {
	
	/*
	* Start application function
	* The logic behind this design is for the Application
	* singleton have access to all private members of the
	* Application class members including static functions
	* and declarations.
	* 
	* @param arguments count
	* @param arguments array
	*/
	void buildApplication(int argc, char* argv[]) {
		// Terminal arguments are here in case we need them in the future mostly for debugging

		// Create a new application instance
		Application::application = createApplication();

		// Starts the application
		Application::application->start();

		// Delete before exiting the applicaiton
		delete Application::application.release();
	}
}

/*
* Definition of the default main function
*/
//auto main(int argc, char* argv[]) -> int {
//
//	/*
//	* Start application from global space
//	*/
//	Uranium::Core::buildApplication(argc, argv);
//
//	return 0; // Exit success
//}
