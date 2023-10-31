#include <GLFW/glfw3.h>

#include "Cursor.h"
#include "CursorShape.h"
#include "Graphics/Display/Window.h"

namespace Uranium::Graphics::UI {

	Cursor::Cursor(std::shared_ptr<Window> window) :
		window(window),
		cursorShape(nullptr),

		xPosition(0.0),
		yPosition(0.0),

		lastXpos(0.0),
	    lastYpos(0.0),

		xSpeed(0.0),
		ySpeed(0.0),

		xNorm(0.0),
		yNorm(0.0),

		isActive(false)
	{

	}

	Cursor::~Cursor() {

	}

	void Cursor::setCursorShape(std::shared_ptr<CursorShape> cursorShape) {
		this->cursorShape = cursorShape;
		glfwSetCursor(*window, *cursorShape);
	}

	void Cursor::setPosition(double xpos, double ypos) {
		xPosition = xpos;
		yPosition = ypos;
		glfwSetCursorPos(*window, xpos, ypos);
	}

	void Cursor::setNormPosition(double xposN, double yposN) {
		xNorm = xposN;
		yNorm = yposN;
	}

	double Cursor::getXPosition() {
		return xPosition;
	}

	double Cursor::getYPosition() {
		return yPosition;
	}

	double Cursor::getXSpeed() {
		xSpeed = lastXpos - xPosition;
		lastXpos = xPosition;
		return xSpeed;
	}
	double Cursor::getYSpeed() {
		ySpeed = lastYpos - yPosition;
		lastYpos = yPosition;
		return ySpeed;
	}

	double Cursor::getXNormPosition() {
		return xNorm;
	}
	double Cursor::getYNormPosition() {
		return yNorm;
	}

	bool Cursor::isMoving() {
		return xSpeed != 0 && ySpeed != 0 && isActive;
	}

	bool Cursor::isInside() {
		return isActive;
	}

	void Cursor::hide() {
		glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void Cursor::grab() {
		glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Cursor::toDefault() {
		glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Cursor::toDefaultShape() {
		glfwSetCursor(*window, NULL);
	}
}
