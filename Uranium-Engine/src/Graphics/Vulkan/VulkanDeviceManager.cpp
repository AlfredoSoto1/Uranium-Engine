//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <stdexcept>
//#include "VulkanDeviceManager.h"
//
//namespace Uranium::Graphics::Vulkan {
//
//    VulkanDeviceManager::VulkanDeviceManager() noexcept {
//
//    }
//
//    VulkanDeviceManager::~VulkanDeviceManager() {
//
//    }
//
//    void VulkanDeviceManager::initialize() {
//        pickPhysicalDevice();
//        createLogicalDevice();
//    }
//
//    void VulkanDeviceManager::cleanup() {
//
//        if (device != VK_NULL_HANDLE) {
//            vkDestroyDevice(device, nullptr);
//            device = VK_NULL_HANDLE;
//        }
//    }
//
//    VkDevice VulkanDeviceManager::getDevice() const {
//        return device;
//    }
//
//    void VulkanDeviceManager::pickPhysicalDevice() {
//        // Obtain all the GPU devices connected to the hardware
//        std::vector<VkPhysicalDevice> devices = scanForPhysicalDevices();
//
//        // If there is no device connected, there is no need to continue
//        if (devices.empty())
//            throw std::runtime_error("failed to find GPUs with Vulkan support!");
//
//        // Use an ordered map to automatically sort candidates by increasing score
//        std::multimap<int, VkPhysicalDevice> candidates;
//
//        for (const auto& device : devices) {
//            int score = rateDeviceSuitability(device);
//            candidates.insert(std::make_pair(score, device));
//        }
//
//        VkPhysicalDevice deviceCandidate = VK_NULL_HANDLE;
//
//        // Check if the best candidate is suitable at all
//        // The last element of the ordered map has the highest score
//        if (candidates.rbegin()->first > 0)
//            deviceCandidate = candidates.rbegin()->second;
//        else
//            throw std::runtime_error("failed to find a suitable GPU!");
//
//        // Check if the device candidate is suitable
//        if (isDeviceSuitable(deviceCandidate))
//            physicalDevice = deviceCandidate;
//
//        if (physicalDevice == VK_NULL_HANDLE)
//            throw std::runtime_error("failed to find a suitable GPU!");
//    }
//
//    void VulkanDeviceManager::createLogicalDevice() {
//        // Obtain the queue family indices
//        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
//
//        VkDeviceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//
//        // Populate the required information for the device to be created
//        populateDeviceFeatures(createInfo);
//        populateDeviceExtensions(createInfo);
//        populateQueueCreateInfos(indices, createInfo);
//
//        if constexpr (enableValidationLayers) {
//            // If the validation layers are enabled, pass the current validation layers
//            // information to the logical device information struct to create.
//            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//            createInfo.ppEnabledLayerNames = validationLayers.data();
//        }
//        else {
//            // If no validation layers are enabled, just compile the following line:
//            createInfo.enabledLayerCount = 0;
//        }
//
//        VkResult deviceCreationResult = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
//
//        // Handle runtime errors after creating the device
//        switch (deviceCreationResult) {
//        case VK_ERROR_OUT_OF_HOST_MEMORY:
//            throw std::runtime_error("Failed logical device creation, host out of memory!");
//        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
//            throw std::runtime_error("Failed logical device creation, device out of memory!");
//        case VK_ERROR_INITIALIZATION_FAILED:
//            throw std::runtime_error("Failed logical device creation, initialization failed!");
//        case VK_ERROR_EXTENSION_NOT_PRESENT:
//            throw std::runtime_error("Failed logical device creation, extension not present!");
//        case VK_ERROR_FEATURE_NOT_PRESENT:
//            throw std::runtime_error("Failed logical device creation, device feature not present!");
//        case VK_ERROR_TOO_MANY_OBJECTS:
//            throw std::runtime_error("Failed logical device creation, too many objects!");
//        case VK_ERROR_DEVICE_LOST:
//            throw std::runtime_error("Failed logical device creation, device lost!");
//        default:
//            if constexpr (enableValidationLayers)
//                std::cout << "Device object created." << std::endl;
//
//            // Get the device queue for the graphics and present families
//            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
//            vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
//        }
//    }
//
//    std::vector<VkPhysicalDevice> VulkanDeviceManager::scanForPhysicalDevices() const {
//        uint32_t deviceCount = 0;
//        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
//
//        if (deviceCount == 0)
//            return {}; // No devices available
//
//        std::vector<VkPhysicalDevice> devices(deviceCount);
//        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
//
//        return devices;
//    }
//
//    int VulkanDeviceManager::rateDeviceSuitability(VkPhysicalDevice device) const {
//        int score = 0;
//
//        // Obtain the properties of the physical device
//        VkPhysicalDeviceProperties deviceProperties;
//        vkGetPhysicalDeviceProperties(device, &deviceProperties);
//
//        // Discrete GPUs have a significant performance advantage
//        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
//            score += 1000;
//
//        // Obtain the features of the physical device
//        VkPhysicalDeviceFeatures deviceFeatures;
//        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
//
//        // Maximum possible size of textures affects graphics quality
//        score += deviceProperties.limits.maxImageDimension2D;
//
//        // Application can't function without geometry shaders
//        if (!deviceFeatures.geometryShader)
//            return 0; // If geometry shaders are not supported, return 0 (unsuitable)
//
//        return score;
//    }
//
//    bool VulkanDeviceManager::isDeviceSuitable(VkPhysicalDevice device) {
//        // Obtain the family queues indices
//        QueueFamilyIndices indices = findQueueFamilies(device);
//
//        bool extensionsSupported = checkDeviceExtensionSupport(device);
//
//        bool swapChainAdequate = false;
//        if (extensionsSupported) {
//            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
//            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
//        }
//
//        return indices.isComplete() && extensionsSupported && swapChainAdequate;
//    }
//
//    void VulkanDeviceManager::populateDeviceFeatures(VkDeviceCreateInfo& createInfo) {
//        // Set physical device features to default
//        VkPhysicalDeviceFeatures deviceFeatures{};
//
//        // Set the enabled physical device features
//        createInfo.pEnabledFeatures = &deviceFeatures;
//    }
//}