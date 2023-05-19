#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "UraniumApi.h"
#include "ApplicationProgram.h" 

#include "Graphics/UI/Cursor.h"
#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowProps.h"

#include "Scenes/SceneMaster.h"

#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

using namespace Uranium::Scenes;

using namespace Uranium::Core::Application;
using namespace Uranium::Input::Callbacks;

using namespace Uranium::Graphics::UI;
using namespace Uranium::Graphics::Display;

ApplicationProgram::ApplicationProgram() :
	cursor(nullptr),		
	window(nullptr),		
	sceneMaster(nullptr),		
	windowCallback(nullptr),
	cursorCallback(nullptr),
	mouseCallback(nullptr),	
	keyboardCallback(nullptr)
{

}

ApplicationProgram::~ApplicationProgram() {

}

void ApplicationProgram::setWindow(std::shared_ptr<Window> window) {
	this->window = window;
}

Cursor* ApplicationProgram::getCursor() {
	return cursor;
}

std::shared_ptr<Window> ApplicationProgram::getWindow() {
	return window;
}

SceneMaster* ApplicationProgram::getSceneMaster() {
	return sceneMaster;
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

void ApplicationProgram::initMembers() {
	
	// Create scene master
	sceneMaster = new SceneMaster();

	// Set custom pointer to GLFW window
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

void ApplicationProgram::disposeMembers() {

	delete sceneMaster;

	delete cursor;

	delete windowCallback;
	delete cursorCallback;
	delete mouseCallback;
	delete keyboardCallback;
}

void ApplicationProgram::pollEvents() {
	
	// update all callbacks
	windowCallback->updateCallbackEvent();
	cursorCallback->updateCallbackEvent();
	mouseCallback->updateCallbackEvent();
	keyboardCallback->updateCallbackEvent();

	// poll events
	glfwPollEvents();
}

void ApplicationProgram::updateProgram() {
	while (!window->hasClosed()) {
		// update scene master
		sceneMaster->update();

		// reset viewport
		if (windowCallback->hasResized())
			glViewport(0, 0, window->getProperties().getWidth(), window->getProperties().getHeight());

		// This will render the current scene linked
		// to the scene master. Any update from scene
		// to transition to another scene, will be 
		// handled in the update() of the scene
		sceneMaster->render();

		// post processing
		
		// swap buffers
		glfwSwapBuffers(*window);

		// update scene master after all has rendered
		sceneMaster->postUpdate();
		
		// poll events
		pollEvents();
	}
}
