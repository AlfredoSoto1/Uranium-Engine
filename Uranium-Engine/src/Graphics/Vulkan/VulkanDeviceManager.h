//#pragma once
//
//#include <vector>
//#include <optional>
//
//namespace Uranium::Graphics::Vulkan {
//
//    class VulkanDeviceManager final {
//    public:
//        explicit VulkanDeviceManager() noexcept;
//
//        ~VulkanDeviceManager();
//
//        // Initialize Vulkan instance and device
//        void initialize();
//
//        // Cleanup Vulkan resources
//        void cleanup();
//
//        VkDevice getDevice() const;
//
//    private:
//        /*
//        */
//        void pickPhysicalDevice();
//        void createLogicalDevice();
//
//    private:
//        /*
//        * Physical and logical device setup helpers
//        */
//        std::vector<VkPhysicalDevice> scanForPhysicalDevices() const;
//        int rateDeviceSuitability(VkPhysicalDevice device) const;
//
//        bool isDeviceSuitable(VkPhysicalDevice device);
//
//        void populateDeviceFeatures(VkDeviceCreateInfo& createInfo);
//
//    private:
//        static constexpr bool enableValidationLayers = true; // DEBUG
//
//        VkDevice device;
//        VkPhysicalDevice physicalDevice; // GPU selected
//
//        // Add other Vulkan-related members as needed
//        const std::vector<const char*> validationLayers = {
//            "VK_LAYER_KHRONOS_validation"
//        };
//
//        const std::vector<const char*> deviceExtensions = {
//            VK_KHR_SWAPCHAIN_EXTENSION_NAME
//        };
//    };
//}