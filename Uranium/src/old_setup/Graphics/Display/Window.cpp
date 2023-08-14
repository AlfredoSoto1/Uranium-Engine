#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Monitor.h"
#include "WindowProps.h"

#include "Core/Application/UraniumApi.h"
#include "Core/Application/Application.h"
#include "Core/Application/ApplicationProgram.h"

#include "Input/Callbacks/WindowCallback.h"

using namespace Uranium::Core::Application;
using namespace Uranium::Graphics::Display;

Window::Window(const std::string& title, unsigned int width, unsigned int height) :
	window(nullptr),
	windowProps(nullptr),
	monitor(nullptr),
	hasFailed(false),
	hasDisposed(false)
{
	/*
	* Check conditions that verify if window can be created
	* in current context.
	*/
	if (Application::get() == nullptr) {
		print_warning(hasFailed = true, "Window cannot be initialized if there is not and Application");
		return;
	}

	if (!Application::get()->hasProgramInitiated()) {
		print_warning(hasFailed = true, "Window cannot be initialized if the GLFW lib. is not initialized");
		return;
	}

	windowProps = new WindowProps(title, width,height);
	windowProps->setContext(this);
}

Window::~Window() {

	// check flag before continuing
	if (hasDisposed)
		return;

	if (hasFailed)
		return;
	/*
	* dispose window content
	* if and only if, the 
	* dispose() method has never
	* been called.
	*/
	dispose();
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

bool Window::hasClosed() {
	
	// throw error in case has no context
	throw_error(!window, "'this' window has no GLFW context.");

	// return in built glfw flag
	return glfwWindowShouldClose(window);
}

bool Window::failedOnCreation() {
	return hasFailed;
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

void Window::init() {

	// Load GLFW hints
	prepareWindowHints();

	// Create GLFW window object
	createWindow();

	if (!window) {
		print_warning(hasFailed = true, "Failed to create GLFW window");
		return;
	}

	// Load GLFW Context-Dependent hints
	prepareContextHints();

	/*
	*  Set context to be current in this thread
	*  and prepare GLEW and all render related stuff
	*  (non window GLFW related)
	*/
	glfwMakeContextCurrent(window);
	glfwShowWindow(window);

	glfwSwapInterval(0); // set to max FPS TEMP

	if (glewInit() != GLEW_OK) {
		print_warning(hasFailed = true, "Failed to initiate GLEW.");
		// dispose if error occours 
		dispose();
		return;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	glViewport(0, 0, windowProps->width, windowProps->height);
}

void Window::focus() {

	// throw error in case has no context
	throw_error(!window, "'this' window has no GLFW context.");

	// focus window
	glfwFocusWindow(window);
}

void Window::close() {

	// throw error in case has no context
	throw_error(!window, "'this' window has no GLFW context.");
	
	// update glfw close flag
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::dispose() {

	// throw possible errors
	throw_error(!window, "Cannot dispose on a window out of context.");
	throw_error(hasDisposed, "Cannot dispose on a window that has already been disposed.");

	// free window props
	delete windowProps;

	// destroy window context
	glfwDestroyWindow(window);

	// update flag
	hasDisposed = true;
}

void Window::requestAttention() {
	// throw error if window == nullptr
	throw_error(!window, "'this' window has no GLFW context.");

	// request attention by glfw
	glfwRequestWindowAttention(window);
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
		// Return window to its regular state
		glfwSetWindowMonitor(window, 0, xpos, ypos, windowProps->width, windowProps->height, 0);
	}

	// 
	// get application program reference
	// through glfw user pointer
	// 
	ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));

	if (program == nullptr)
		return;

	// update has_Resized flag from window callback
	program->windowCallback->has_Resized = true;
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
