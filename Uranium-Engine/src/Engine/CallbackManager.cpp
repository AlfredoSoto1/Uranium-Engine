#include "CallbackManager.h"

#include "Input/Callbacks/WindowCallback.h"
#include "Input/Callbacks/MonitorCallback.h"

#include "Input/Callbacks/MouseCallback.h"
#include "Input/Callbacks/CursorCallback.h"
#include "Input/Callbacks/KeyboardCallback.h"

namespace Uranium::Engine {

	CallbackManager::CallbackManager() noexcept
	{
		windowCallback = new WindowCallback();
		monitorCallback = new MonitorCallback();
		mouseCallback = new MouseCallback();
		cursorCallback = new CursorCallback();
		keyboardCallback = new KeyboardCallback();
	}

	CallbackManager::~CallbackManager() {
		delete windowCallback;
		delete monitorCallback;
		delete mouseCallback;
		delete cursorCallback;
		delete keyboardCallback;
	}
}