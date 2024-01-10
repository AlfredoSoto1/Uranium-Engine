#pragma once

#include <memory>
#include <string>
#include <glm/vec2.hpp>

#include "Core/CoreMacros.h"
#include "Input/Events/Event.h"

struct GLFWwindow;

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Input::Callbacks {
	class WindowCallback;
	class MouseCallback;
	class CursorCallback;
	class KeyboardCallback;
}

namespace Uranium::Platform::Monitor {
	class Monitor;
}

namespace Uranium::Platform::Interface {
	
	URANIUM_API class Window {
	public:
		static void initWindowAPI();              // Initiates the windowing API
		static void shutdownWindowAPI() noexcept; // Shuts down the windowing API

		// Minimun and maximum default dimensions
		// for a window when resizing and creation
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

	private:
		/*
		* Logs any GLFW errors
		* 
		* @param error-code
		* @param description
		*/
		static void displayGLFWErrors(int error, const char* description) noexcept;

	public:
		/*
		* Creates a Uranium based Window
		* 
		* @param title
		* @param width
		* @param height
		*/
		explicit Window(const std::string& title, uint32_t width, uint32_t height);
		virtual ~Window() noexcept;
		
		/*
		* Returns a raw pointer reference to a GLFWwindow
		*/
		operator GLFWwindow* () const noexcept;

	public:
		/*
		* @returns true if window should close false otherwise
		*/
		bool shouldClose() const noexcept;

		auto isVisible()     const noexcept -> bool { return visible;     };
		auto isResizable()   const noexcept -> bool { return resizable;   };
		auto isDecorated()   const noexcept -> bool { return decorated;   };
		auto isAlwaysOnTop() const noexcept -> bool { return alwaysOnTop; };

	public:
		void setTitle(const std::string& title);

		void setPosition(const glm::ivec2& position);
		void setDimension(const glm::ivec2& dimension);
		void setResolution(const glm::ivec2& resolution);

	public:
		/*
		* Sets the current VSync to be enabled or disabled.
		* This is can be implemented differently depending
		* the graphics API used. If the method is not
		* overriten, it will use glfwSwapInterval(0);
		* 
		* @param enabled - true or false
		*/
		virtual void setVSync(bool enabled);

	protected:
		friend class GraphicsAPI;

		using SurfaceRef = void*;

		/*
		* @returns surface reference for the graphics API chosen to use.
		* 
		* @throw runtime_error if fails to create.
		*/
		virtual SurfaceRef createSurface() const = 0;

	protected:
		virtual void setVisible(bool visible)         = 0;
		virtual void setResizable(bool resizable)     = 0;
		virtual void setDecorated(bool decorated)     = 0;
		virtual void setAlwaysOnTop(bool alwaysOnTop) = 0;

	protected:
		virtual void close() = 0;
		virtual void focus() = 0;
		virtual void requestAttention() = 0;

	protected:
		virtual void restore() = 0;
		virtual void maximize() = 0;
		virtual void minimize() = 0;

	protected:
		using MonitorRef = std::shared_ptr<Monitor::Monitor>;

		virtual void center(MonitorRef monitor) = 0;
		virtual void setFullscreen(MonitorRef monitor) = 0;

	protected:
		GLFWwindow* glfwWindow;

		std::string title;

		glm::ivec2 position;
		glm::ivec2 dimension;
		glm::ivec2 resolution;

		bool visible;
		bool resizable;
		bool decorated;
		bool alwaysOnTop;

		bool restored;
		bool maximized;
		bool minimized;
		bool fullscreen;

		bool vSyncEnabled;

	private:
		friend class Core::Application;

		void onUpdate() const;

	private:
		using Event = Input::Events::Event;
			
		using WindowCallback   = Input::Callbacks::WindowCallback;
		using MouseCallback    = Input::Callbacks::MouseCallback;
		using CursorCallback   = Input::Callbacks::CursorCallback;
		using KeyboardCallback = Input::Callbacks::KeyboardCallback;

		friend class WindowCallback;
		friend class MouseCallback;
		friend class CursorCallback;
		friend class KeyboardCallback;
			
		std::unique_ptr<WindowCallback>   windowCallback;
		std::unique_ptr<MouseCallback>    mouseCallback;
		std::unique_ptr<CursorCallback>   cursorCallback;
		std::unique_ptr<KeyboardCallback> keyboardCallback;

		Event::EventCallbackFn callbackFunction;

	private:
		/*
		* Creates and disposes the callbacks.
		* This is internally handled by the application
		*/

		void createCallbacks();
		void disposeCallbacks() noexcept;

		/*
		* Sets the event callback function. This is
		* internally handled by the application
		*/
		void setEventCallback(const Event::EventCallbackFn& callbackEvent) noexcept;
	};
}