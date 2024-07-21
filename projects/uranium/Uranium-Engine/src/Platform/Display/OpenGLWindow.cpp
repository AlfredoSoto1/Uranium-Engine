//#include <GLFW/glfw3.h>
//#include <exception>
//
//#include "OpenGLWindow.h"
//#include "Platform/Interface/Monitor.h"
//
//namespace Uranium::Platform::Display {
//
//	OpenGLWindow::OpenGLWindow() noexcept :
//		Window()
//	{
//
//	}
//
//	OpenGLWindow::~OpenGLWindow() {
//
//	}
//
//	void OpenGLWindow::setVisible(bool visible) {
//		modes.visible = visible;
//		if (visible)
//			glfwShowWindow(glWindow);
//		else
//			glfwHideWindow(glWindow);
//	}
//
//	void OpenGLWindow::setResizable(bool resizable) {
//		modes.resizable = resizable;
//		glfwSetWindowAttrib(glWindow, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
//	}
//
//	void OpenGLWindow::setDecorated(bool decorated) {
//		modes.decorated = decorated;
//		glfwSetWindowAttrib(glWindow, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
//	}
//
//	void OpenGLWindow::setAlwaysOnTop(bool alwaysOnTop) {
//		modes.alwaysOnTop = alwaysOnTop;
//		glfwSetWindowAttrib(glWindow, GLFW_FLOATING, alwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
//	}
//
//	void OpenGLWindow::restore() {
//		operation.restored = true;
//		operation.maximized = false;
//		operation.minimized = false;
//
//		// if the window is not in fullscreen mode, we
//		// can restore the window manually
//		if (!operation.fullscreen) {
//			glfwRestoreWindow(glWindow);
//			return;
//		}
//
//		// if the window is on fullscreen mode, we need to
//		// handle it in a different way...
//		operation.fullscreen = false;
//
//		// Get the current position of the window
//		// and keep track of the corresponding values
//		int xpos;
//		int ypos;
//		glfwGetWindowPos(glWindow, &xpos, &ypos);
//
//		// Update position without setting a new
//		// position with glfw internally
//		props.position.x = xpos;
//		props.position.y = ypos;
//
//		// return window to its default dimensions:
//		glfwSetWindowMonitor(
//			glWindow,
//			nullptr,                // current active monitor
//			xpos, ypos,             // position of the extended window
//			props.dimension.x,      // width of the window
//			props.dimension.y,      // height of the window
//			GLFW_DONT_CARE          // refreshrate in Hz
//		);
//	}
//
//	void OpenGLWindow::maximize() {
//		// if the window is already in fullscreen
//		// we don't need to maximize it
//		if (operation.fullscreen)
//			return;
//
//		operation.restored = false;
//		operation.maximized = true;
//		operation.minimized = false;
//
//		glfwMaximizeWindow(glWindow);
//	}
//
//	void OpenGLWindow::minimize() {
//		// if the window is on fullscreen we don't need
//		// to minimize it because the fullscreen mode takes
//		// posession of the entire display.
//		if (operation.fullscreen)
//			return;
//
//		operation.maximized = false;
//		operation.minimized = true;
//
//		glfwIconifyWindow(glWindow);
//	}
//
//	void OpenGLWindow::close() {
//		glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
//	}
//
//	void OpenGLWindow::focus() {
//		glfwFocusWindow(glWindow);
//	}
//
//	void OpenGLWindow::requestAttention() {
//		glfwRequestWindowAttention(glWindow);
//	}
//
//	void OpenGLWindow::center(MonitorRef monitor) {
//		// if no monitor connected, throw exception
//		if (!monitor->isConnected())
//			throw std::exception("Provided monitor is not connected!");
//
//		// If monitor is present but is maximized, minimized or fullscreen
//		// there is no need to update the window position since
//		// there is not going to be visible if any of these conditions happen
//		if (operation.maximized || operation.minimized || operation.fullscreen)
//			return;
//
//		// calculate relative position retlative to center
//		int newPositionX = (monitor->getResolution().x - props.dimension.x) / 2;
//		int newPositionY = (monitor->getResolution().y - props.dimension.y) / 2;
//
//		// set new position to Props. and update GLFW window
//		props.position.x = newPositionX;
//		props.position.y = newPositionY;
//		glfwSetWindowPos(glWindow, newPositionX, newPositionY);
//	}
//
//	void OpenGLWindow::setFullscreen(MonitorRef monitor) {
//		if (!monitor->isConnected())
//			throw std::exception("Provided monitor is not connected!");
//
//		operation.fullscreen = true;
//
//		// Make the window fullscreen with:
//		glfwSetWindowMonitor(
//			glWindow,
//			*monitor,            // current active monitor
//			0, 0,                // position of the extended window
//			props.resolution.x,  // width of the window
//			props.resolution.y,  // height of the window
//			GLFW_DONT_CARE       // refreshrate in Hz
//		);
//	}
//}