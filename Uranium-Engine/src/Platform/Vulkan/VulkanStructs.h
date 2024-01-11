#pragma once

#include "Core/CoreMacros.h"

namespace Uranium::Platform::Vulkan {

    URANIUM_API struct DeviceQueueFamilyIndices final {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> computeFamily;  // TODO in the future add support
        std::optional<uint32_t> transferFamily; // TODO in the future add support

        /*
        * Returns true if the graphics and present queues
        * are present in both optionals
        */
        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    URANIUM_API struct DeviceRequirements final {
        // Provide requirements
    };

    URANIUM_API struct DeviceSwapChainSupportDetails final {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
}