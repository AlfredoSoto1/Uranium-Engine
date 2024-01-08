#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <set>
#include <map>
#include <iostream>
#include <stdexcept>
#include "VulkanContext.h"

namespace Uranium::Graphics::Vulkan {

	VulkanContext::VulkanContext(
        const std::string& engineName,
        const std::string& applicationName,
        // Application version
        uint32_t appMajor,
        uint32_t appMinor,
        uint32_t appPatch,
        // Engine version
        uint32_t engineMajor,
        uint32_t engineMinor,
        uint32_t enginePatch
    ) noexcept :
        engineName(engineName),
        applicationName(applicationName),
        appMajor(appMajor),
        appMinor(appMinor),
        appPatch(appPatch),
        engineMajor(engineMajor),
        engineMinor(engineMinor),
        enginePatch(enginePatch)
    {

	}

	VulkanContext::~VulkanContext() {

	}

	void VulkanContext::initialize() {
		createInstance();
		setupDebugMessenger();
		pickPhysicalDevice();
		createLogicalDevice();
	}

	void VulkanContext::cleanup() {

        if (device != VK_NULL_HANDLE) {
            vkDestroyDevice(device, nullptr);
            device = VK_NULL_HANDLE;
        }

        if constexpr(enableValidationLayers)
            destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

        if (instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
            instance = VK_NULL_HANDLE;
        }
	}

	VkInstance VulkanContext::getInstance() const {
        return instance;
	}

	VkDevice VulkanContext::getDevice() const {
        return device;
	}

    void VulkanContext::obtainLatestVulkanVersion() {
        // Use the VK_HEADER_VERSION macro to get the latest Vulkan version
        uint32_t latestVulkanVersion = VK_HEADER_VERSION;

        // Extract major, minor, and patch versions
        uint32_t major = VK_VERSION_MAJOR(latestVulkanVersion);
        uint32_t minor = VK_VERSION_MINOR(latestVulkanVersion);
        uint32_t patch = VK_VERSION_PATCH(latestVulkanVersion);

        // Output the latest Vulkan version
        if constexpr (enableValidationLayers)
            std::cout << "Latest Vulkan Version: " << major << "." << minor << "." << patch << std::endl;
    }

	void VulkanContext::createInstance() {
        // Prepare the Vulkan Application information
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan-Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        
        // TODO: make it so that it always grabs the latest version of vulkan supported by the driver
        appInfo.apiVersion = VK_API_VERSION_1_0;
        obtainLatestVulkanVersion();

        // Prepare the instance information
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Prepare the validation layers if running on debug mode
        // Prepare the extensions to be used
        prepareValidationLayers(createInfo);
        prepareRequiredExtensions(createInfo);

        // Check if the vulkan context to be created supports validation layers
        // if no layer is supported throw an exception. This validation can be skipped
        // if the validation layer flag is false. The first if statement is to guarantee
        // that the flag will be evaluated first always before te check.
        if constexpr (enableValidationLayers)
        if (!checkValidationLayerSupport())
            throw std::runtime_error("validation layers requested, but not available!");

        // Create a vulkan instance with the instance info
        VkResult instanceCreationResult = vkCreateInstance(&createInfo, nullptr, &instance);

        // Handle runtime errors after creating the instance
        switch (instanceCreationResult) {
        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("Instance failed creation!");
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("Instance failed creation, out of host memory!");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("Instance failed creation, out of device memory!");
        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("Instance failed creation, layer not present!");
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            throw std::runtime_error("Instance failed creation, extension not present!");
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            throw std::runtime_error("Instance failed creation, incompatible driver!");
        default:
            if constexpr (enableValidationLayers)
                std::cout << "Vulkan instance created" << std::endl;
        }
	}

	void VulkanContext::setupDebugMessenger() {
        if constexpr (!enableValidationLayers) return;

        // Retrieve the debug messenger creation info
        VkDebugUtilsMessengerCreateInfoEXT createInfo = getDebugMessengerCreateInfo();

        // Attempt to create the debug messenger
        if (createDebugUtilsMessengerEXT(instance, &getDebugMessengerCreateInfo(), nullptr, &debugMessenger) != VK_SUCCESS)
            throw std::runtime_error("failed to set up debug messenger!");
	}

