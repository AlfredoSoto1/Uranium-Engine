#pragma once

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

#include "Core/CoreMacros.h"
#include "Platform/Interface/GraphicsAPI.h"

namespace Uranium::Platform::Interface {
	UR_DECLARE Window;
}

namespace Uranium::Platform::Vulkan {

	UR_DECLARE VulkanContext;
	UR_DECLARE VulkanDevice;
	UR_DECLARE VulkanSwapChain;

    URANIUM_API class VulkanAPI {// : UR_EXTENDS GraphicsAPI {
    public:
		friend VulkanContext;
		friend VulkanDevice;
		friend VulkanSwapChain;

    public:
        explicit VulkanAPI(
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor,
			uint32_t appMinor,
			uint32_t appPatch,

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch
		) noexcept;

        virtual ~VulkanAPI() noexcept = default;

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

		/*
		* @returns Information related to the debug messenger
		*/
		VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo() const noexcept;

	private:
		/*
		* Create debug utils messenger extension
		* This extension is required to debug any vulkan
		* related event/call. This is not called in other
		* configurations that is not UR_DEBUG
		*
		* @param instance
		* @param pCreateInfo
		* @param pAllocator
		* @param pDebugMessenger
		*
		* @throw Vulkan instance is NULL
		*/
		VkResult createDebugUtilsMessengerEXT(
			VkInstance                                instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		) const;

		/*
		* Destroys the created instance for the
		* extension requested.This is not called in other
		* configurations that is not UR_DEBUG
		*
		* @param instance
		* @param debugMessenger
		* @param pAllocator
		*/
		void destroyDebugUtilsMessengerEXT(
			VkInstance                   instance,
			VkDebugUtilsMessengerEXT     debugMessenger,
			const VkAllocationCallbacks* pAllocator
		) const noexcept;

    private:
        static constexpr const bool validationLayerSupported = UR_ON_DEBUG_SWAP(true, false);

	private:
		/*
		* API specific validation layers and extensions
		*/
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

	private:
		VkDebugUtilsMessengerEXT debugMessenger;
		
		std::unique_ptr<VulkanContext> context;
		std::unique_ptr<VulkanDevice> deviceManager;

		VkSurfaceKHR surface;
    };
}