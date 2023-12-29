#pragma once

#include <memory>
#include <string>
#include <glm/vec2.hpp>

struct GLFWwindow;

namespace Uranium::Platform::Monitor {
	class Monitor;
}

namespace Uranium::Platform::Display {

	class WindowProps final {
	private:
		/*
		* Friends with other classes
		*/
		friend class Window;

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

	public:
		/*
		* No need of default constructor
		*/
		WindowProps() = delete;

	public:
		/*
		* Center window on a monitor
		*/
		void center(std::shared_ptr<Monitor::Monitor> monitor);

	public:
		/*
		* Get window properties
		*/
		auto getTitle() const -> std::string;
		auto getPosition() const -> glm::ivec2;
		auto getDimension() const -> glm::ivec2;
		auto getResolution() const -> glm::ivec2;

		auto getOpacity() const -> unsigned int;
	
	public:
		/*
		* Set window properties
		*/
		void setTitle(const std::string& title);
		void setPosition(const glm::ivec2& position);
		void setDimension(const glm::ivec2& dimension);
		void setResolution(const glm::ivec2& resolution);

		void setOpacity(unsigned int opacity);
	
	private:
		/*
		* Constructs a WindowProps object with default values.
		* Initializes the properties to default.
		*/
		explicit WindowProps(Window* window) noexcept;

	private:
		/*
		* Window reference
		*/
		Window* window;

		/*
		* General Properties
		*/
		std::string title;

		glm::ivec2 position;   // Position of the window
		glm::ivec2 dimension;  // Dimension of window in pixels
		glm::ivec2 resolution; // Resolution of the display in pixels inside window

		unsigned int opacity;
	};
}