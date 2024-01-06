#pragma once

#include <vector>

namespace Uranium::Graphics::Vulkan {

	class VulkanValidation final {
	public:
		explicit VulkanValidation() noexcept;
		
		~VulkanValidation();

	public:
		using ExtensionName = const char*;
		using ValidationLayerName = const char*;
		
		/*
		* Returns true if there is support for layer validation
		*/
		bool checkValidationLayerSupport() const;

		/*
		* Returns true if the validation layers are enabled for debug
		*/
		bool isValidationActive() const;

		/*
		* Enables the validation layers for vulkan
		*/
		void enableValidation(bool enableValidationLayers);

		/*
		* Returns a list of all extensions required
		*/
		std::vector<ExtensionName> getRequiredExtensions() const;

		/*
		* Returns the default validation layer names
		*/
		const std::vector<ValidationLayerName>& getDefaultLayer() const;

		/*
		*/
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	private:
		/*
		* Default validation layer
		*/
		const std::vector<ValidationLayerName> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		bool enableValidationLayers;
	};
}