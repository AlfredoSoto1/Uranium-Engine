#pragma once

#include <string>

#include "Utils/Position.h"
#include "Utils/Dimension.h"

struct GLFWwindow;

namespace Uranium::Utils {
	struct Position;
	struct Dimension;
}

namespace Uranium::Graphics::Display {

	class Window;
	class WindowMode;

	/*
	* Window Properties blueprint
	* 
	*/
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
		* public methods
		*/
		void setGLVersion(unsigned int mayor, unsigned int minor);

		void setTitle(const std::string& title);

		void setOpacity(unsigned int opacity);
		void setPosition(const Position& position);
		void setDimension(const Dimension& dimension);
		void setResolution(const Dimension& resolution);

	public:
		/*
		* Public getters
		*/
		std::string getTitle() const;

		unsigned int getMayorGLVersion() const;
		unsigned int getMinorGLVersion() const;

		inline unsigned int getOpacity() const;

		Position& getPosition();
		Dimension& getDimension();
		Dimension& getResolution();

	private:
		/*
		* Friends with other classes
		*/
		friend Window;

	private:
		/*
		* Non visible constructor
		*/
		explicit WindowProps();
		
		void initDefault() const;

	private:
		/*
		* private members
		*/
		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;

		GLFWwindow* glWindow;

		std::string title;

		unsigned int opacity;

		Position position;
		Dimension dimension;
		Dimension resolution;
	};
}
