#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include "Core/Logger.h"

#include "VulkanAPI.h"
#include "VulkanContext.h"

namespace Uranium::Platform::Vulkan {

	VulkanContext::VulkanContext(
        const VulkanAPI& vulkanAPI,
        const std::string& engineName,
        const std::string& applicationName,

        uint32_t appMajor,
        uint32_t appMinor,
        uint32_t appPatch,

        uint32_t engineMajor,
        uint32_t engineMinor,
        uint32_t enginePatch
        ) noexcept :
        vulkanAPI(vulkanAPI),
        engineName(engineName),
        applicationName(applicationName),

        appMajor(appMajor),
        appMinor(appMinor),
        appPatch(appPatch),

        engineMajor(engineMajor),
        engineMinor(engineMinor),
        enginePatch(enginePatch),

        instance(VK_NULL_HANDLE)
    {
    }

    VkInstance VulkanContext::getInstance() const noexcept {
        return instance;
    }

	void VulkanContext::create() {
        // Prepare the Vulkan Application information
        VkApplicationInfo appInfo = createVulkanApplication();

        // Prepare the instance information
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Prepare the validation layers if available
        // Prepare the extensions to be used
        populateValidationLayers(createInfo);
        populateRequiredExtensions(createInfo);

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
            Core::UR_INFO("[Vulkan]", "Vulkan instance created.");
        }
	}

    void VulkanContext::destroy() noexcept {
        if (instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
            instance = VK_NULL_HANDLE;
        }
        else {
            Core::UR_WARN("[Vulkan]", "Vulkan instance is already NULL.");
        }
	}

    void VulkanContext::catchLatestVersion() noexcept {
        // Use the VK_HEADER_VERSION macro to get the latest Vulkan version
        uint32_t latestVulkanVersion = VK_HEADER_VERSION;

        // Extract major, minor, and patch versions
        uint32_t major = VK_VERSION_MAJOR(latestVulkanVersion);
        uint32_t minor = VK_VERSION_MINOR(latestVulkanVersion);
        uint32_t patch = VK_VERSION_PATCH(latestVulkanVersion);

        Core::UR_INFO("[Vulkan]", "Version %d.%d.%d", major, minor, patch);
    }

    VkApplicationInfo VulkanContext::createVulkanApplication() noexcept {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

        // Set the application name & version
        appInfo.pApplicationName = applicationName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(appMajor, appMinor, appPatch);

        // Set the engine name & version
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(engineMajor, engineMinor, enginePatch);

        // TODO: make it so that it always grabs the latest version of vulkan supported by the driver
        appInfo.apiVersion = VK_API_VERSION_1_0;
        return appInfo;
    }

    void VulkanContext::populateValidationLayers(VkInstanceCreateInfo& createInfo) noexcept {
        if constexpr (VulkanAPI::validationLayerSupported) {
            VkDebugUtilsMessengerCreateInfoEXT debugInfo = vulkanAPI.getDebugMessengerCreateInfo();
            // Enable validation layers
            createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanAPI.validationLayers.size());
            createInfo.ppEnabledLayerNames = vulkanAPI.validationLayers.data();
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugInfo;
        }
        else {
            // Disable validation layers
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }
    }

    void VulkanContext::populateRequiredExtensions(VkInstanceCreateInfo& createInfo) noexcept {
        // Returns the required extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> requiredExtensions(glfwExtensionCount);

        for (uint32_t i = 0; i < glfwExtensionCount; i++)
            requiredExtensions.emplace_back(glfwExtensions[i]);

        // add more extensions here if needed in the future
        if constexpr (VulkanAPI::validationLayerSupported)
            requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        // Returns all the extensions that vulkan supports in *this* platform
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        // Log all the extensions that are required by the applicaiton
        // and the extensions available to use
        if constexpr (VulkanAPI::validationLayerSupported) {
            Core::UR_INFO("[Vulkan]", "Required extensions count [%d]", glfwExtensionCount);

            for (uint32_t i = 0; i < glfwExtensionCount; i++)
                Core::UR_TRACE("[Vulkan]", "Extension [%d]", requiredExtensions[i]);

            Core::UR_INFO("[Vulkan]", "Available extensions count [%d]", extensionCount);

            for (uint32_t i = 0; i < extensionCount; i++)
                Core::UR_TRACE("[Vulkan]", "Extension [%d]", extensions[i].extensionName);
        }

        createInfo.enabledExtensionCount = (uint32_t)(requiredExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    }
}