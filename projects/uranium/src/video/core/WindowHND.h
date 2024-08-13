#pragma once

#include "core/URAPI.h"

#include <string>
#include <glm/vec2.hpp>

namespace uranium::video::core {

	URANIUM_API class WindowHND final {
	public:
		static constexpr unsigned int MIN_WIDTH  = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;
	
	public:
		explicit WindowHND() noexcept;
		~WindowHND() noexcept;

	public:
		bool shouldClose() const;

		void setOpacity(unsigned int opacity);
		void setTitle(const std::string& title);
		void setPosition(const glm::ivec2& position);
		void setDimension(const glm::ivec2& dimension);
		void setResolution(const glm::ivec2& resolution);

	public:
		inline bool isVisible()     const { return visible;     };
		inline bool isResizable()   const { return resizable;   };
		inline bool isDecorated()   const { return decorated;   };
		inline bool isAlwaysOnTop() const { return alwaysOnTop; };

		void setVisible(bool visible);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);
		void setAlwaysOnTop(bool alwaysOnTop);

	public:
		void close();
		void focus();
		void requestAttention();

		void restore() ;
		void maximize();
		void minimize();

		void center(void* monitor);
		void setFullscreen(void* monitor);

	private:
		bool visible;
		bool resizable;
		bool decorated;
		bool alwaysOnTop;

		bool restored;
		bool maximized;
		bool minimized;
		bool fullscreen;
		unsigned int opacity;

		std::string title;
		glm::ivec2 position;
		glm::ivec2 dimension;
		glm::ivec2 resolution;

		GLFWwindow* glfwWindow;
	};
}