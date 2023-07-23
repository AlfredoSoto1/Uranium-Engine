#pragma once

namespace Uranium::Core {
	
	class Application;

	/*
	* Application Thread Pool
	* 
	* This class is incharged of creating a pool of
	* threads that will run in parallel in relation to
	* one another. Each thread will have its unique way
	* of behaving dictated by client.
	*/
	class ApplicationThreadPool {
	public:
		/*
		* Delete the copy/move constructors
		* to prevent client from using this singleton class.
		*/
		ApplicationThreadPool(ApplicationThreadPool& copy) = delete;
		ApplicationThreadPool(ApplicationThreadPool&& move) = delete;
		ApplicationThreadPool(const ApplicationThreadPool& copy) = delete;
		ApplicationThreadPool(const ApplicationThreadPool&& move) = delete;

		// Free the thread pool content allocated
		~ApplicationThreadPool();

	private:
		/*
		* Friends with other classes
		*/
		friend Application;

	private:
		// Create a single thread pool where all
		// threads will live.
		explicit ApplicationThreadPool();
		
		void start();
		void dispose();
		void shutdown();
	};
}