#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "UraniumApi.h"
#include "ApplicationProgram.h"
#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowProps.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/WindowCallback.h"

using namespace Uranium::Core::Application;
using namespace Uranium::Input::Callbacks;
using namespace Uranium::Graphics::Display;

ApplicationProgram::ApplicationProgram() :
	cursor(nullptr),			 // 
	window(nullptr),			 // 
	windowCallback(nullptr),	 // Initializes all private members to null
	cursorCallback(nullptr),	 // 
	mouseCallback(nullptr),		 // 
	keyboardCallback(nullptr)	 // 
{

}

ApplicationProgram::~ApplicationProgram() {

}

void ApplicationProgram::setWindow(Window* window) {
	this->window = window;
}

UI::Cursor* ApplicationProgram::getCursor() {
	return cursor;
}

Window* ApplicationProgram::getWindow() {
	return window;
}

WindowCallback* ApplicationProgram::getWindowCallback() {
	return windowCallback;
}

CursorCallback* ApplicationProgram::getCursorCallback() {
	return cursorCallback;
}

MouseCallback* ApplicationProgram::getMouseCallback() {
	return mouseCallback;
}

KeyboardCallback* ApplicationProgram::getKeyboardCallback() {
	return keyboardCallback;
}

bool ApplicationProgram::hasWindow() {
	return window != nullptr;
}

void ApplicationProgram::createCallbacks() {
	
	// Initiate window Callbacks
	windowCallback = new WindowCallback(window);

}

void ApplicationProgram::createComponents() {

	// set custom pointer to GLFW window
	glfwSetWindowUserPointer(*window, this);
}

void ApplicationProgram::disposeCallbacks() {
	delete windowCallback;
	delete cursorCallback;
	delete mouseCallback;
	delete keyboardCallback;
}

void ApplicationProgram::disposeComponents() {
	delete cursor;
	delete window;
}

void ApplicationProgram::updateProgram() {
	while (!window->hasClosed()) {
		// update
		//appProgram->update();
		// reset viewport
		if (windowCallback->hasResized()) {
			print_status("resized");
			glViewport(0, 0, window->getProperties().getWidth(), window->getProperties().getHeight());
		}

		// draw
		//appProgram->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(*window);

		// post draw
		windowCallback->has_Resized = false;
		//appProgram->afterDraw();

		// poll events
		glfwPollEvents();

		//mouseCallback->update();
		//keyboardCallback->update();
	}
	// closes the application
	//appProgram->dispose();

	// disposes everything after application has ended
	window->dispose();
}
