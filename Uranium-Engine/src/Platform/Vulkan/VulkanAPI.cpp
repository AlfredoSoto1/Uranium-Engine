#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include "Core/Logger.h"

#include "VulkanAPI.h"
#include "VulkanContext.h"
#include "VulkanDeviceManager.h"

#include "Platform/Interface/Window.h"

namespace Uranium::Platform::Vulkan {

    VulkanAPI::VulkanAPI(
        const std::string& engineName      = "Engine",
        const std::string& applicationName = "Vulkan-Application",

        uint32_t appMajor = 1,
        uint32_t appMinor = 0,
        uint32_t appPatch = 0,

        uint32_t engineMajor = 1,
        uint32_t engineMinor = 0,
        uint32_t enginePatch = 0
    ) noexcept :
        context(nullptr),
        deviceManager(nullptr),
        debugMessenger(VK_NULL_HANDLE)
    {
        context = std::make_unique<VulkanContext> (
            *this,
            engineName,
            applicationName,

            appMajor,
            appMinor,
            appPatch,

            engineMajor,
            engineMinor,
            enginePatch
        );

        deviceManager = std::make_unique<VulkanDeviceManager>(*this, *context);
    }

    void VulkanAPI::init() {
        //Check if vulkan is supported, if not use opengl
        //glfwVulkanSupported();

        // Check if the vulkan context to be created supports vulkan validation layers.
        // If there is no validation layer that supports the device, continue running the
        // program. The application will throw warnings and possibly errors if any.
        // Validation layers can be skipped in UR_DEBUG configuration. They are completely
        // ignored in UR_RELEASE and UR_DISTRIBUTION configurations.
        UR_IF(!checkValidationLayerSupport(),
            Core::UR_WARN("[Vulkan]", "Validation layers requested, but not available!");
        );
        
        context->catchLatestVersion();
        context->createInstance();

        setupDebugConfigurations();
    }

    void VulkanAPI::prepare() {
        deviceManager->setDeviceSurface(surface);

        deviceManager->pickPhysicalDevice();
        deviceManager->createLogicalDevice();
        deviceManager->obtainDeviceQueues();
    }

    void VulkanAPI::shutdown() noexcept {

        deviceManager->disposeDevice();

        if constexpr (VulkanAPI::validationLayerSupported)
            destroyDebugUtilsMessengerEXT(context->getInstance(), debugMessenger, nullptr);

        context->disposeInstance();
    }

    void VulkanAPI::createSurface(const Interface::Window& window) {
        if (glfwCreateWindowSurface(context->getInstance(), window, nullptr, &surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface!");
    }

    bool VulkanAPI::hasValidationLayerSupport() const noexcept {
        return VulkanAPI::validationLayerSupported;
    }

    void VulkanAPI::setupDebugConfigurations() {
        if constexpr (!VulkanAPI::validationLayerSupported)
            return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo = getDebugMessengerCreateInfo();

        // Attempt to create the debug messenger
        if (createDebugUtilsMessengerEXT(context->getInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
            throw std::runtime_error("Failed to set up debug messenger!");
        
        Core::UR_INFO("[Vulkan]", "Debug messenger setup successfull.");
    }

    bool VulkanAPI::checkValidationLayerSupport() const noexcept {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        // Obtain all the layer properties
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // Obtain validation layer flag reference
        bool* validationSupported = const_cast<bool*>(&VulkanAPI::validationLayerSupported);

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
            // No Validation layer supported
            if (!layerFound) {
                *validationSupported = false;
                return false;
            }
        }
        // Validation layers are supported
        *validationSupported = true;
        return true;
    }

    VkDebugUtilsMessengerCreateInfoEXT VulkanAPI::getDebugMessengerCreateInfo() const noexcept {
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
            VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT             messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void*                                       pUserData)
        {
            // Output the validation layer message to the standard error stream
            Core::UR_TRACE("[Vulkan Validation Layer]", pCallbackData->pMessage);

            // Check if the message severity is warning or higher
            if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                // Message is important enough to show
                // Log any information that is severly shown alot
                Core::UR_WARN("[Vulkan Validation Layer]", pCallbackData->pMessage);
            }

            // Return VK_FALSE to indicate that the Vulkan call that triggered the validation message
            // should be aborted if the message is of severity VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
            return VK_FALSE;
        };

        return debugCreateInfo;
    }

    VkResult VulkanAPI::createDebugUtilsMessengerEXT(
        VkInstance                                instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks*              pAllocator, 
        VkDebugUtilsMessengerEXT*                 pDebugMessenger
    ) const 
    {
        // Use vkGetInstanceProcAddr to get the function pointer for vkCreateDebugUtilsMessengerEXT
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            // Call the function if it's available
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);

        // Indicate that the extension is not present
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void VulkanAPI::destroyDebugUtilsMessengerEXT(
        VkInstance                   instance, 
        VkDebugUtilsMessengerEXT     debugMessenger, 
        const VkAllocationCallbacks* pAllocator
    ) const noexcept
    {
        if (instance == VK_NULL_HANDLE) {
            Core::UR_WARN("[Vulkan]", "Debug messenger extension could not be destroyed since the vulkan instance is NULL.");
            return;
        }
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }
}