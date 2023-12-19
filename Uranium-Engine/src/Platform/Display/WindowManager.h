#pragma once

#include <mutex>
#include <memory>
#include <functional>

namespace Uranium::Core::Engine {
	class BaseEngine;
}

namespace Uranium::Platform::Display {

	class Window;

	class WindowManager final {
	public:
		friend Core::Engine::BaseEngine;

	private:
		/*
		* Creates and controls the flow of
		* the windows during the lifetime of the application
		*/
		explicit WindowManager() noexcept;

		~WindowManager();

	private:
		/*
		* Waits for the current thread to finish render
		*/
		bool waitToRender() const;

		/*
		* Returns true if all windows are closed
		*/
		bool allWindowsClosed() const;

		/*
		* Runs and updates the window
		*/
		void runWindow(std::shared_ptr<Window> window, std::function<void()>& render);

	private:
		/*
		* Render control flags
		*/
		volatile bool canRender;
		volatile bool isFirstThreadTurn;

		unsigned int openedWindowCount;

		/*
		* Mutex to control the swapbuffer of each window
		*/
		std::mutex swapBufferControl;
		std::condition_variable allowBufferSwap;
	};
}