#pragma once

#include "Graphics/Display/Cursor.h"

namespace Uranium::Input {

	class Uranium::Graphics::Display::Window;

	class Mouse {
	private:
		friend class Core::Application::Application;

		Graphics::Display::Cursor cursor;

		bool* mouseButtons;

		void update();

	public:
		Mouse(Uranium::Graphics::Display::Window* _window);
		virtual ~Mouse();

		Graphics::Display::Cursor& getCursor();

		bool isButtonDown(int _button);

		int isMouseToggled(int _button);
	};
}