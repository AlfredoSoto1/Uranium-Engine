#pragma once

#include <string>
#include <type_traits>

#include "Uranium/Utils/Position.h"
#include "Uranium/Utils/Dimension.h"

struct GLFWwindow;

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

		enum class PropHint {
			TITLE,
			POSITION,
			DIMENSION,
			ASPECT_RATIO,

			ICON,
			OPACITY,
		};

	public:
		/*
		* Window props constructors
		*/
		explicit WindowProps() : 
			mayorGLVersion(3),
			minorGLVersion(3),

			glWindow(nullptr),

			title("Uranium Engine"),

			opacity(100),
			position(0, 0),
			dimension(MIN_WIDTH, MIN_HEIGHT)
		{
		}

		// Resolve at compile time using templates
		// Compare the type-V entered and call the
		// corresponding method that matches its type
		template<typename V> void set(const PropHint& hint, const V& value) {
			if constexpr (std::is_same<V, int>::value)
				setInt(hint, value);
			else if constexpr (std::is_same<V, Position>::value)
				setPosition(value);
			else if constexpr (std::is_same<V, Dimension>::value)
				setDimension(hint, value);
			else if constexpr (std::is_same<V, std::string>::value)
				setTitle(value);
			else
				static_assert(
					std::is_same<V, int>::value         ||
					std::is_same<V, Position>::value    ||
					std::is_same<V, Dimension>::value   ||
					std::is_same<V, std::string>::value,
					"Incompatible type as parameter"
				);
		}

		// Specialization for handling const char[]
		template<std::size_t N> void set(const PropHint& hint, const char(&value)[N]) {
			set(hint, std::string(value));
		}

	private:
		/*
		* Private methods
		*/
		void setInt(const PropHint& hint, int integerValue);

		void setTitle(const std::string& title);
		void setPosition(const Position& position);
		void setDimension(const PropHint& hint, const Dimension& dimension);

	public:
		/*
		* public props
		*/
		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;

		// Current bound window for 'this'
		// WindowProps instance
		GLFWwindow* glWindow;

		std::string title;

		unsigned int opacity;

		Position position;
		Dimension dimension;
	};
}
