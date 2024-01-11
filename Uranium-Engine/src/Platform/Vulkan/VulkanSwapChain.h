#pragma once

#include <vector>

#include "Core/CoreMacros.h"

namespace Uranium::Platform::Vulkan {

	UR_DECLARE VulkanAPI;
	UR_DECLARE VulkanContext;

	URANIUM_API class VulkanSwapChain final {
	public:
		explicit VulkanSwapChain(const VulkanAPI& vulkanAPI, const VulkanContext& context) noexcept;

		~VulkanSwapChain() noexcept = default;

	public:
		void create();
		void dispose() noexcept;

	private:
		const VulkanAPI& vulkanAPI;
		const VulkanContext& context;

		VkSurfaceKHR surfaceRef;
	};
}