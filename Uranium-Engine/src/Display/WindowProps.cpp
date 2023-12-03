#include <GL/glfw3.h>

#include "Window.h"
#include "WindowProps.h"

namespace Uranium::Display {

	explicit WindowProps::WindowProps() noexcept :
		title("Uranium-Engine Display"),
		position(0, 0),   
		dimension(),  
		resolution(), 
		opacity()
	{

	}

	auto WindowProps::getTitle() const->std::string {
		return title;
	}

	auto WindowProps::getPosition() const->glm::ivec2 {
		return position;
	}

	auto WindowProps::getDimension() const->glm::ivec2 {
		return dimension;
	}

	auto WindowProps::getResolution() const->glm::ivec2 {
		return resolution;
	}

	auto WindowProps::getOpacity() const -> unsigned int {
	
	}

	void WindowProps::setTitle(const std::string& title) {
	
	}

	void WindowProps::setPosition(const glm::ivec2& position) {
	
	}

	void WindowProps::setDimension(const glm::ivec2& dimension) {
	
	}

	void WindowProps::setResolution(const glm::ivec2& resolution) {
	
	}

	void WindowProps::setOpacity(unsigned int opacity) {
	
	}
}