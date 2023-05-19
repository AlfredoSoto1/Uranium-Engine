#pragma once

#include <string>
#include <memory>

namespace Uranium::Input::Callbacks {
	class WindowCallback;
}

namespace Uranium::Graphics::Display {

	class Window;
	class Monitor;

	class WindowProps {
	public:
		/*
		* custom alias
		*/
		using WindowCallback = Uranium::Input::Callbacks::WindowCallback;

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static const unsigned int MIN_WIDTH = 320;
		static const unsigned int MIN_HEIGHT = 180;

	public:
		/*
		* Default constructor for creating window props.
		* ~title
		* ~width-height
		* ~monitor to where it will be displayed at first
		*/
		WindowProps(const std::string& title, unsigned int width, unsigned int height);
		virtual ~WindowProps();

		void setTitle(const std::string& title);
		void setOpenGLVersion(unsigned int mayor, unsigned int minor);

		void setSize(unsigned int width, unsigned int height);
		void setPosition(int xpos, int ypos);

		void setWindowTransparency(unsigned int transparency);

		void setVisible(bool isVisible);
		void setResizable(bool isResizable);
		void setDecorated(bool isDecorated);
		void setAlwaysOnTop(bool isAlwaysOnTop);

		std::string getTitle();

		unsigned int getWindowTransparency();

		unsigned int getWidth();
		unsigned int getHeight();

		void getSize(unsigned int& width, unsigned int& height);
		void getPosition(int& xpos, int& ypos);
		void getOpenGlVersion(unsigned int& mayor, unsigned int& minor);
		
		bool isRestored();		 // 
		bool isMaximized();		 // 
		bool isMinimized();		 // 
								 // 
		bool isVisible();		 // Current Window status
		bool isResizable();		 // 
		bool isDecorated();		 // 
		bool isFullscreen();	 // 
		bool isAlwaysOnTop();	 // 

	private:
		/*
		* Mutual friend classes
		*/
		friend Window;
		friend WindowCallback;

	private:
		/*
		* Private methods
		*/
		void setContext(Window* windowContext);

	private:
		/*
		* Private members
		*/
		Window* windowContext;
		
		std::string title;

		unsigned int width;
		unsigned int height;

		unsigned int mayorGLVersion;
		unsigned int minorGLVersion;

		unsigned int transparency;

		int xPosition;
		int yPosition;

		bool is_Visible;
		bool is_Resizable;
		bool is_Decorated;
		bool is_Fullscreen;
		bool is_AlwaysOnTop;

		bool is_Maximized;
		bool is_Minimized;
	};
}