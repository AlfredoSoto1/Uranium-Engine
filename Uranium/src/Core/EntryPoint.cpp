
import Uranium.Core.Application;

import <memory>;

/*
* Define a custom entry point where
* the application can start without the need of
* a main function. With this the application can handle
* efficiently the lifetime of the Application.
*/
extern std::unique_ptr<Uranium::Core::Application> createApplication();

/*
* Definition of the default main function
*/
auto main(int argc, char* argv[]) -> int {

	/*
	* Build the Application
	*/
	Uranium::Core::Application::build(
		argc, // argument count
		argv, // argument values as an array
		std::move(createApplication())
	);

	return 0; // Exit success
}