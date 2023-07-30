#include <GLFW/glfw3.h>

#include "WindowProps.h"

namespace Uranium::Graphics::Display {

	void WindowProps::setInt(const PropHint& hint, int integerValue) {
		switch (hint) {
		case PropHint::OPACITY:
			this->opacity = integerValue;
			
			if (not glWindow) return;
			
			glfwSetWindowAttrib(
				// Establish window attribute to be -> frame buffer
				glWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
				// Tell the frame buffer to become transparent
				// if and only if the opacity is lower than 100%
				opacity < 100 ? GLFW_TRUE : GLFW_FALSE
			);

			// Set the opacity of the window to be in a scale of [0, 100]
			glfwSetWindowOpacity(glWindow, opacity / 100.0f);
			break;
		}
	}

	void WindowProps::setTitle(const std::string& title) {
		this->title = title;
		if (glWindow) glfwSetWindowTitle(glWindow, title.c_str());
	}

	void WindowProps::setPosition(const Position& position) {
	
	}

	void WindowProps::setDimension(const PropHint& hint, const Dimension& dimension) {
		switch (hint) {
		case PropHint::DIMENSION:
			this->dimension = dimension;

			if (not glWindow) return;

			glfwSetWindowAttrib(
				// Establish window attribute to be -> frame buffer
				glWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
				// Tell the frame buffer to become transparent
				// if and only if the opacity is lower than 100%
				opacity < 100 ? GLFW_TRUE : GLFW_FALSE
			);

			// Set the opacity of the window to be in a scale of [0, 100]
			glfwSetWindowOpacity(glWindow, opacity / 100.0f);
			break;
		}
	}
}