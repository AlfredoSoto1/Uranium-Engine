#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Graphics::UI {
	
	namespace Display = Uranium::Graphics::Display;

	class CursorShape;

	class Cursor {
	public:
		virtual ~Cursor();

		Cursor(const Cursor&) = delete;
		Cursor(const Cursor&&) = delete;

		void setPosition(double xpos, double ypos);
		void setNormPosition(double xposN, double yposN);

		void setCursorShape(std::shared_ptr<CursorShape> cursorProps);

		double getXPosition();
		double getYPosition();

		double getXSpeed();
		double getYSpeed();

		double getXNormPosition();
		double getYNormPosition();

		bool isMoving();

		void hide();
		void grab();
		void toDefault();

		void toDefaultShape();

	private:
		/*
		* Friends with other classes
		*/
		//friend class Mouse;

	private:
		/*
		* Private methods
		*/
		Cursor() = delete;
		Cursor(Display::Window* _window);

	private:
		/*
		* Private members
		*/

		double xPosition;
		double yPosition;

		double lastXpos;
		double lastYpos;

		double xSpeed;
		double ySpeed;

		double xNorm;
		double yNorm;

		bool isActive;

		Display::Window* window;

		std::shared_ptr<CursorShape> cursorShape;

	};
}