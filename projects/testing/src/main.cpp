// Basic Application Framework : 
//     Ensure you have a working setup to display something on screen.
// 
// Vulkan Setup : 
//     USE: https://vulkan-tutorial.com/
//     Focus on Vulkan initialization and basic rendering capabilities.
// 
// Custom Data Structures& Memory Management : 
//     Implement foundational components that your engine will rely on.
// 
// Basic Rendering Features : 
//     Get simple rendering up and running with shaders and scene management.
// 
// Entity - Component System : 
//     Add ECS to manage and render objects effectively.
// 
// Advanced Features & Optimizations : 
//     Enhance your engine with advanced features and performance improvements.

//import ModuleTestApp;

//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>
//
//#include <iostream>


//int main() {
//    //MyFunc({});
//
//    //glfwInit();
//
//    //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//    //GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
//
//    //uint32_t extensionCount = 0;
//    //vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//
//    //std::cout << extensionCount << " extensions supported\n";
//
//    //glm::mat4 matrix;
//    //glm::vec4 vec;
//    //auto test = matrix * vec;
//
//    //while (!glfwWindowShouldClose(window)) {
//    //    glfwPollEvents();
//    //}
//
//    //glfwDestroyWindow(window);
//
//    //glfwTerminate();
//
//    return 0;
//}

#include <core/URAPI.h>
#include <services/LogCalls.h>

import uranium.core;
import uranium.services;

//#include <core/Application.h>

using uranium::services::Logger;
using uranium::services::LogLevel;
using uranium::core::Application;

class MyApplication : UR_EXTENDS Application {
public:

	MyApplication() : Application() {

	}

	void init() noexcept {
		
	}
};

/*
* Definition of the default main function
* No arguments needed for starting the uranium app
*/
auto main() -> int {
	return Application::start(std::make_unique<MyApplication>());
}