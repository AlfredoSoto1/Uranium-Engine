#pragma once

#include <string>

#include "Uranium/Utils/Position.h"
#include "Uranium/Utils/Dimension.h"

namespace Uranium::Utils {
	struct Position;
	struct Dimension;
}

namespace Uranium::Graphics::Display {

	class WindowProps {
	public:
		/*
		* Custom alias
		*/
		using Position = Uranium::Utils::Position;
		using Dimension = Uranium::Utils::Dimension;

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		* 
		*  - unsinged int as pixels
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

	public:
		/*
		* Window props constructors
		*/
		explicit WindowProps() : 
			mayorGLVersion(3),
			minorGLVersion(3),

			title("Uranium Engine"),

			opacity(100),
			position(0, 0),
			dimension(MIN_WIDTH, MIN_HEIGHT),
			resolution(MIN_WIDTH, MIN_HEIGHT)
		{
		}

	public:
		/*
		* public props
		*/
		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;

		std::string title;

		unsigned int opacity;

		Position position;
		Dimension dimension;
		Dimension resolution;
	};
}
