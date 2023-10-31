#include "InputEvent.h"

#include "Core/Application/Application.h"

using namespace Uranium::Core::Application;

Mouse& InputEvent::getMouse() {
	return Application::get().getMouse();
}

Keyboard& InputEvent::getKeyboard() {
	return Application::get().getKeyboard();
}
