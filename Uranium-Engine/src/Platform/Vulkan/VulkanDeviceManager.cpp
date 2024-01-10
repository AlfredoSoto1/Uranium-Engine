#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <set>
#include <map>
#include <stdexcept>
#include "Core/Logger.h"

#include "VulkanAPI.h"
#include "VulkanContext.h"
#include "VulkanDeviceManager.h"

namespace Uranium::Platform::Vulkan {

    VulkanDeviceManager::VulkanDeviceManager(const VulkanAPI& vulkanAPI, const VulkanContext& context) noexcept :
        vulkanAPI(vulkanAPI),
        context(context),

        graphicsQueue(VK_NULL_HANDLE),
        presentQueue(VK_NULL_HANDLE),
        queueIndices(),

        device(VK_NULL_HANDLE),
        physicalDevice(VK_NULL_HANDLE)
    {

    }

    void VulkanDeviceManager::pickPhysicalDevice() {
        // Obtain all the GPU devices connected to the hardware
        std::vector<VkPhysicalDevice> devices = scanForPhysicalDevices();

        // If there is no device connected, there is no need to continue
        if (devices.empty())
            throw std::runtime_error("failed to find GPUs with Vulkan support!");

        // Use an ordered map to automatically sort candidates by increasing score
        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices) {
            int score = rateDeviceProperties(device);
            candidates.insert(std::make_pair(score, device));
        }

        VkPhysicalDevice deviceCandidate = VK_NULL_HANDLE;

        // Check if the best candidate is suitable at all
        // The last element of the ordered map has the highest score
        if (candidates.rbegin()->first > 0)
            deviceCandidate = candidates.rbegin()->second;
        else
            throw std::runtime_error("failed to obtain rated device!");

        // Check if the device candidate is suitable
        if (isDeviceSuitable(deviceCandidate))
            physicalDevice = deviceCandidate;
        else
            throw std::runtime_error("failed to find a suitable GPU!");
    }

    void VulkanDeviceManager::createLogicalDevice() {

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        // Populate the required information for the device to be created
        populateDeviceFeatures(createInfo);
        populateDeviceExtensions(createInfo);
        populateDeviceQueueFamilyInfo(createInfo);
        populateDeviceValidationLayerSupport(createInfo);

        VkResult deviceCreationResult = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);

        // Handle runtime errors after creating the device
        switch (deviceCreationResult) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, host out of memory!");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, device out of memory!");
        case VK_ERROR_INITIALIZATION_FAILED:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, initialization failed!");
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, extension not present!");
        case VK_ERROR_FEATURE_NOT_PRESENT:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, device feature not present!");
        case VK_ERROR_TOO_MANY_OBJECTS:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, too many objects!");
        case VK_ERROR_DEVICE_LOST:
            device = VK_NULL_HANDLE;
            throw std::runtime_error("Failed logical device creation, device lost!");
        }

        if constexpr (VulkanAPI::validationLayerSupported)
            Core::UR_INFO("[Vulkan]", "Logical device created.");
    }

    void VulkanDeviceManager::disposeDevice() noexcept {
        if (device != VK_NULL_HANDLE) {
            vkDestroyDevice(device, nullptr);
            device = VK_NULL_HANDLE;
        }
        else
            Core::UR_WARN("[Vulkan]", "Failed to dispose logical device reference since it was already NULL.");
    }

    void VulkanDeviceManager::obtainDeviceQueues() noexcept {
        // Get the device queue for the graphics and present families
        vkGetDeviceQueue(device, queueIndices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, queueIndices.presentFamily.value(), 0, &presentQueue);
    }

    VkDevice VulkanDeviceManager::getDevice() const noexcept {
        return device;
    }

    std::vector<VkPhysicalDevice> VulkanDeviceManager::scanForPhysicalDevices() const noexcept {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(context.getInstance(), &deviceCount, nullptr);

        if (deviceCount == 0)
            return {}; // No devices available

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(context.getInstance(), &deviceCount, devices.data());

        return devices;
    }

    bool VulkanDeviceManager::isDeviceSuitable(VkPhysicalDevice device) noexcept {
        // Obtain the family queues indices
        queueIndices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            //SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            //swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return queueIndices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    int VulkanDeviceManager::rateDeviceProperties(VkPhysicalDevice device) const noexcept {
        int score = 0;

        // Obtain the properties of the physical device
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // Obtain the features of the physical device
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        // Discrete GPUs have a significant performance advantage
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            score += 1000;

        // Maximum possible size of textures affects graphics quality
        score += deviceProperties.limits.maxImageDimension2D;

        // Filter more by features or device properties

        // Application can't function without geometry shaders
        if (!deviceFeatures.geometryShader)
            return 0; // If geometry shaders are not supported, return 0 (unsuitable)

        return score;
    }

    void VulkanDeviceManager::populateDeviceFeatures(VkDeviceCreateInfo& createInfo) noexcept {
        // Set physical device features to default
        VkPhysicalDeviceFeatures deviceFeatures{};

        // Set the enabled physical device features
        createInfo.pEnabledFeatures = &deviceFeatures;
    }

    void VulkanDeviceManager::populateDeviceExtensions(VkDeviceCreateInfo& createInfo) noexcept {
        // Pass the device extension names
        createInfo.enabledExtensionCount = static_cast<uint32_t>(vulkanAPI.deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = vulkanAPI.deviceExtensions.data();
    }

    void VulkanDeviceManager::populateDeviceQueueFamilyInfo(VkDeviceCreateInfo& createInfo) noexcept {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        // Create a set for all the queue families. This is to eliminate the duplicate
        // indices and provide a more generic and scalable solution for future modifications
        // if more family queues were to be added.
        std::set<uint32_t> uniqueQueueFamilies = {
            queueIndices.graphicsFamily.value(),
            queueIndices.presentFamily.value()
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

    void VulkanDeviceManager::populateDeviceValidationLayerSupport(VkDeviceCreateInfo& createInfo) noexcept {
        if constexpr (VulkanAPI::validationLayerSupported) {
            // If the validation layers are enabled, pass the current validation layers
            // information to the logical device information struct to create.
            createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanAPI.validationLayers.size());
            createInfo.ppEnabledLayerNames = vulkanAPI.validationLayers.data();
        }
        else {
            // If no validation layers are enabled, just compile the following line:
            createInfo.enabledLayerCount = 0;
        }
    }

    DeviceQueueFamilyIndices VulkanDeviceManager::findQueueFamilies(VkPhysicalDevice device) const noexcept {
        DeviceQueueFamilyIndices indices = {};

        // Obtain the family queue count
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        if constexpr (VulkanAPI::validationLayerSupported)
            Core::UR_INFO("[Vulkan]", "There are [%d] family queues available.", queueFamilyCount);

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

    bool VulkanDeviceManager::checkDeviceExtensionSupport(VkPhysicalDevice device) const noexcept {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        // Create a set to hold all the required extensions
        // we use a set to remove the duplicates extensions if any.
        std::set<std::string> requiredExtensions(vulkanAPI.deviceExtensions.begin(), vulkanAPI.deviceExtensions.end());

        for (const auto& extension : availableExtensions)
            requiredExtensions.erase(extension.extensionName);

        return requiredExtensions.empty();
    }
}