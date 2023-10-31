#pragma once

#include <memory>

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {
	class MouseCallback;
	class CursorCallback;
}

namespace Uranium::Graphics::UI {
	
	class CursorShape;

	/*
	* Cursor blueprint
	* 
	*/
	class Cursor {
	public:
		/*
		* Custom alias
		*/
		using Window         = Uranium::Graphics::Display::Window;
		using MouseCallback  = Uranium::Input::Callbacks::MouseCallback;
		using CursorCallback = Uranium::Input::Callbacks::CursorCallback;

	public:
		/*
		* Public modifiers
		*/
		void hide();
		void grab();

		void toDefault();
		void toDefaultShape();

	public:
		/*
		* Public setters
		*/
		void setPosition(double xpos, double ypos);
		void setCursorShape(std::shared_ptr<CursorShape> cursorProps);

	public:
		/*
		* Public getters
		*/
		bool isMoving();
		bool isInside();

		double getXSpeed();
		double getYSpeed();

		double getXPosition();
		double getYPosition();

		double getXNormPosition();
		double getYNormPosition();

	private:
		/*
		* Friends with other classes
		*/
		friend MouseCallback;
		friend CursorCallback;

	private:
		/*
		* Private methods
		*/
		Cursor() = delete;
		Cursor(Cursor& copy) = delete;
		Cursor(Cursor&& move) = delete;
		Cursor(const Cursor& copy) = delete;
		Cursor(const Cursor&& move) = delete;

		explicit Cursor(std::shared_ptr<Window> _window);

		virtual ~Cursor();

	private:
		/*
		* private modifiers
		*/
		void setNormPosition(double xposN, double yposN);

	private:
		/*
		* Private members
		*/
		std::shared_ptr<Window> window;
		std::shared_ptr<CursorShape> cursorShape;
		
		double xPosition;
		double yPosition;

		double lastXpos;
		double lastYpos;

		double xSpeed;
		double ySpeed;

		double xNorm;
		double yNorm;

		bool isActive;
	};
}