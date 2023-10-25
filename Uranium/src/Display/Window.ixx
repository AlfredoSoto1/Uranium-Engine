export module Uranium.Display.Window;

import <string>;
import <type_traits>;
import <glm/vec2.hpp>;

extern struct GLFWwindow;

export namespace Uranium::Display {

	class Window final {
	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

		enum class Modes {
			VISIBLE = 0,
			RESIZABLE,
			DECORATED,
			FULLSCREEN,
			ALWAYS_ON_TOP,
		};

		enum class Properties {
			TITLE = 0,
			OPACITY,
			POSITION,
			DIMENSION,
			RESOLUTION
		};

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
		operator GLFWwindow* () const {
			return glWindow;
		}

		//bool isCurrent() const;
		//bool shouldClose() const;
	
	public:
		/*
		* Public setters
		*/
		template<class T>
		void setProperty(Properties property, T type);

		//void setTitle(const std::string& title);
		//void setOpacity(unsigned int opacity);
		//void setPosition(const glm::ivec2& position);
		//void setDimension(const glm::ivec2& dimension);
		//void setResolution(const glm::ivec2& resolution);

	public:
		/*
		* Public modifiers
		*/

		//void close();
		//void focus();
		//void restore();
		//void maximize();
		//void minimize();
		//void requestAttention();

		//void centerWindow(const Monitor& monitor);

	private:
		/*
		* Private methods
		*/
		// void build();
		// void dispose();

	private:
		/*
		* Private members
		*/
		
		// Volatile members
		volatile bool hasCreated;
		volatile bool hasDisposed;

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

	template<class T>
	void Window::setProperty(Window::Properties property, T type) {
#ifdef _DEBUG
		if constexpr (!std::is_same<T, glm::ivec2>::value)
			throw std::exception("Type entered is not a glm::ivec2 type");
#endif // _DEBUG

		switch (property) {
		case Properties::POSITION:
			
			break;
		case Properties::DIMENSION:

			break;
		case Properties::RESOLUTION:

			break;
		}
	}
}