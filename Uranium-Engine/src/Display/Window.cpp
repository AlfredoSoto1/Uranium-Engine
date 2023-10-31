#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>

import Uranium.Display.Window;

namespace Uranium::Display {

	Window::Window() :
		/*
		* Volatile members
		*/
		hasCreated(false),

		/*
		* Window properties
		*/
		glWindow(nullptr),

		title("Default Window"),

		position(0, 0),
		dimension(MIN_WIDTH, MIN_HEIGHT),
		resolution(MIN_WIDTH, MIN_HEIGHT),

		opacity(100),

		// These are the minimum versions
		// of OpenGL that this application can
		// support by default
		glMajor(3),
		glMinor(3),

		/*
		* Window modes
		*/
		visible(true),
		resizable(true),
		decorated(true),
		fullscreen(false),
		alwaysOnTop(false),

		maximized(false),
		minimized(false)
	{
		// Prepare default GLFW window hints before creating
		glfwDefaultWindowHints();

		// First prepare the GLFW hints before
		// creating a window context.
		// This is so the window to be created,
		// can adopt all hints given before its creation

		// Set OpenGL version (optional, but recommended)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

		prepareDefaultHints();

		// Create a GLFW window with the given parameters
		//glWindow = glfwCreateWindow(dimension.x, dimension.y, title.c_str(), nullptr, nullptr);

		if (!glWindow)
			throw std::exception("[Exception]: Failed to create window display");

		hasCreated = true;

		//glfwSetWindowUserPointer(glWindow, this);

		// Provide the corresponding values to the hints
		// declared before window creation after the window
		// has initialized correctly.

		// set resize window limits if and only if its resizable
		//if (resizable)
		//	glfwSetWindowSizeLimits(glWindow, Window::MIN_WIDTH, Window::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

		// set window minimized / maximized if it was a Property setted before
		if (minimized)
			minimize();
		else if (maximized)
			maximize();

		// Update the window Opacity with the established
		// value before window context creation
		setOpacity(opacity);

		// Display the window
		//glfwShowWindow(glWindow);
	}

	Window::~Window() {
		if (!glWindow) return;
			
		// Hide the current visible window
		// and free all resources used for
		// generating *this* window instance
		//glfwHideWindow(glWindow);
		//glfwDestroyWindow(glWindow);
	}

	bool Window::isCurrent() const {
		return false;
	}

	bool Window::shouldClose() const {
		return false;
	}

	void Window::close() {

	}

	void Window::focus() {

	}

	void Window::restore() {

	}

	void Window::maximize() {

	}

	void Window::minimize() {

	}

	void Window::requestAttention() {

	}

	void Window::setTitle(const std::string& title) {
		this->title = title;
	}

	void Window::setOpacity(unsigned int opacity) {
		this->opacity = opacity;
	}

	void Window::setPosition(const glm::ivec2& position) {
		this->position = position;
	}

	void Window::setDimension(const glm::ivec2& dimension) {
		this->dimension = dimension;
	}

	void Window::setResolution(const glm::ivec2& resolution) {
		this->resolution = resolution;
	}

	void Window::setVisible(bool visible) {
		this->visible = visible;
	}

	void Window::setResizable(bool resizable) {
		this->resizable = resizable;
	}

	void Window::setDecorated(bool decorated) {
		this->decorated = decorated;
	}

	void Window::setAlwaysOnTop(bool alwaysOnTop) {
		this->alwaysOnTop = alwaysOnTop;
	}

	void Window::prepareDefaultHints() const {
		glfwWindowHint(GLFW_VISIBLE,   visible     ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, decorated   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_FLOATING,  alwaysOnTop ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, maximized   ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, resizable   ? GL_TRUE : GL_FALSE);

		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, opacity < 100 ? GL_TRUE : GL_FALSE);
		//glfwWindowHint(GLFW_CENTER_CURSOR, true ? GL_TRUE : GL_FALSE);

		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	}
}