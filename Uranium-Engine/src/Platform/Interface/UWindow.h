//#pragma once
//
//#include <memory>
//#include <string>
//#include <glm/vec2.hpp>
//
//#include "Input/Events/Event.h"
//
//struct GLFWwindow;
//
//namespace Uranium::Core {
//	class Application;
//}
//
//namespace Uranium::Input::Callbacks {
//	class WindowCallback;
//	class MouseCallback;
//	class CursorCallback;
//	class KeyboardCallback;
//}
//
//namespace Uranium::Platform::Monitor {
//	class Monitor;
//}
//
//namespace Uranium::Platform::Interface {
//	
//	class UWindow {
//	protected:
//		using MonitorRef = std::shared_ptr<Monitor::Monitor>;
//
//		/*
//		* Minimun and maximum default dimensions
//		* for a window when resizing and creation
//		*/
//		static constexpr unsigned int MIN_WIDTH = 320;
//		static constexpr unsigned int MIN_HEIGHT = 180;
//
//	public:
//		/*
//		* Constructs and initiates the window context
//		*/
//		explicit UWindow() noexcept;
//
//		virtual ~UWindow();
//		
//		/*
//		* Returns a raw pointer reference to a GLFWwindow
//		*/
//		operator GLFWwindow* () const;
//
//	public:
//		void onUpdate() const;
//
//		bool shouldClose() const;
//		
//		/*
//		* Set all basic window properties
//		*/
//		void setOpacity(unsigned int opacity);
//		void setTitle(const std::string& title);
//		void setPosition(const glm::ivec2& position);
//		void setDimension(const glm::ivec2& dimension);
//		void setResolution(const glm::ivec2& resolution);
//
//	public:
//		/*
//		* Get window modes
//		*/
//		auto isVisible()     const -> bool { return modes.visible;     };
//		auto isResizable()   const -> bool { return modes.resizable;   };
//		auto isDecorated()   const -> bool { return modes.decorated;   };
//		auto isAlwaysOnTop() const -> bool { return modes.alwaysOnTop; };
//
//		/*
//		* Set window modes
//		*/
//		virtual void setVisible(bool visible)         = 0;
//		virtual void setResizable(bool resizable)     = 0;
//		virtual void setDecorated(bool decorated)     = 0;
//		virtual void setAlwaysOnTop(bool alwaysOnTop) = 0;
//
//	public:
//		/*
//		* Close, focus and request attention operations
//		*/
//		virtual void close() = 0;
//		virtual void focus() = 0;
//		virtual void requestAttention() = 0;
//
//		/*
//		* Restores, maximizes and minimizes the current window
//		*/
//		virtual void restore() = 0;
//		virtual void maximize() = 0;
//		virtual void minimize() = 0;
//
//		/*
//		* Can center and make the window fullscreen
//		* for a given monitor reference
//		*/
//		virtual void center(MonitorRef monitor) = 0;
//		virtual void setFullscreen(MonitorRef monitor) = 0;
//
//	public:
//		/*
//		* Sets the current VSync to be enabled or disabled.
//		* This is can be implemented differently depending the graphics API
//		* used. This is why the function is set as virtual.
//		*/
//		virtual void setVSync(bool enabled);
//
//	protected:
//		friend class Core::Application;
//
//		using Event = Input::Events::Event;
//		
//		using WindowCallback   = Input::Callbacks::WindowCallback;
//		using MouseCallback    = Input::Callbacks::MouseCallback;
//		using CursorCallback   = Input::Callbacks::CursorCallback;
//		using KeyboardCallback = Input::Callbacks::KeyboardCallback;
//
//		friend class WindowCallback;
//		friend class MouseCallback;
//		friend class CursorCallback;
//		friend class KeyboardCallback;
//		
//		std::unique_ptr<WindowCallback> windowCallback;
//		std::unique_ptr<MouseCallback> mouseCallback;
//		std::unique_ptr<CursorCallback> cursorCallback;
//		std::unique_ptr<KeyboardCallback> keyboardCallback;
//
//		Event::EventCallbackFn callbackFunction;
//
//		/*
//		* Creates and disposes the callbacks.
//		* This is internally handled by the application
//		*/
//		void createCallbacks();
//		void disposeCallbacks();
//
//		/*
//		* Sets the event callback function. This is
//		* internally handled by the application
//		*/
//		void setEventCallback(const Event::EventCallbackFn& callbackEvent);
//
//	protected:
//		struct WindowModes {
//			bool visible;
//			bool resizable;
//			bool decorated;
//			bool alwaysOnTop;
//		};
//
//		struct OperationState {
//			bool restored;
//			bool maximized;
//			bool minimized;
//			bool fullscreen;
//		};
//
//		struct WindowProps {
//			std::string title;
//			glm::ivec2 position;
//			glm::ivec2 dimension;
//			glm::ivec2 resolution;
//			unsigned int opacity;
//		};
//
//		GLFWwindow* glWindow;
//
//		WindowModes modes;
//		WindowProps props;
//		OperationState operation;
//
//		bool vSyncEnabled;
//	};
//}