#pragma once

#include <vector>
#include <optional>

namespace Uranium::Graphics::Vulkan {

    class VulkanExtensionsManager final {
    public:
        explicit VulkanExtensionsManager() noexcept;

        ~VulkanExtensionsManager();

        // Initialize Vulkan instance and device
        void initialize();

        // Cleanup Vulkan resources
        void cleanup();

    private:
        /*
        * Extensions helpers
        */
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void populateDeviceExtensions(VkDeviceCreateInfo& createInfo);
        void prepareRequiredExtensions(VkInstanceCreateInfo& createInfo);

    private:
        static constexpr bool enableValidationLayers = true; // DEBUG

        // Add other Vulkan-related members as needed
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
    };
}