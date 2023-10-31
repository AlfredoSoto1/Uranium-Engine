#pragma once

namespace Uranium::Input {

	class Uranium::Graphics::Display::Window;

	class Keyboard {
	private:
		friend class Uranium::Core::Application::Application;
		
		bool* keys;

		bool toggled = false;
		bool released = false;

		Keyboard(Uranium::Graphics::Display::Window* _window);

		void update();
	
	public:
		virtual ~Keyboard();

		bool isKeyDown(int _key);
		bool isKeyToggled(int _key);
		bool isKeyReleased(int _key);
	};
}