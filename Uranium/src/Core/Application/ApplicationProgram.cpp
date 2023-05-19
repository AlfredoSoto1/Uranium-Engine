#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "UraniumApi.h"
#include "ApplicationProgram.h" 

#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowProps.h"

#include "Graphics/UI/Cursor.h"

#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

using namespace Uranium::Core::Application;
using namespace Uranium::Input::Callbacks;

using namespace Uranium::Graphics::UI;
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
	
	// set custom pointer to GLFW window
	glfwSetWindowUserPointer(*window, this);
	
	// Create new cursor
	cursor = new Cursor(window);

	// Initiate window Callbacks
	windowCallback = new WindowCallback(window);
	
	// Initate mouse & keyboard Callbacks
	mouseCallback = new MouseCallback(window);
	keyboardCallback = new KeyboardCallback(window);

	// Initiate cursor Callback
	cursorCallback = new CursorCallback(window);
}

void ApplicationProgram::disposeCallbacks() {

	delete cursor;

	delete windowCallback;
	delete cursorCallback;
	delete mouseCallback;
	delete keyboardCallback;
}

void ApplicationProgram::updateProgram() {
	while (!window->hasClosed()) {
		// update
		//appProgram->update();

		// reset viewport
		if (windowCallback->hasResized())
			glViewport(0, 0, window->getProperties().getWidth(), window->getProperties().getHeight());

		// draw
		//appProgram->draw();

		// post processing

		// swap buffers
		glfwSwapBuffers(*window);

		// post draw
		//appProgram->afterDraw();
		
		// 
		// update all callbacks
		//
		windowCallback->updateCallbackEvent();
		cursorCallback->updateCallbackEvent();
		mouseCallback->updateCallbackEvent();
		keyboardCallback->updateCallbackEvent();
		
		// poll events
		glfwPollEvents();
	}
}
