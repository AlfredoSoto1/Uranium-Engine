#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <set>
#include <iostream>
#include <stdexcept>
#include "VulkanQueueManager.h"

namespace Uranium::Graphics::Vulkan {

    VulkanQueueManager::VulkanQueueManager() noexcept {

    }

    VulkanQueueManager::~VulkanQueueManager() {

    }

    void VulkanQueueManager::initialize() {

    }

    void VulkanQueueManager::cleanup() {

    }

    VulkanQueueManager::QueueFamilyIndices VulkanQueueManager::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        // Obtain the family queue count
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        if constexpr (enableValidationLayers)
            std::cout << "There are [" << queueFamilyCount << "] family queues available." << std::endl;

        // Iterate over all family queues that the physical device has
        // then populate the QueueFamilyIndices with the corresponding queue index
        for (uint32_t index = 0; index < queueFamilies.size(); index++) {
            // Check if the queue family supports graphics operations
            if (queueFamilies[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = index;

            // Check if the queue family supports presentation to the specified surface
            VkBool32 presentSupport = false;
            //vkGetPhysicalDeviceSurfaceSupportKHR(device, index, surface, &presentSupport); // TODO

            if (presentSupport)
                indices.presentFamily = index;

            // If both graphics and presentation families are found, exit the loop
            if (indices.isComplete())
                break;
        }

        // Return the QueueFamilyIndices containing the results
        return indices;
    }

    void VulkanQueueManager::populateQueueCreateInfos(const QueueFamilyIndices& indices, VkDeviceCreateInfo& createInfo) {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        // Create a set for all the queue families. This is to eliminate the duplicate
        // indices and provide a more generic and scalable solution for future modifications
        // if more family queues were to be added.
        std::set<uint32_t> uniqueQueueFamilies = {
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
        };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        // Pass the device queue information
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
    }
}