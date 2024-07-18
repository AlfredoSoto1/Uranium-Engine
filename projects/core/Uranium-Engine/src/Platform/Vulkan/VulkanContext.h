#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include "Core/CoreMacros.h"

namespace Uranium::Platform::Vulkan {

	UR_DECLARE VulkanAPI;

	URANIUM_API class VulkanContext final {
	public:
		/*
		* @param App-Name
		* @param Engine-Name
		* @param App-Version (mayor, minor, patch)
		* @param Engine-Version (mayor, minor, patch)
		*/
		explicit VulkanContext(
			const VulkanAPI& vulkanAPI,
			const std::string& engineName,
			const std::string& applicationName,

			uint32_t appMajor,
			uint32_t appMinor,
			uint32_t appPatch,

			uint32_t engineMajor,
			uint32_t engineMinor,
			uint32_t enginePatch
		) noexcept;

		~VulkanContext() noexcept = default;

	public:
		/*
		* @returns the instance in relation to the graphics API used
		*/
		VkInstance getInstance() const noexcept;
	
	public:
		/*
		* Creates a vulkan instance as main reference for the API.
		*/
		void create();

		/*
		* Destroys the vulkan instance and the context context.
		*/
		void destroy() noexcept;

		/*
		* Catches the latest Vulkan Version
		*/
		void catchLatestVersion() noexcept;
	
	private:
		/*
		* @returns Vulkan specific application information.
		*/
		VkApplicationInfo createVulkanApplication() noexcept;

		/*
		* Populates the validation layer information for the vulkan instance.
		* 
		* @param createInfo-ref
		*/
		void populateValidationLayers(VkInstanceCreateInfo& createInfo) noexcept;

		/*
		* Populates the required extensions information for the vulkan instance.
		*
		* @param createInfo-ref
		*/
		void populateRequiredExtensions(VkInstanceCreateInfo& createInfo) noexcept;

	private:
		// Engine name
		std::string engineName;
		// Application name
		std::string applicationName; 
		
		// Application version
		uint32_t appMajor;            
		uint32_t appMinor;           
		uint32_t appPatch;

		// Engine version		                              
		uint32_t engineMajor;        
		uint32_t engineMinor;        
		uint32_t enginePatch;        

		VkInstance instance;
		const VulkanAPI& vulkanAPI;
	};
}