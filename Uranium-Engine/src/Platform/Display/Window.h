#pragma once

#include <memory>
#include <string>
#include <functional>
#include <glm/vec2.hpp>

struct GLFWwindow;

namespace Uranium::Platform::Monitor {
	class Monitor;
}

namespace Uranium::Platform::Display {

	class Window final {
	private:
		using MonitorRef = std::shared_ptr<Monitor::Monitor>;
		using EventCallbackFn = std::function<void()>;

		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;
		
	public:
		struct WindowModes {
			bool visible;  
			bool resizable;  
			bool decorated;  
			bool alwaysOnTop; 
			bool vSyncEnabled;
		};

		struct WindowStates {
			bool restored;
			bool maximized;
			bool minimized;
			bool fullscreen;
		};

		struct WindowProps {
			std::string title;     
			glm::ivec2 position;  
			glm::ivec2 dimension;  
			glm::ivec2 resolution; 
			unsigned int opacity;
		};

		/*
		* Creates a window instance
		*/
		explicit Window() noexcept;

		~Window();
		
		/*
		* Returns a raw pointer reference to a GLFWwindow
		*/
		operator GLFWwindow* () const;

	public:
		void onUpdate() const;

		void restore();
		void maximize();
		void minimize();

		void close();
		void focus();
		void requestAttention();

	public:
		bool shouldClose() const;

		auto getModes() const      -> const WindowModes&;
		auto getStates() const     -> const WindowStates&;
		auto getProperties() const -> const WindowProps&;

		void center(MonitorRef monitor);
		void setFullscreen(MonitorRef monitor);

		void setTitle(const std::string& title);
		void setOpacity(unsigned int opacity);
		void setPosition(const glm::ivec2& position);
		void setDimension(const glm::ivec2& dimension);
		void setResolution(const glm::ivec2& resolution);

		void setVSync(bool enabled);
		void setVisible(bool visible);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);
		void setAlwaysOnTop(bool alwaysOnTop);

	private:
		GLFWwindow* glWindow;

		WindowModes modes;
		WindowProps props;
		WindowStates states;
	};
}