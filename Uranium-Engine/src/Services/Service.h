#pragma once

namespace Uranium::Services {

	/*
	* Service interface:
	* This is used for generic service hosting
	* inside the application
	*/
	class Service {
	public:
		/*
		* Initiates the service
		*/
		virtual void init() = 0;
		
		/*
		* Starts the service
		*/
		virtual void start() = 0;

		/*
		* It kills the service when running
		* this disposes the service automatically
		*/
		virtual void prune() = 0;

		/*
		* Returns true if the current service is active
		*/
		virtual bool isActive() const = 0;
	};
}