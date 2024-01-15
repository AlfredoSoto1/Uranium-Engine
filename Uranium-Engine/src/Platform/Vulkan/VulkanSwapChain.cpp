#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <limits>    // Necessary for std::numeric_limits
#include <cstdint>   // Necessary for uint32_t
#include <algorithm> // Necessary for std::clamp
#include <stdexcept>
#include "Core/Logger.h"

#include "VulkanAPI.h"
#include "VulkanStructs.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

namespace Uranium::Platform::Vulkan {

    VulkanSwapChain::VulkanSwapChain(const VulkanAPI& vulkanAPI) noexcept :
        vulkanAPI(vulkanAPI)
    {

    }

    void VulkanSwapChain::setVSync(bool enabled) noexcept {
        this->vSyncEnabled = enabled;
    }

    void VulkanSwapChain::create() {
        SwapChainSupportDetails swapChainSupport = vulkanAPI.deviceManager->getSwapChainSupportDetails();

        // Choose the Color formats to present on the surface
        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);

        // Choose how the frames should be presented, with VSync or not
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);

        // Choose the correct resolution of the updated framebuffer from the window
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        // Images present in the swapchain to swap between every frame
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        // Clamp the image count to stay between the minimum and the maximum
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
            imageCount = swapChainSupport.capabilities.maxImageCount;

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

        populateSwapchainCreateInfo(createInfo);

        createInfo.surface = vulkanAPI.surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const DeviceQueueFamilyIndices& indices = vulkanAPI.deviceManager->getQueueFamilies();
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr; 
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        //createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult result = vkCreateSwapchainKHR(vulkanAPI.deviceManager->getDevice(), &createInfo, nullptr, &swapChain);

        // Handle runtime errors after creating the device
        switch (result) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, host out of memory!");
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, device out of memory!");
        case VK_ERROR_DEVICE_LOST:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, device lost!");
        case VK_ERROR_SURFACE_LOST_KHR:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, surface lost!");
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, native window in use!");
        case VK_ERROR_INITIALIZATION_FAILED:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, initialization failed!");
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
            swapChain = VK_NULL_HANDLE;
            throw std::runtime_error("Failed to create swap chain, compression exhausted!");
        }

        vkGetSwapchainImagesKHR(vulkanAPI.deviceManager->getDevice(), swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(vulkanAPI.deviceManager->getDevice(), swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void VulkanSwapChain::destroy() noexcept {
        if (swapChain == VK_NULL_HANDLE) { 
            vkDestroySwapchainKHR(vulkanAPI.deviceManager->getDevice(), swapChain, nullptr);
            swapChain = VK_NULL_HANDLE;
        }
        else
            Core::UR_WARN("[Vulkan]", "Failed to dispose swap chain reference since it was already NULL.");
    }

    VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept {
        for (const auto& availableFormat : availableFormats)
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;

        return availableFormats[0];
    }

    VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept {
        // If V-Sync is enabled, prioritize VK_PRESENT_MODE_MAILBOX_KHR
        if (vSyncEnabled)
            for (const auto& availablePresentMode : availablePresentModes)
                if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                    return availablePresentMode;

        // If VK_PRESENT_MODE_MAILBOX_KHR is not available or V-Sync is disabled, use VK_PRESENT_MODE_IMMEDIATE_KHR
        for (const auto& availablePresentMode : availablePresentModes)
            if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
                return availablePresentMode;

        // Fallback to a standard mode if neither VK_PRESENT_MODE_MAILBOX_KHR nor VK_PRESENT_MODE_IMMEDIATE_KHR is available
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
            return capabilities.currentExtent;

        // obtain from application events
        int width, height;
        //glfwGetFramebufferSize(window, &width, &height); // TODO

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width  = std::clamp(actualExtent.width,  capabilities.minImageExtent.width,  capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void VulkanSwapChain::populateSwapchainCreateInfo(VkSwapchainCreateInfoKHR& createInfo) noexcept {
        
    }
}