#pragma once

#include <vector>
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

	public:
		/*
		* @returns the instance in relation to the graphics API used
		*/
		InstanceRef getInstance() const noexcept;

	private:
		void createInstance() override;
		void disposeInstance() noexcept override;
		void catchLatestVersion() noexcept override;

	private:
		VkApplicationInfo createVulkanApplication();

	private:
		bool hasValidationLayerSupport() const noexcept override;
		bool checkValidationLayerSupport() const noexcept override;

		void populateValidationLayers(VkInstanceCreateInfo& createInfo);

	private:
		/*
		* Prepares the debug configurations
		*/
		void setupDebugConfigurations() noexcept override;

		/*
		* @returns Information related to the debug messenger
		*/
		VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo() noexcept;

		/*
		* Creates the debug messenger
		*/
		VkResult createDebugUtilsMessengerEXT(
			VkInstance                                instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks*              pAllocator,
			VkDebugUtilsMessengerEXT*                 pDebugMessenger
		) const;
		
		/*
		* Disposes the debug messenger
		*/
		void destroyDebugUtilsMessengerEXT(
			VkInstance                   instance,
			VkDebugUtilsMessengerEXT     debugMessenger,
			const VkAllocationCallbacks* pAllocator
		);

	private:
		void populateRequiredExtensions(VkInstanceCreateInfo& createInfo);

	private:
		// Add other Vulkan-related members as needed
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
		
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		bool isDebugMessengerSupported;
		bool isValidationLayerSupported;
	};
}