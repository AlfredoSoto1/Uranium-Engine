#pragma once

namespace Uranium::Core {

	class Application;

	/*
	* WorkingUnit class
	* 
	* This class creates a WorkingUnit inside a thread
	* from the thread pool of the application. The
	* WorkingUnit created from an instance of this class
	* will be incharged of managing everything related to:
	* 
	* - Window opening/closing and updating
	* - WorkingUnit update workflow
	* - WorkingUnit rendering workflow
	*/
	class WorkingUnit {
	public:

		explicit WorkingUnit();
		
		virtual ~WorkingUnit();
	
	public:
		/*
		* public methods
		*/
		virtual void init();
		virtual void dispose();

		operator volatile bool() const;

	private:
		/*
		* friends with other classes
		*/
		friend Application;

	private:
		/*
		* private members
		*/
		volatile bool unitCreated;

	private:
		/*
		* private methods
		*/

		// The method run() will be incharged
		// or running 'this' context in a controled
		// enviroment managed by the application.
		void run();
	};
}