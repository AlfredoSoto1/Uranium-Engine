#pragma once

#include <string>

namespace Uranium::Graphics::Display {

	class WindowMode {
	public:
		/*
		* Window props constructors
		*/
		WindowMode() :
			visible(true),
			resizable(true),
			decorated(true),
			fullscreen(false),
			alwaysOnTop(false),

			maximized(false),
			minimized(false)
		{
		}

	public:
		/*
		* Public modes
		*/
		bool visible;
		bool resizable;
		bool decorated;
		bool fullscreen;
		bool alwaysOnTop;

		bool maximized;
		bool minimized;
	};
}
