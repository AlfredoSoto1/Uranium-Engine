#pragma once

#include <vector>
#include "Core/CoreMacros.h"

namespace Uranium::Platform::Vulkan {

	UR_DECLARE VulkanAPI;
	UR_DECLARE VulkanContext;

	URANIUM_API class VulkanSwapChain final {
	public:
		explicit VulkanSwapChain(const VulkanAPI& vulkanAPI) noexcept;

		~VulkanSwapChain() noexcept = default;

	public:
		void create();
		void destroy() noexcept;

		void setVSync(bool enabled) noexcept;

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void populateSwapchainCreateInfo(VkSwapchainCreateInfoKHR& createInfo) noexcept;

	private:
		const VulkanAPI& vulkanAPI;
		bool vSyncEnabled;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;

		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
	};
}