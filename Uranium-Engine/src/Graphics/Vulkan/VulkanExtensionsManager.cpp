#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <set>
#include <map>
#include <iostream>
#include <stdexcept>
#include "VulkanExtensionsManager.h"

namespace Uranium::Graphics::Vulkan {

    VulkanExtensionsManager::VulkanExtensionsManager() noexcept {

    }

    VulkanExtensionsManager::~VulkanExtensionsManager() {

    }

    void VulkanExtensionsManager::initialize() {
    }

    void VulkanExtensionsManager::cleanup() {

    }

    void VulkanExtensionsManager::prepareRequiredExtensions(VkInstanceCreateInfo& createInfo) {
        // Returns the required extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> requiredExtensions(glfwExtensionCount);

        for (uint32_t i = 0; i < glfwExtensionCount; i++)
            requiredExtensions.emplace_back(glfwExtensions[i]);

        // add more extensions here if needed in the future
        if constexpr (enableValidationLayers)
            requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        // Returns all the extensions that vulkan supports in *this* platform
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        // Log all the extensions that are required by the applicaiton
        // and the extensions available to use
        if constexpr (enableValidationLayers) {
            std::cout << "Required extensions count [" << glfwExtensionCount << "]" << std::endl;
            for (uint32_t i = 0; i < glfwExtensionCount; i++)
                std::cout << "extension[" << i << "]: " << requiredExtensions[i] << std::endl;

            std::cout << "Available extensions count [" << extensionCount << "]" << std::endl;
            for (uint32_t i = 0; i < extensionCount; i++)
                std::cout << extensions[i].extensionName << std::endl;
        }

        createInfo.enabledExtensionCount = (uint32_t)(requiredExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    }

    bool VulkanExtensionsManager::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
            requiredExtensions.erase(extension.extensionName);

        return requiredExtensions.empty();
    }

    void VulkanExtensionsManager::populateDeviceExtensions(VkDeviceCreateInfo& createInfo) {
        // Pass the device extension names
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    }
}