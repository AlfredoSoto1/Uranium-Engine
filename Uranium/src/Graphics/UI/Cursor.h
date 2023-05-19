#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Core::Application {
	class ApplicationProgram;
}

namespace Uranium::Input::Callbacks {
	class MouseCallback;
	class CursorCallback;
}

namespace Uranium::Graphics::UI {
	
	namespace Display = Uranium::Graphics::Display;
	namespace Callbacks = Uranium::Input::Callbacks;
	namespace Application = Uranium::Core::Application;

	class CursorShape;

	class Cursor {
	public:
		virtual ~Cursor();

		void setPosition(double xpos, double ypos);
		void setCursorShape(std::shared_ptr<CursorShape> cursorProps);

	public:
		/*
		* Public methods
		*/
		double getXPosition();
		double getYPosition();

		double getXSpeed();
		double getYSpeed();

		double getXNormPosition();
		double getYNormPosition();

		bool isMoving();
		bool isInside();

		void hide();
		void grab();
		void toDefault();

		void toDefaultShape();

	private:
		/*
		* Friends with other classes
		*/
		friend Callbacks::MouseCallback;
		friend Callbacks::CursorCallback;
		friend Application::ApplicationProgram;

	private:
		/*
		* Private methods
		*/
		Cursor() = delete;
		Cursor(const Cursor&) = delete;
		Cursor(const Cursor&&) = delete;

		Cursor(Display::Window* _window);

		void setNormPosition(double xposN, double yposN);

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