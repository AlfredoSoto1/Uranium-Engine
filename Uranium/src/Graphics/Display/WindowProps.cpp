#include "WindowProps.h"
#include "Monitor.h"
#include "Window.h"

#include <GLFW/glfw3.h>

using namespace Uranium::Graphics::Display;

WindowProps::WindowProps(const std::string& title, unsigned int width, unsigned int height) :
	title(title),
	width(width),
	height(height),
	xPosition(),
	yPosition(),
	is_Visible(true),
	is_Resizable(true),
	is_Decorated(true),
	is_Fullscreen(false),
	is_AlwaysOnTop(false),	
	is_Maximized(false),
	is_Minimized(false),

	transparency(100), // max value - no transparency

	mayorGLVersion(4), // Latest OpenGL version
	minorGLVersion(6)
{

}

WindowProps::~WindowProps() {

}

void WindowProps::setContext(Window* windowContext) {
	this->windowContext = windowContext;
}

void WindowProps::setTitle(const std::string& title) {
	this->title = title;
	if (*windowContext) glfwSetWindowTitle(*windowContext, title.c_str());
}

void WindowProps::setOpenGLVersion(unsigned int mayor, unsigned int minor) {
	this->mayorGLVersion = mayor;
	this->minorGLVersion = minor;
}

void WindowProps::setSize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
}

void WindowProps::setPosition(int xpos, int ypos) {
	this->xPosition = xpos;
	this->yPosition = ypos;
}

void WindowProps::setWindowTransparency(unsigned int transparency) {
	this->transparency = transparency;
	if (*windowContext != nullptr) return;
	glfwSetWindowAttrib(*windowContext, GLFW_TRANSPARENT_FRAMEBUFFER, transparency < 100 ? GLFW_TRUE : GLFW_FALSE);
	glfwSetWindowOpacity(*windowContext, transparency / 1.0f);
}

void WindowProps::setVisible(bool isVisible) {
	this->is_Visible = isVisible;
	if (*windowContext == nullptr) return;
	if (is_Visible)
		glfwShowWindow(*windowContext);
	else
		glfwHideWindow(*windowContext);
}

void WindowProps::setResizable(bool isResizable) {
	this->is_Resizable = isResizable;
	if (*windowContext) glfwSetWindowAttrib(*windowContext, GLFW_RESIZABLE, is_Resizable ? GLFW_TRUE : GLFW_FALSE);
}

void WindowProps::setDecorated(bool isDecorated) {
	this->is_Decorated = isDecorated;
	if (*windowContext) glfwSetWindowAttrib(*windowContext, GLFW_DECORATED, is_Decorated ? GLFW_TRUE : GLFW_FALSE);
}

void WindowProps::setAlwaysOnTop(bool isAlwaysOnTop) {
	this->is_AlwaysOnTop = isAlwaysOnTop;
	if (*windowContext) glfwSetWindowAttrib(*windowContext, GLFW_FLOATING, is_AlwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
}

std::string WindowProps::getTitle() {
	return title;
}

unsigned int WindowProps::getWindowTransparency() {
	return transparency;
}

void WindowProps::getSize(unsigned int& width, unsigned int& height) {
	width = this->width;
	height = this->height;
}

void WindowProps::getPosition(int& xpos, int& ypos) {
	xpos = this->xPosition;
	ypos = this->yPosition;
}

void WindowProps::getOpenGlVersion(unsigned int& mayor, unsigned int& minor) {
	mayor = this->mayorGLVersion;
	minor = this->minorGLVersion;
}


bool WindowProps::isRestored() {
	return !is_Minimized && !is_Maximized;
}

bool WindowProps::isMaximized() {
	return is_Maximized;
}

bool WindowProps::isMinimized() {
	return is_Minimized;
}

bool WindowProps::isVisible() {
	return is_Visible;
}

bool WindowProps::isResizable() {
	return is_Resizable;
}

bool WindowProps::isDecorated() {
	return is_Decorated;
}

bool WindowProps::isFullscreen() {
	return is_Fullscreen;
}

bool WindowProps::isAlwaysOnTop() {
	return is_AlwaysOnTop;
}
