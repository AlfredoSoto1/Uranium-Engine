#include <GL/glfw3.h>

#include "Window.h"
#include "WindowManager.h"

namespace Uranium::Platform::Display {

	WindowManager::WindowManager() noexcept :
		canRender(true),
		isFirstThreadTurn(true),
		openedWindowCount(0u)
	{

	}

	WindowManager::~WindowManager() {
		openedWindowCount = 0u;
	}

	bool WindowManager::allWindowsClosed() const {
		return openedWindowCount == 0u;
	}

	bool WindowManager::waitToRender() const {
		return (canRender && isFirstThreadTurn) || (!canRender && !isFirstThreadTurn);
	}

	void WindowManager::runWindow(std::shared_ptr<Window> window, std::function<void()>& render) {

		// Increase the window count
		openedWindowCount++;

		// Make the window context lock in *this* thread
		window->lockWindowOnThread();

		// Update the window content
		while (!window->getEvents().shouldClose()) {
			// Lock the current thread before rendering
			std::unique_lock<std::mutex> lock(swapBufferControl);

			// Force the thread to wait until any neighbor thread
			// has finished the rendering
			allowBufferSwap.wait(lock, &WindowManager::waitToRender);
		
			// Toggle if the thread should go next
			isFirstThreadTurn = !isFirstThreadTurn;

			// render the content of the application
			render();

			// update the content of the display
			window->updateDisplay();

			// Allow the next thread to render
			canRender = !canRender;
			lock.unlock();
			allowBufferSwap.notify_one();
		}

		// Decrease the window count
		openedWindowCount--;
	}
}