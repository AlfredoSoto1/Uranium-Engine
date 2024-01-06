#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

#include "VulkanInstance.h"

namespace Uranium::Graphics::Vulkan {

	VulkanInstance::VulkanInstance(const std::string& appName)
    {

	}

	VulkanInstance::~VulkanInstance() {

	}

	void VulkanInstance::create() {

        if (validation.isValidationActive() && !validation.checkValidationLayerSupport())
            throw std::runtime_error("validation layers requested, but not available!");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = validation.getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (validation.isValidationActive()) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validation.getDefaultLayer().size());
            createInfo.ppEnabledLayerNames = validation.getDefaultLayer().data();

            validation.populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

		VkResult instanceCreationResult = vkCreateInstance(&createInfo, nullptr, &instance);

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
		}
	}

}