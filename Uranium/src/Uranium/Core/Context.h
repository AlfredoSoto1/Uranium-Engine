#pragma once

namespace Uranium::Core {

	/*
	* Context class
	* 
	* This class creates a context inside a thread
	* from the thread pool of the application. The
	* context created from an instance of this class
	* will be incharged of managing everything related to:
	* 
	* - Window opening/closing and updating
	* - Context update workflow
	* - Context rendering workflow
	*/
	class Context {
	public:
		Context();
		
		virtual ~Context();
	
	public:
		/*
		* public methods
		*/
		void setOpenGLVersion(unsigned int mayor, unsigned int minor);

	private:
		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;
	};
}