#pragma once

namespace Uranium::Graphics::Viewport {

	class Window;

	class WindowEvents final {
	private:
		/*
		* Friends with other classes
		*/
		friend Window;

	public:
		/*
		* No need of default constructor
		*/
		WindowEvents() = delete;

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
		* Constructs a WindowEvent object with default values.
		* Initializes the events to default.
		*/
		explicit WindowEvents(Window* window) noexcept;

	private:
		/*
		* Window reference
		*/
		Window* window;
	};
}