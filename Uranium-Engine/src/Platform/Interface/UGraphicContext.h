#pragma once

#include <cstdint>
#include <string>
#include "Core/CoreMacros.h"

namespace Uranium::Platform::Interface {

	URANIUM_API class UGraphicContext {
	public:
		/*
		* @param App-Name
		* @param Engine-Name
		* @param App-Version (mayor, minor, patch)
		* @param Engine-Version (mayor, minor, patch)
		*/
		explicit UGraphicContext(
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor, 
			uint32_t appMinor,
			uint32_t appPatch, 

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch 
		) noexcept;

		virtual ~UGraphicContext() noexcept;

	public:
		void init();
		void shutdown() noexcept;

	public:
		/*
		* @returns the instance in relation to the graphics API used
		*/
		//virtual UGraphicInstance<> getInstance() const noexcept = 0;

	public:
		/*
		* Enables the validation logs meaning that the graphics
		* API selected can log everything that is happening.
		* If the build configuration of the program is set to UR_DEBUG,
		* all logs will be presented in the console. If the configuration
		* is set to UR_RELEASE, all logs will appear on a log file as the
		* default output.
		* 
		* @param enableValidationLogs
		*/
		void enableValidationLog(bool enableValidationLogs) noexcept;

	protected:
		/*
		* Creates an instance that references the graphics API
		*/
		virtual void createInstance() = 0;
		
		/*
		* Disposes the instance that references the graphics API
		*/
		virtual void disposeInstance() noexcept = 0;

	protected:
		/*
		* Prepares and initializes all debug configurations.
		* This is done only when the application configuration
		* is set to UR_DEBUG.
		*/
		virtual void setupDebugConfigurations() noexcept = 0;

		/*
		* This obtains the latest API version
		*/
		virtual void catchLatestVersion() noexcept = 0;

	private:
		// Application & Engine names
		std::string engineName;
		std::string applicationName;

		// Application version
		uint32_t appMajor;
		uint32_t appMinor;
		uint32_t appPatch;

		// Engine version
		uint32_t engineMajor;
		uint32_t engineMinor;
		uint32_t enginePatch;

		bool enableValidationLogs;
	};
}