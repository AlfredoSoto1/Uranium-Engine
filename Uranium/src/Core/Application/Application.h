#pragma once

#include <memory>

#include "ApplicationProgram.h"

namespace Uranium::Core::Application {

	class Application {
	public:
		/*
		* remove all constructors
		* to prevent any user creating one that
		* might break the actual flow and
		* creation of the program 
		*/
		Application() = delete;
		
		Application(Application&) = delete;
		Application(Application&&) = delete;
		
		Application(const Application&) = delete;
		Application(const Application&&) = delete;

		/*
		* Starts application with a reference
		* to a program that has all the necessary
		* methods required to run the sub-program
		* according to the application rules
		*/
		static void start(std::shared_ptr<ApplicationProgram> program);

	private:
		/*
		* Private static members
		*/

		// Current active application reference
		static Application* mainApplication;
	
	private:
		/*
		* Private methods
		*/
	
		Application(std::shared_ptr<ApplicationProgram> program);
	
		// Runs application
		void run();

	private:
		/*
		* Private members
		*/
		// Current active program reference
		std::shared_ptr<ApplicationProgram> program;
	};
}