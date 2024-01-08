#pragma once

#include "Core/CoreMacros.h"
#include "Platform/Interface/UGraphicContext.h"

namespace Uranium::Platform::Vulkan {

	URANIUM_API class VulkanContext final :
		UR_EXTENDS Interface::UGraphicContext
	{
	public:
		/*
		* @param App-Name
		* @param Engine-Name
		* @param App-Version (mayor, minor, patch)
		* @param Engine-Version (mayor, minor, patch)
		*/
		explicit VulkanContext(
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor,
			uint32_t appMinor,
			uint32_t appPatch,

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch
		) noexcept;

		virtual ~VulkanContext() noexcept;

	protected:
		/*
		* Creates an instance that references the graphics API
		*/
		virtual void createInstance() override;

		/*
		* Disposes the instance that references the graphics API
		*/
		virtual void disposeInstance() noexcept override;

	protected:
		/*
		* Prepares and initializes all debug configurations.
		* This is done only when the application configuration
		* is set to UR_DEBUG.
		*/
		virtual void setupDebugConfigurations() noexcept override;

		/*
		* This obtains the latest API version
		*/
		virtual void catchLatestVersion() noexcept override;

	private:
	};
}