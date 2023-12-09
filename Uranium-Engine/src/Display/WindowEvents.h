#pragma once

namespace Uranium::Display {

	extern class Window;

	class WindowEvents final {
	public:
		/*
		* Constructs a WindowEvent object with default values.
		* Initializes the events to default.
		*/
		explicit WindowEvents(Window* window) noexcept;

	public:
		/*
		* Prepare events
		*/
		void close();
		void focus();
		void requestAttention();

	public:
		/*
		* Get current events
		*/
		bool shouldClose() const;

	private:
		/*
		* Window reference
		*/
		Window* window;
	};
}