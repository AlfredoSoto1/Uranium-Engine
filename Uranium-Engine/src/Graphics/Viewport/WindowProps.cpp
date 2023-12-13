#include <GL/glfw3.h>
#include <stdexcept>

#include "Window.h"
#include "WindowProps.h"

#include "Graphics/Display/Monitor.h"

using namespace Uranium::Graphics::Display;

namespace Uranium::Graphics::Viewport {

	WindowProps::WindowProps(Window* window) noexcept :
		window(window),
		title("Uranium-Engine Display"),
		position(0, 0),   
		dimension(MIN_WIDTH, MIN_HEIGHT),
		resolution(MIN_WIDTH, MIN_HEIGHT),
		opacity(100)
	{

	}

	auto WindowProps::getTitle() const->std::string {
		return title;
	}

	auto WindowProps::getPosition() const->glm::ivec2 {
		return position;
	}

	auto WindowProps::getDimension() const->glm::ivec2 {
		return dimension;
	}

	auto WindowProps::getResolution() const->glm::ivec2 {
		return resolution;
	}

	auto WindowProps::getOpacity() const -> unsigned int {
		return opacity;
	}

	void WindowProps::setTitle(const std::string& title) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		this->title = title;
		glfwSetWindowTitle(window->glWindow, title.c_str());
	}

	void WindowProps::setPosition(const glm::ivec2& position) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		glfwSetWindowPos(window->glWindow, position.x, position.y);
	}

	void WindowProps::setDimension(const glm::ivec2& dimension) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		glfwSetWindowSize(window->glWindow, dimension.x, dimension.y);
	}

	void WindowProps::setResolution(const glm::ivec2& resolution) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		this->resolution = resolution;
	}

	void WindowProps::setOpacity(unsigned int opacity) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		this->opacity = opacity >= 100 ? 100 : opacity <= 0 ? 0 : opacity;

		// if max opacity is achieved, dont make
		// the window transparent
		if (opacity == 100) return;

		glfwSetWindowAttrib(
			// Establish window attribute to be -> frame buffer
			window->glWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
			// Tell the frame buffer to become transparent
			// if and only if the opacity is lower than 100%
			opacity != 100 ? GLFW_TRUE : GLFW_FALSE
		);

		// Set the opacity of the window to be in a scale of [0, 100]
		glfwSetWindowOpacity(window->glWindow, opacity / 100.0f);
	}

	void WindowProps::center(std::unique_ptr<Monitor> monitor) {
#ifdef UR_DEBUG
		if (!window->glWindow)
			throw std::exception("GLFW window is not initialized");
#endif
		// if no monitor connected, throw exception
		if (!monitor->isConnected())
			throw std::invalid_argument("Provided monitor is not connected!");

		// If monitor is present but is maximized, minimized or fullscreen
		// there is no need to update the window position since
		// there is not going to be visible if any of these conditions happen
		if (window->states.isMaximized() || window->states.isMinimized() || window->states.isFullscreen())
			return;

		// calculate relative position retlative to center
		int newPositionX = (resolution.x - dimension.x) / 2;
		int newPositionY = (resolution.y - dimension.y) / 2;

		// set new position to Props. and update GLFW window
		position.x = newPositionX;
		position.y = newPositionY;
		glfwSetWindowPos(window->glWindow, newPositionX, newPositionY);
	}
}