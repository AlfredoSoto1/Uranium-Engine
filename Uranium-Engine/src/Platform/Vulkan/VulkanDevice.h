#pragma once

#include <vector>
#include <optional>

#include "Core/CoreMacros.h"

#include "VulkanStructs.h"

namespace Uranium::Platform::Vulkan {

    UR_DECLARE VulkanAPI;
    UR_DECLARE VulkanContext;

    URANIUM_API class VulkanDevice final {
    public:
        explicit VulkanDevice(const VulkanAPI& vulkanAPI) noexcept;

        ~VulkanDevice() noexcept;

    public:
        VkDevice getDevice() const noexcept;
        
        const DeviceQueueFamilyIndices& getQueueFamilies() const noexcept;
        const SwapChainSupportDetails&  getSwapChainSupportDetails() const noexcept;

    private:
        /*
        * Picks the suitable physical device for the application
        * to use.
        *
        * @throw Vulkan instance is NULL
        */
        void pickPhysicalDevice();

        /*
        * Creates a logical device from the physical device for the
        * application to use for rendering.
        *
        * @throw Vulkan instance is NULL
        */
        void createLogicalDevice();

        /*
        * Obtains the device queues from the indices
        */
        void obtainDeviceQueues() noexcept;

    private:
        /*
        * Scans the hardware for any physical devices available.
        *
        * @returns vector of all physical devices available to the application.
        * If no physical devices available, the returning vector will be empty.
        */
        std::vector<VkPhysicalDevice> scanForPhysicalDevices() const noexcept;

        /*
        * Rates the properties and features of the device. This is used to sort
        * properly the devices of interest for the application to use.
        *
        * @returns the score of the evaluated properties of the device.
        */
        int rateDeviceProperties(VkPhysicalDevice device) const noexcept;

        /*
        * @returns true if the GPU device is suitable for the application to use.
        */
        bool isDeviceSuitable(VkPhysicalDevice device) noexcept;

    private:
        /*
        * Populates the required device features that the application
        * needs in order to create the logical device.
        * 
        * @param createInfo-ref
        */
        void populateDeviceFeatures(VkDeviceCreateInfo& createInfo) noexcept;

        /*
        * Populates the required extensions that the application
        * needs in order to create the logical device.
        * 
        * @param createInfo-ref
        */
        void populateDeviceExtensions(VkDeviceCreateInfo& createInfo) noexcept;

        /*
        * Populates the required information to create a device with the
        * proper family queue indices.
        *
        * @param indices
        * @param createInfo-ref
        */
        void populateDeviceQueueFamilyInfo(VkDeviceCreateInfo& createInfo) noexcept;

        /*
        * Populates the required validation layer information that the
        * device supports. This is only evaluated if the application 
        * configuration is set to UR_DEBUG.
        *
        * @param createInfo-ref
        */
        void populateDeviceValidationLayerSupport(VkDeviceCreateInfo& createInfo) noexcept;

    private:
        /*
        * @returns struct of queue family indices
        */
        DeviceQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const noexcept;

    private:
        /*
        * @param physical-device
        * 
        * @returns true if the physical device has the extensions required
        */
        bool checkDeviceExtensionSupport(VkPhysicalDevice device) const noexcept;

        /*
        * Queries all the swap chain support details to a struct
        * from the provided physical device.
        * 
        * @param physicalDevice
        * @returns swapchain-support-details
        */
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const noexcept;

    private:
        const VulkanAPI& vulkanAPI;

        VkDevice device;                  // Logical device
        VkPhysicalDevice physicalDevice;  // GPU device
    
        VkQueue graphicsQueue;           
        VkQueue presentQueue;            
        DeviceQueueFamilyIndices queueIndices;

        SwapChainSupportDetails swapChainSupport;
    };
}