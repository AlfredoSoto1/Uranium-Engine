#pragma once

#include "Core/CoreMacros.h"

namespace Uranium::Platform::Interface {

	UR_DECLARE Window;

	URANIUM_API class GraphicsAPI {
	public:
		explicit GraphicsAPI(
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor,
			uint32_t appMinor,
			uint32_t appPatch,

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch
		) noexcept;

		virtual ~GraphicsAPI() noexcept = default;

	public:
		/*
		* Initiates the Vulkan API
		*/
		void init(const Interface::Window& window);
		void shutdown() noexcept;

	public:
		/*
		* @returns true if the device supports validation layers
		* for the graphics API.
		*/
		bool hasValidationLayerSupport() const noexcept;

	private:
		/*
		* Prepares and initializes all debug configurations.
		* This is done only when the application configuration
		* is set to UR_DEBUG.
		*/

		void setupDebugConfigurations();
		bool checkValidationLayerSupport() const noexcept;

	protected:
		static constexpr const bool validationLayerSupported = UR_ON_DEBUG_SWAP(true, false);

	};
}