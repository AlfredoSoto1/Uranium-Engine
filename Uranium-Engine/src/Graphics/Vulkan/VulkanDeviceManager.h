#pragma once

#include <vector>
#include <optional>

namespace Uranium::Graphics::Vulkan {

    class VulkanDeviceManager final {
    public:
        explicit VulkanDeviceManager() noexcept;

        ~VulkanDeviceManager();

        // Initialize Vulkan instance and device
        void initialize();

        // Cleanup Vulkan resources
        void cleanup();

        VkDevice getDevice() const;

    private:
        /*
        */
        void pickPhysicalDevice();
        void createLogicalDevice();

    private:
        /*
        * Queue Family Indices
        * This holds the indices (if any),
        * of the queues used to render and present to the screen
        */
        struct QueueFamilyIndices final {
        public:
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            /*
            * Returns true if the graphics and present queues
            * are present in both optionals
            */
            bool isComplete() const {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        /*
        * Returns the struct of queue family indices
        */
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    private:
        /*
        * Physical and logical device setup helpers
        */
        std::vector<VkPhysicalDevice> scanForPhysicalDevices() const;
        int rateDeviceSuitability(VkPhysicalDevice device) const;

        bool isDeviceSuitable(VkPhysicalDevice device);

        void populateDeviceFeatures(VkDeviceCreateInfo& createInfo);
        void populateQueueCreateInfos(const QueueFamilyIndices& indices, VkDeviceCreateInfo& createInfo);

    private:
        /*
        * Extensions helpers
        */
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void populateDeviceExtensions(VkDeviceCreateInfo& createInfo);
        void prepareRequiredExtensions(VkInstanceCreateInfo& createInfo);

    private:
        static constexpr bool enableValidationLayers = true; // DEBUG

        VkDevice device;
        VkPhysicalDevice physicalDevice; // GPU selected

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        // Add other Vulkan-related members as needed
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
    };
}