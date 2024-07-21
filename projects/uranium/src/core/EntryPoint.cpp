#include "Application.h"

/*
* @brief
* Define a custom entry point where the application can 
* start without the need of a main function. With this 
* the application can handle efficiently the lifetime 
* of the Application.
* 
* @return unique application reference
*/
extern std::unique_ptr<uranium::core::Application> createApplication();

namespace uranium::core {
	
	/*
	* @brief
	* Start application function
	* The logic behind this design is for the Application
	* singleton have access to all private members of the
	* Application class members including static functions
	* and declarations.
	*/
	void buildApplication() {
		std::unique_ptr<Application> application = createApplication();

		// Starts the application
		//Application::application->start();

		// Delete before exiting the applicaiton
		delete Application::application.release();
	}
}

/*
* Definition of the default main function
* No arguments needed for starting the uranium app
*/
auto main() -> int {
	/*
	* Start application from global space
	*/
	uranium::core::buildApplication();

	return 0; // Exit success
}
