#include "Window.h"

namespace Uranium::Graphics::Display {

	Window::Window(const std::string& title, unsigned int width, unsigned int height) : 
		title(title),
		dimension(width, height), 
		position(0, 0),
		windowContext(nullptr),
		
		transparency(0),

		is_Visible(false),
		is_Resizable(false),
		is_Decorated(false),
		is_Fullscreen(false),
		is_AlwaysOnTop(false),

		is_Maximized(false),
		is_Minimized(false)
	{

	}

	Window::~Window() {

	}

	void Window::setTitle(const std::string& title) {
		this->title = title;
	}

	void Window::setSize(const Dimension& dimension) {
		this->dimension = dimension;
	}

	void Window::setPosition(const Position& position) {
		this->position = position;
	}

	void Window::setFullscreen(const Dimension& dimension) {
		
	}

	void Window::setVisible(bool isVisible) {
		
	}

	void Window::setResizable(bool isResizable) {
	
	}

	void Window::setDecorated(bool isDecorated) {
	
	}

	void Window::setAlwaysOnTop(bool isAlwaysOnTop) {
	
	}

	void Window::setTransparency(unsigned int transparency) {
	
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

	void Window::centerWindow() {

	}

	void Window::requestAttention() {

	}

	auto Window::getSize() -> Dimension {

	}

	auto Window::getPosition() -> Position {

	}

	unsigned int Window::getTransparency() {

	}

	bool Window::hasClosed() {
		
	}

	bool Window::isRestored() {
	
	}

	bool Window::isMaximized() {
	
	}

	bool Window::isMinimized() {
	
	}

	bool Window::isVisible() {
	
	}

	bool Window::isResizable() {
	
	}

	bool Window::isDecorated() {
	
	}

	bool Window::isFullscreen() {
	
	}

	bool Window::isAlwaysOnTop() {
	
	}

}