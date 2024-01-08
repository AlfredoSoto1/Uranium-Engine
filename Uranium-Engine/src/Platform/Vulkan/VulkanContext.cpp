#include "VulkanContext.h"

namespace Uranium::Platform::Vulkan {
	VulkanContext::VulkanContext(
		const std::string& engineName      = "Engine",
		const std::string& applicationName = "Application",

		uint32_t appMajor = 1,
		uint32_t appMinor = 0,
		uint32_t appPatch = 0,

		uint32_t engineMajor = 1,
		uint32_t engineMinor = 0,
		uint32_t enginePatch = 0
	) noexcept :
		Interface::UGraphicContext(
			engineName, 
			applicationName,

			appMajor, 
			appMinor, 
			appPatch,

			engineMajor,
			engineMinor,
			enginePatch
		)
	{
	}

	VulkanContext::~VulkanContext() noexcept {

	}

	void VulkanContext::createInstance() {

	}

	void VulkanContext::disposeInstance() noexcept {

	}

	void VulkanContext::setupDebugConfigurations() noexcept {

	}

	void VulkanContext::catchLatestVersion() noexcept {

	}
}