#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "WindowHND.h"

namespace uranium::video::core {
	
	WindowHND::WindowHND() noexcept :
		visible     (true),
		resizable   (true),
		decorated   (true),
		alwaysOnTop (false),
		restored    (false),
		maximized   (false),
		minimized   (false),
		fullscreen  (false),
		opacity     (100),
		title       ("GLFW Window"),
		position    (0, 0),
		dimension   (MIN_WIDTH, MIN_HEIGHT),
		resolution  (MIN_WIDTH, MIN_HEIGHT),
		glfwWindow  (nullptr)
	{
		
	}

	WindowHND::~WindowHND() noexcept {
	
	}

	bool WindowHND::shouldClose() const {
		return false;
	}

	void WindowHND::setOpacity(unsigned int opacity) {
	
	}

	void WindowHND::setTitle(const std::string& title) {
	
	}

	void WindowHND::setPosition(const glm::ivec2& position) {
	
	}

	void WindowHND::setDimension(const glm::ivec2& dimension) {
	
	}

	void WindowHND::setResolution(const glm::ivec2& resolution) {
	
	}

	void WindowHND::setVisible(bool visible) {
	
	}

	void WindowHND::setResizable(bool resizable) {
	
	}

	void WindowHND::setDecorated(bool decorated) {
	
	}

	void WindowHND::setAlwaysOnTop(bool alwaysOnTop) {
	
	}

	void WindowHND::close() {
	
	}

	void WindowHND::focus() {
	
	}

	void WindowHND::requestAttention() {
	
	}

	void WindowHND::restore() {
	
	}
	
	void WindowHND::maximize() {
	
	}
	
	void WindowHND::minimize() {
	
	}

	void WindowHND::center(void* monitor) {
	
	}

	void WindowHND::setFullscreen(void* monitor) {
	
	}
}