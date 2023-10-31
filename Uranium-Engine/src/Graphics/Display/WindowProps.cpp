#include <GLFW/glfw3.h>

#include "WindowProps.h"

namespace Uranium::Graphics::Display {

	WindowProps::WindowProps() :
		mayorGLVersion(3),
		minorGLVersion(3),

		glWindow(nullptr),

		title("Uranium Engine"),

		opacity(100),
		position(0, 0),
		dimension(MIN_WIDTH, MIN_HEIGHT),
		resolution(MIN_WIDTH, MIN_HEIGHT)
	{
	}

	void WindowProps::initDefault() const {
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, opacity < 100 ? GL_TRUE : GL_FALSE);
		//glfwWindowHint(GLFW_CENTER_CURSOR, true ? GL_TRUE : GL_FALSE);
	}

	void WindowProps::setGLVersion(unsigned int mayor, unsigned int minor) {
		this->mayorGLVersion = mayor;
		this->minorGLVersion = minor;
	}

	void WindowProps::setTitle(const std::string& title) {
		this->title = title;
		if (glWindow) glfwSetWindowTitle(glWindow, title.c_str());
	}

	void WindowProps::setOpacity(unsigned int opacity) {
		this->opacity = opacity;

		if (not glWindow or opacity == 100) return;

		glfwSetWindowAttrib(
			// Establish window attribute to be -> frame buffer
			glWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
			// Tell the frame buffer to become transparent
			// if and only if the opacity is lower than 100%
			opacity < 100 ? GLFW_TRUE : GLFW_FALSE
		);

		// Set the opacity of the window to be in a scale of [0, 100]
		glfwSetWindowOpacity(glWindow, opacity / 100.0f);
	}

	void WindowProps::setPosition(const Position& position) {
		this->position = position;

		if (not glWindow) return;

		glfwSetWindowPos(glWindow, position.x, position.y);
	}

	void WindowProps::setDimension(const Dimension& dimension) {
		this->dimension = dimension;

		if (not glWindow) return;

		glfwSetWindowSize(glWindow, dimension.width, dimension.height);
	}

	void WindowProps::setResolution(const Dimension& resolution) {
		this->resolution = resolution;
	}

	std::string WindowProps::getTitle() const {
		return title;
	}

	unsigned int WindowProps::getMayorGLVersion() const {
		return mayorGLVersion;
	}

	unsigned int WindowProps::getMinorGLVersion() const {
		return minorGLVersion;
	}

	inline unsigned int WindowProps::getOpacity() const {
		return opacity;
	}

	WindowProps::Position& WindowProps::getPosition() {
		return position;
	}

	WindowProps::Dimension& WindowProps::getDimension() {
		return dimension;
	}

	WindowProps::Dimension& WindowProps::getResolution() {
		return resolution;
	}
}