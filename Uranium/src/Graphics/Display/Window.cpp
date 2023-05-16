#include "Window.h"

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Monitor.h"
#include "WindowProps.h"

#include "Input/WindowCallback.h"

using namespace Uranium::Input;
using namespace Uranium::Graphics::Display;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

Window::Window(const std::string& title, unsigned int width, unsigned int height) :
	window(nullptr),
	monitor(nullptr)
{
	windowProps = new WindowProps(title, width,height);
	windowProps->setContext(this);
}

Window::~Window() {

	if(callback != nullptr)
		delete callback;
	
	delete windowProps;

	if (!window)
		return;

	glfwDestroyWindow(window);
}

Window::operator GLFWwindow* () {
	return window;
}

void Window::setMonitor(std::shared_ptr<Monitor> monitor) {
	this->monitor = monitor;
}

std::shared_ptr<Monitor> Window::getMonitor() {
	return monitor;
}

WindowProps& Window::getProperties() {
	return *windowProps;
}

void Window::prepareWindowGLVersion() {
	unsigned int mayor;
	unsigned int minor;

	windowProps->getOpenGlVersion(mayor, minor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mayor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
}

void Window::prepareWindowHints() {

	// set glfw to its default hint settings
	glfwDefaultWindowHints();

	// set the version of OpenGl that the program will use
	prepareWindowGLVersion();
	
	//Prepare Window Hits before launch
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE,					windowProps->isVisible()					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_DECORATED,					windowProps->isDecorated()					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_FLOATING,					windowProps->isAlwaysOnTop()				? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED,					windowProps->isMaximized()					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE,					windowProps->isResizable()					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,	windowProps->getWindowTransparency() < 100	? GL_TRUE : GL_FALSE);
	//glfwWindowHint(GLFW_CENTER_CURSOR,				is_CursorCentered				? GL_TRUE : GL_FALSE);

	// set default monitor to launch window
	if(monitor == nullptr)
		monitor = Monitor::getPrimaryMonitor();
}

void Window::prepareContextHints() {
	// set resize window limits if and only if its resizable
	if (windowProps->isResizable())
		glfwSetWindowSizeLimits(window, WindowProps::MIN_WIDTH, WindowProps::MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

	// set window minimized / maximized if it was a Property setted before
	if (windowProps->isMinimized())
		minimize();
	else if (windowProps->isMaximized())
		maximize();

	// set window transparency if it was a Property setted before
	if (windowProps->getWindowTransparency() < 100)
		windowProps->setWindowTransparency(windowProps->getWindowTransparency());
}

void Window::createWindow() {
	// get monitor reference
	GLFWmonitor* activeMonitor = windowProps->isFullscreen() ? monitor.get()->operator GLFWmonitor *() : nullptr;

	// create window with all given constraints
	window = glfwCreateWindow(windowProps->width, windowProps->height, windowProps->getTitle().c_str(), activeMonitor, nullptr);
}

bool Window::init() {
	if (!glfwInit()) {
		std::cerr << "Failed to initiate GLFW" << std::endl;
		return false;
	}

	// set default GLFW error callback
	glfwSetErrorCallback(&error_callback);

	// Load GLFW hints
	prepareWindowHints();

	// Create GLFW window object
	createWindow();

	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	/// 
	/// Load GLFW Context-Dependent hints
	/// 
	prepareContextHints();

	/// 
	/// Set context to be current in this thread
	/// and prepare GLEW and all render related stuff
	/// (non window GLFW related)
	/// 
	glfwMakeContextCurrent(window);
	glfwShowWindow(window);

	glfwSwapInterval(0); // set to max FPS TEMP

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initiate GLEW." << std::endl;
		return false;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	glViewport(0, 0, windowProps->width, windowProps->height);

	// Initiate window Callbacks
	callback = new WindowCallback(this);

	// set custom pointer to GLFW remember in context
	//glfwSetWindowUserPointer(getWindow(), this);
	return true;
}

void Window::run() {
	while (!glfwWindowShouldClose(window)) {
		// update
		//appProgram->update();
		// reset viewport
		if (callback->hasResized()) {
			glViewport(0, 0, windowProps->width, windowProps->height);
		}

		// draw
		//appProgram->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(window);

		// post draw
		callback->has_Resized = false;
		//appProgram->afterDraw();

		// poll events
		glfwPollEvents();

		//mouse->update();
		//keyboard->update();
	}
	// closes the application
	//appProgram->dispose();

	// disposes everything after application has ended
	dispose();
}

void Window::exit(int errorCode) {
}

void Window::dispose() {
	glfwDestroyWindow(window);

	glfwTerminate();
}

void Window::focus() {
	if (window) glfwFocusWindow(window);
	else std::cerr << "'this' window has no GLFW context." << std::endl;
}

void Window::close() {
	if (window) glfwSetWindowShouldClose(window, GLFW_TRUE);
	else std::cerr << "'this' window has no GLFW context." << std::endl;
}

void Window::requestAttention() {
	if (window) glfwRequestWindowAttention(window);
	else std::cerr << "'this' window has no GLFW context." << std::endl;
}

void Window::restore() {
	windowProps->is_Maximized = false;
	windowProps->is_Minimized = false;
	if (window) glfwRestoreWindow(window);
}

void Window::maximize() {
	windowProps->is_Maximized = true;
	windowProps->is_Minimized = false;
	if (window) glfwMaximizeWindow(window);
}

void Window::minimize() {
	windowProps->is_Maximized = false;
	windowProps->is_Minimized = true;
	if (window) glfwIconifyWindow(window);
}


void Window::fullscreen(unsigned int width, unsigned int height) {

	// toggle fullscreen flag
	windowProps->is_Fullscreen = !windowProps->is_Fullscreen;

	if (window == nullptr || monitor == nullptr) return;

	int xpos;
	int ypos;
	// get current window position
	glfwGetWindowPos(window, &xpos, &ypos);
	// remember old position before making fullscreen
	windowProps->setPosition(xpos, ypos);

	if (windowProps->is_Fullscreen) {
		Monitor* activeMonitor = monitor.get();
		// make window fullscreen
		glfwSetWindowMonitor(window, activeMonitor->operator GLFWmonitor * (), 0, 0, width, height, 0);//have to put monitor scale
	}
	else {
		glfwSetWindowMonitor(window, 0, xpos, ypos, windowProps->width, windowProps->height, 0);
	}
	callback->has_Resized = true;
}

void Window::centerWindow() {

	// do nothing if...
	if (window == nullptr || monitor == nullptr || windowProps->is_Maximized || windowProps->is_Minimized) return;

	// calculate relative position retlative to center
	int newPositionX = (monitor->getWidth() - windowProps->width) / 2;
	int newPositionY = (monitor->getHeight() - windowProps->height) / 2;

	// set new position to Props. and update GLFW window
	windowProps->setPosition(newPositionX, newPositionY);
	glfwSetWindowPos(window, newPositionX, newPositionY);
}
