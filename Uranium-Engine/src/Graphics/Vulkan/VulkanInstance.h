#pragma once

#include <string>
#include <vector>

#include "VulkanValidation.h"

namespace Uranium::Graphics::Vulkan {

	class VulkanInstance final {
	public:
		VulkanInstance(const std::string& appName);
		~VulkanInstance();

	public:
		void create();

	private:
	
	private:
		VkInstance instance;

		VulkanValidation validation;
	};
}