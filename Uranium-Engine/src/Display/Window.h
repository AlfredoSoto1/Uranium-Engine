#pragma once

#include <string>
#include <type_traits>
#include <glm/vec2.hpp>

extern struct GLFWwindow;

namespace Uranium::Display {

	class Window final {
	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

	public:
		/*
		* This creates a window inside an OpenGL context.
		* The distructor is not added to the virtual table
		* since no class should inherit from *this* class.
		*/
		explicit Window();

		~Window();

	public:
		/*
		* Public getters
		*/
		//operator GLFWwindow* () const {
		//	return glWindow;
		//}

		bool isCurrent() const;
		bool shouldClose() const;
	
	public:
		/*
		* Public setter properties
		*/

		// Sets the title at the top of the window
		void setTitle(const std::string& title);

		/*
		* Sets the opacity of the window
		* (This takes alot of resources for low-end devices)
		*/
		void setOpacity(unsigned int opacity);

		// Sets the position of the window
		void setPosition(const glm::ivec2& position);

		// Sets the dimension of the window
		void setDimension(const glm::ivec2& dimension);

		// Sets the Resolution of the window
		void setResolution(const glm::ivec2& resolution);

	public:
		/*
		* Public setter modes
		*/

		// Changes the visibility of the window
		void setVisible(bool visible);

		// Changes if the window should be capable of resizing
		void setResizable(bool resizable);

		// Decorated flag that draws the border and top bar of the window
		void setDecorated(bool decorated);

		// Sets the window at the top of the app priority queue
		void setAlwaysOnTop(bool alwaysOnTop);

		// Changes the screen mode to fullscreen when provided with a monitor
		//void setFullscreen(const Monitor& monitor);

	public:
		/*
		* Public modifiers
		*/

		void close();
		void focus();
		void restore();
		void maximize();
		void minimize();
		void requestAttention();

		//void centerWindow(const Monitor& monitor);

	private:
		/*
		* Private methods
		*/
		
		void prepareDefaultHints() const;

	private:
		/*
		* Private members
		*/
		
		// Volatile members
		volatile bool hasCreated;

		/*
		* Window properties
		*/
		GLFWwindow* glWindow;
		
		std::string title;
		
		glm::ivec2 position;
		glm::ivec2 dimension;
		glm::ivec2 resolution;
		
		unsigned int opacity;
		
		unsigned int glMajor;
		unsigned int glMinor;

		/*
		* Window modes
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