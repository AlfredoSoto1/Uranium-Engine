#pragma once

#include <string>
#include <glm/vec2.hpp>

extern struct GLFWwindow;

namespace Uranium::Display {

	class WindowProps final {
	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;

	public:
		/*
		* Constructs a WindowProps object with default values.
		* Initializes the properties to default.
		*/
		explicit WindowProps() noexcept;

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
		* General Properties
		*/
		std::string title;

		glm::ivec2 position;   // Position of the window
		glm::ivec2 dimension;  // Dimension of window in pixels
		glm::ivec2 resolution; // Resolution of the display in pixels inside window

		unsigned int opacity;
	};
}