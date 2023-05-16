#pragma once

namespace Uranium::Input {

	class Mouse;
	class Keyboard;

	class InputEvent {
	private:

	public:
		Mouse& getMouse();
		Keyboard& getKeyboard();
		
	};
}