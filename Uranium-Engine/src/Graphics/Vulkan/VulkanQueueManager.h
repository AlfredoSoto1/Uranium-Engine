#pragma once

#include <vector>
#include <optional>

namespace Uranium::Graphics::Vulkan {

    class VulkanQueueManager final {
    public:
        explicit VulkanQueueManager() noexcept;

        ~VulkanQueueManager();

        // Initialize Vulkan instance and device
        void initialize();

        // Cleanup Vulkan resources
        void cleanup();

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
        void populateQueueCreateInfos(const QueueFamilyIndices& indices, VkDeviceCreateInfo& createInfo);

    private:
        static constexpr bool enableValidationLayers = true; // DEBUG

        VkQueue graphicsQueue;
        VkQueue presentQueue;
    };
}