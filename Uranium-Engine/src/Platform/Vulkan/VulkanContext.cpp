#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Core/Logger.h"
#include "VulkanContext.h"

namespace Uranium::Platform::Vulkan {
	VulkanContext::VulkanContext(
		const std::string& engineName,
		const std::string& applicationName,

		uint32_t appMajor,
		uint32_t appMinor,
		uint32_t appPatch,

		uint32_t engineMajor,
		uint32_t engineMinor,
		uint32_t enginePatch
	) noexcept :
		Interface::UGraphicContext(
			engineName, 
			applicationName,

			appMajor, 
			appMinor, 
			appPatch,

			engineMajor,
			engineMinor,
			enginePatch
		),

        isDebugMessengerSupported(UR_ON_DEBUG_SWAP(true, false)),
        isValidationLayerSupported(UR_ON_DEBUG_SWAP(true, false))
	{
	}

	VulkanContext::~VulkanContext() noexcept {

	}

    VulkanContext::InstanceRef VulkanContext::getInstance() const noexcept {
        return instance;
    }

	void VulkanContext::createInstance() {
        using namespace Core;
        // Check if the vulkan context to be created supports vulkan validation layers.
        // If there is no validation layer that supports the device, continue running the
        // program. The application will throw warnings and possibly errors if any.
        // Validation layers can be skipped in UR_DEBUG configuration. They are completely
        // ignored in UR_RELEASE and UR_DISTRIBUTION configurations.
        UR_IF(validationLayerEnabled && !checkValidationLayerSupport(),
            isValidationLayerSupported = false;
            Core::UR_WARN("[Vulkan]", "Validation layers requested, but not available!");
        )

        // Prepare the Vulkan Application information
        VkApplicationInfo appInfo = createVulkanApplication();
        catchLatestVersion();

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

    void VulkanContext::disposeInstance() noexcept {

        UR_IF(validationLayerEnabled && isValidationLayerSupported,
            destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        )

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

        char versionString[256];
        std::sprintf(versionString, "Version: %d.%d.%d", major, minor, patch);
        Core::UR_INFO("[Vulkan]", versionString);
    }

    VkApplicationInfo VulkanContext::createVulkanApplication() {
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

	void VulkanContext::setupDebugConfigurations() noexcept {
        if (!validationLayerEnabled && !isValidationLayerSupported)
            return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo = getDebugMessengerCreateInfo();

        // Attempt to create the debug messenger
        if (createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            isDebugMessengerSupported = false;
            Core::UR_INFO("[Vulkan]", "Failed to set up debug messenger!");
        }
        else
            Core::UR_INFO("[Vulkan]", "Debug messenger setup successfull.");
	}

    bool VulkanContext::hasValidationLayerSupport() const noexcept {
        return isValidationLayerSupported;
    }

    bool VulkanContext::checkValidationLayerSupport() const noexcept {
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
                return false; // No Validation layer supported
        }
        // Validation layers are supported
        bool* validationSupported = const_cast<bool*>(&isValidationLayerSupported);
        *validationSupported = true;
        return true;
    }

    void VulkanContext::populateValidationLayers(VkInstanceCreateInfo& createInfo) {
        if (validationLayerEnabled && isValidationLayerSupported) {
            VkDebugUtilsMessengerCreateInfoEXT debugInfo = getDebugMessengerCreateInfo();
            // Enable validation layers
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugInfo;
        }
        else {
            // Disable validation layers
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }
    }

    VkDebugUtilsMessengerCreateInfoEXT VulkanContext::getDebugMessengerCreateInfo() noexcept {
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

    VkResult VulkanContext::createDebugUtilsMessengerEXT(
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

    void VulkanContext::destroyDebugUtilsMessengerEXT(
        VkInstance                   instance, 
        VkDebugUtilsMessengerEXT     debugMessenger, 
        const VkAllocationCallbacks* pAllocator
    ) 
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    void VulkanContext::populateRequiredExtensions(VkInstanceCreateInfo& createInfo) {
        // Returns the required extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> requiredExtensions(glfwExtensionCount);

        for (uint32_t i = 0; i < glfwExtensionCount; i++)
            requiredExtensions.emplace_back(glfwExtensions[i]);

        // add more extensions here if needed in the future
        if (validationLayerEnabled && isValidationLayerSupported)
            requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        // Returns all the extensions that vulkan supports in *this* platform
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        // Log all the extensions that are required by the applicaiton
        // and the extensions available to use
        UR_IF(validationLayerEnabled, {
            char req_ExtensionCount[256];
            std::sprintf(req_ExtensionCount, "Required extensions count [%d]", glfwExtensionCount);
            Core::UR_INFO("[Vulkan]", req_ExtensionCount);

            for (uint32_t i = 0; i < glfwExtensionCount; i++) {
                char req_extension[256];
                std::sprintf(req_extension, "Extension [%d]", requiredExtensions[i]);
                Core::UR_TRACE("[Vulkan]", req_ExtensionCount);
            }

            char ava_ExtensionCount[256];
            std::sprintf(ava_ExtensionCount, "Available extensions count [%d]", extensionCount);
            Core::UR_INFO("[Vulkan]", ava_ExtensionCount);

            for (uint32_t i = 0; i < extensionCount; i++) {
                char ava_extension[256];
                std::sprintf(ava_extension, "Extension [%d]", extensions[i].extensionName);
                Core::UR_TRACE("[Vulkan]", ava_extension);
            }
        })

        createInfo.enabledExtensionCount = (uint32_t)(requiredExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    }
}