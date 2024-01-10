#pragma once

#include <string>
#include <cstdint>
#include "Core/CoreMacros.h"

namespace Uranium::Platform::Interface {

	URANIUM_API class GraphicContext {
	public:
		/*
		* @param App-Name
		* @param Engine-Name
		* @param App-Version (mayor, minor, patch)
		* @param Engine-Version (mayor, minor, patch)
		*/
		explicit GraphicContext(
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor, 
			uint32_t appMinor,
			uint32_t appPatch, 

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch 
		) noexcept;

		~GraphicContext() noexcept = default;

	public:
		using InstanceRef = void*;

		/*
		* @returns the instance in relation to the graphics API used
		*/
		virtual InstanceRef getInstance() const noexcept = 0;

	public:
		virtual void init() = 0;
		virtual void shutdown() noexcept = 0;

	public:
		/*
		* @returns true if the device supports validation layers
		* for the graphics API.
		*/
		virtual bool hasValidationLayerSupport() const noexcept = 0;

	protected:
		/*
		* Creates a unique instance to reference the API selected.
		* Disposes the instance if initialized before.
		* Catches the latest version of the API to run as default.
		*/

		virtual void createInstance() = 0;
		virtual void disposeInstance() noexcept = 0;
		virtual void catchLatestVersion() noexcept = 0;

	protected:
		/*
		* Prepares and initializes all debug configurations.
		* This is done only when the application configuration
		* is set to UR_DEBUG.
		*/

		virtual void setupDebugConfigurations() = 0;
		virtual bool checkValidationLayerSupport() const noexcept = 0;

	protected:
		std::string engineName;      // Engine name
		std::string applicationName; // Application name
		                             //
		uint32_t appMajor;           // 
		uint32_t appMinor;           // Application version
		uint32_t appPatch;           // 
		                             // 
		uint32_t engineMajor;        //
		uint32_t engineMinor;        // Engine version
		uint32_t enginePatch;        //

		static constexpr const bool validationLayerSupported = UR_ON_DEBUG_SWAP(true, false);
	};
}