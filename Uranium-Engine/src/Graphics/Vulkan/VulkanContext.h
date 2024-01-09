//#pragma once
//
//#include <vector>
//#include <string>
//#include <optional>
//
//namespace Uranium::Graphics::Vulkan {
//
//	class VulkanContext final {
//    public:
//        explicit VulkanContext(
//            const std::string& engineName,
//            const std::string& applicationName,
//            uint32_t appMajor = 1,    // 
//            uint32_t appMinor = 0,    // Application version 
//            uint32_t appPatch = 0,    // 
//                                      
//            uint32_t engineMajor = 1, //
//            uint32_t engineMinor = 0, // Engine version
//            uint32_t enginePatch = 0  //
//        ) noexcept;
//
//        ~VulkanContext();
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
//        * Helper functions for Vulkan initialization
//        */
//        void pickPhysicalDevice();
//        void createLogicalDevice();
//
//    private:
//        /*
//        * Queue Family Indices
//        * This holds the indices (if any),
//        * of the queues used to render and present to the screen
//        */
//        struct QueueFamilyIndices final {
//        public:
//            std::optional<uint32_t> graphicsFamily;
//            std::optional<uint32_t> presentFamily;
//
//            /*
//            * Returns true if the graphics and present queues
//            * are present in both optionals
//            */
//            bool isComplete() const {
//                return graphicsFamily.has_value() && presentFamily.has_value();
//            }
//        };
//
//        /*
//        * Returns the struct of queue family indices
//        */
//        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
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
//        void populateQueueCreateInfos(const QueueFamilyIndices& indices, VkDeviceCreateInfo& createInfo);
//
//    private:
//        /*
//        * Extensions helpers
//        */
//        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
//        void populateDeviceExtensions(VkDeviceCreateInfo& createInfo);
//
//    private:
//        static constexpr bool enableValidationLayers = true; // DEBUG
//
//        VkPhysicalDevice physicalDevice; // GPU selected
//        VkDevice device;
//
//        VkQueue graphicsQueue;
//        VkQueue presentQueue;
//
//        // Add other Vulkan-related members as needed
//        const std::vector<const char*> validationLayers = {
//            "VK_LAYER_KHRONOS_validation"
//        };
//
//        const std::vector<const char*> deviceExtensions = {
//            VK_KHR_SWAPCHAIN_EXTENSION_NAME
//        };
//	};
//}