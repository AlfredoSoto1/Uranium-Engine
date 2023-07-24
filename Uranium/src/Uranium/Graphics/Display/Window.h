#pragma once

#include <string>

#include "Uranium/Utils/Position.h"
#include "Uranium/Utils/Dimension.h"

struct GLFWwindow;

namespace Uranium::Utils {
	struct Position;
	struct Dimension;
}

namespace Uranium::Graphics::Display {
	/*
	* Window class
	* 
	*/
	class Window {
	public:
		/*
		* custom alias
		*/
		using Position = Uranium::Utils::Position;
		using Dimension = Uranium::Utils::Dimension;

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static const unsigned int MIN_WIDTH = 320;
		static const unsigned int MIN_HEIGHT = 180;

	public:
		// 
		// Explicit creation of a window inside a context
		// + title - Title as string on top of window
		// + width/height representing the window Dimensions
		//
		explicit Window(const std::string& title, unsigned int width, unsigned int height);
		
		~Window();

	public:
		/*
		* Setters
		*/
		//void setMonitor();

		void setTitle(const std::string& title);

		void setSize(const Dimension& dimension);
		void setPosition(const Position& position);
		void setFullscreen(const Dimension& dimension);

		void setVisible(bool isVisible);
		void setResizable(bool isResizable);
		void setDecorated(bool isDecorated);
		void setAlwaysOnTop(bool isAlwaysOnTop);

		void setTransparency(unsigned int transparency);
		
	public:
		/*
		* Window-action methods
		*/
		void close();
		void focus();			
		void restore();			
		void maximize();		
		void minimize();		
		void centerWindow();	
		void requestAttention();

	public:
		/*
		* Getters
		*/
		auto getSize() -> Dimension;
		auto getPosition() -> Position;

		unsigned int getTransparency();

	public:
		/*
		* Result of actions
		*/
		bool hasClosed();

		bool isRestored();		 
		bool isMaximized();		 
		bool isMinimized();	

		bool isVisible();		 
		bool isResizable();		 
		bool isDecorated();		 
		bool isFullscreen();	 
		bool isAlwaysOnTop();	 

	private:
		/*
		* Private members
		*/
		GLFWwindow* windowContext;

		std::string title;

		Position position;
		Dimension dimension;

		unsigned int transparency;

		bool is_Visible;
		bool is_Resizable;
		bool is_Decorated;
		bool is_Fullscreen;
		bool is_AlwaysOnTop;

		bool is_Maximized;
		bool is_Minimized;

	private:
		/*
		* Private methods
		*/
	};
}