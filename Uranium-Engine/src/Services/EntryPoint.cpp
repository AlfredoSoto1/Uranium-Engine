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
	void startApplication(int argc, char* argv[]) {

		// Build the application
		Application::build(
			argc, // argument count
			argv, // argument values as an array
			std::move(createApplication())
		);

		// Application ends here
	}
}

/*
* Definition of the default main function
*/
auto main(int argc, char* argv[]) -> int {

	/*
	* Start application from global space
	*/
	Uranium::Services::startApplication(argc, argv);

	return 0; // Exit success
}