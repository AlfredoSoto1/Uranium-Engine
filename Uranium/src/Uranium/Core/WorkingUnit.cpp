#include <iostream>
#include <GLFW/glfw3.h>

#include "WorkingUnit.h"

namespace Uranium::Core {

	WorkingUnit::WorkingUnit() :
		unitCreated(false)
	{
		std::cout << "WorkingUnit created" << std::endl;
	}

	WorkingUnit::~WorkingUnit() {
		std::cout << "WorkingUnit destroyed" << std::endl;
	}

	WorkingUnit::operator volatile bool() const {
		return unitCreated;
	}

	void WorkingUnit::init() {
	
	}

	void WorkingUnit::dispose() {
	
	}

	void WorkingUnit::run() {
		// Initiate the context
		// Here will be loading and creating
		// all context dependent features.
		init();

		// --Do something interesting here--

		// Dispose all content from 'this'
		// context generated when it initiated
		dispose();
	}
}