	void VulkanContext::pickPhysicalDevice() {
        // Obtain all the GPU devices connected to the hardware
        std::vector<VkPhysicalDevice> devices = scanForPhysicalDevices();

        // If there is no device connected, there is no need to continue
        if (devices.empty())
            throw std::runtime_error("failed to find GPUs with Vulkan support!");

        // Use an ordered map to automatically sort candidates by increasing score
        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices) {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        VkPhysicalDevice deviceCandidate = VK_NULL_HANDLE;

        // Check if the best candidate is suitable at all
        // The last element of the ordered map has the highest score
        if (candidates.rbegin()->first > 0)
            deviceCandidate = candidates.rbegin()->second;
        else
            throw std::runtime_error("failed to find a suitable GPU!");

        // Check if the device candidate is suitable
        if (isDeviceSuitable(deviceCandidate))
            physicalDevice = deviceCandidate;

        if (physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("failed to find a suitable GPU!");
	}

	void VulkanContext::createLogicalDevice() {
        // Obtain the queue family indices
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        // Populate the required information for the device to be created
        populateDeviceFeatures(createInfo);
        populateDeviceExtensions(createInfo);
        populateQueueCreateInfos(indices, createInfo);

        if constexpr (enableValidationLayers) {
            // If the validation layers are enabled, pass the current validation layers
            // information to the logical device information struct to create.
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            // If no validation layers are enabled, just compile the following line:
            createInfo.enabledLayerCount = 0;
        }

        VkResult deviceCreationResult = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);

        // Handle runtime errors after creating the device
        switch (deviceCreationResult) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("Failed logical device creation, host out of memory!");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("Failed logical device creation, device out of memory!");
        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("Failed logical device creation, initialization failed!");
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            throw std::runtime_error("Failed logical device creation, extension not present!");
        case VK_ERROR_FEATURE_NOT_PRESENT:
            throw std::runtime_error("Failed logical device creation, device feature not present!");
        case VK_ERROR_TOO_MANY_OBJECTS:
            throw std::runtime_error("Failed logical device creation, too many objects!");
        case VK_ERROR_DEVICE_LOST:
            throw std::runtime_error("Failed logical device creation, device lost!");
        default:
            if constexpr (enableValidationLayers)
                std::cout << "Device object created." << std::endl;

            // Get the device queue for the graphics and present families
            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
        }
	}

    bool VulkanContext::checkValidationLayerSupport() const {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        // Obtain all the layer properties
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // For all the layers that this vulkan context support
        for (const char* layerName : validationLayers) {
            bool layerFound = false;
            // Check if the available layers from the driver support
            // the layers requrested from this vulkan context
            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) != 0)
                    continue;
                layerFound = true;
                break;
            }
            if (!layerFound)
                return false;
        }
        return true;
    }

    void VulkanContext::prepareRequiredExtensions(VkInstanceCreateInfo& createInfo) {
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

    void VulkanContext::prepareValidationLayers(VkInstanceCreateInfo& createInfo) {
        if constexpr (enableValidationLayers) {
            // Enable validation layers
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&getDebugMessengerCreateInfo();
        }
        else {
            // Disable validation layers
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }
    }

    auto VulkanContext::getDebugMessengerCreateInfo() -> VkDebugUtilsMessengerCreateInfoEXT {
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};

        // Set up the Vulkan Debug Utils Messenger creation info
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        // Specify the severity levels for which messages should be captured
        debugCreateInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | // Allow verbose messages
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | // Allow warnings
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;    // Allow errors

        // Specify the types of messages to capture
        debugCreateInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT    |  // Allow general messages
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |  // Allow validation messages
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;  // Allow performace-related messages

        // Set up the callback function to handle debug messages
        debugCreateInfo.pfnUserCallback = [](
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData)
        {
            // Output the validation layer message to the standard error stream
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
            
            // Check if the message severity is warning or higher
            if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                // Message is important enough to show
                // Log any information that is severly shown alot
            }

            // Return VK_FALSE to indicate that the Vulkan call that triggered the validation message
            // should be aborted if the message is of severity VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
            return VK_FALSE;
        };

        return debugCreateInfo;
    }

    VkResult VulkanContext::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) const {
        // Use vkGetInstanceProcAddr to get the function pointer for vkCreateDebugUtilsMessengerEXT
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            // Call the function if it's available
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);

        // Indicate that the extension is not present
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void VulkanContext::destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    std::vector<VkPhysicalDevice> VulkanContext::scanForPhysicalDevices() const {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
            return {}; // No devices available

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        return devices;
    }

    int VulkanContext::rateDeviceSuitability(VkPhysicalDevice device) const {
        int score = 0;

        // Obtain the properties of the physical device
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // Discrete GPUs have a significant performance advantage
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            score += 1000;

        // Obtain the features of the physical device
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        // Maximum possible size of textures affects graphics quality
        score += deviceProperties.limits.maxImageDimension2D;

        // Application can't function without geometry shaders
        if (!deviceFeatures.geometryShader)
            return 0; // If geometry shaders are not supported, return 0 (unsuitable)

        return score;
    }

    bool VulkanContext::isDeviceSuitable(VkPhysicalDevice device) {
        // Obtain the family queues indices
        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    VulkanContext::QueueFamilyIndices VulkanContext::findQueueFamilies(VkPhysicalDevice device) {
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

    bool VulkanContext::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
            requiredExtensions.erase(extension.extensionName);

        return requiredExtensions.empty();
    }

    void VulkanContext::populateQueueCreateInfos(const QueueFamilyIndices& indices, VkDeviceCreateInfo& createInfo) {
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

    void VulkanContext::populateDeviceFeatures(VkDeviceCreateInfo& createInfo) {
        // Set physical device features to default
        VkPhysicalDeviceFeatures deviceFeatures{};

        // Set the enabled physical device features
        createInfo.pEnabledFeatures = &deviceFeatures;
    }

    void VulkanContext::populateDeviceExtensions(VkDeviceCreateInfo& createInfo) {
        // Pass the device extension names
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    }
}