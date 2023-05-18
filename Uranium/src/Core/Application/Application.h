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
		
		Application(Application&) = delete;				  // 
		Application(Application&&) = delete;			  //  Most of the constructors have been deleted
														  //  because we don't want any user to create an
		Application(const Application&) = delete;		  //  instance of Application
		Application(const Application&&) = delete;		  // 

		/*
		* Starts application with a reference
		* to a program that has all the necessary
		* methods required to run the sub-program
		* according to the application rules
		*/
		static void start(std::shared_ptr<ApplicationProgram> program);

		static Application* get();

		bool isProgramRunnning();
		bool hasProgramInitiated();

	private:
		/*
		* Private static members
		*/

		// Current active application reference
		static Application* appSingleton;

		static void error_callback(int error, const char* description);
	
	private:
		/*
		* Private methods
		*/
	
		Application(std::shared_ptr<ApplicationProgram> program);
	
		void run();

	private:
		/*
		* Private members
		*/
		std::shared_ptr<ApplicationProgram> program;

		bool isRunning;
		bool hasInitiated;
	};
}