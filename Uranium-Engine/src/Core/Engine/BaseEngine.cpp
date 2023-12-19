#include <GL/glfw3.h>

#include <mutex>
#include <condition_variable>

#include "BaseEngine.h"
#include "ThreadContext.h"

#include "Platform/Display/Window.h"
#include "Platform/Display/WindowManager.h"
#include "Input/Callbacks/CallbackManager.h"

namespace Uranium::Core::Engine {

	BaseEngine::BaseEngine() noexcept :
		renderThreads(),
		updateThreads(),

		windows(),
		windowManager(nullptr),
		callbackManager(nullptr)
	{
	}

	BaseEngine::~BaseEngine() {

	}

	void BaseEngine::run() {

		using namespace Platform::Display;

		// Obtain list of windows
		auto display1 = std::make_shared<Window>();
		auto display2 = std::make_shared<Window>();

		/*
		* Create the renderer
		*/
		std::function<void()> render1 = [&display1] () {
			// check if window has resized
			int width, height;
			glfwGetFramebufferSize(*display1, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0, 0.0, 0.0, 1.0);
		};		
		
		std::function<void()> render2 = [&display2] () {
			// check if window has resized
			int width, height;
			glfwGetFramebufferSize(*display2, &width, &height);
			glViewport(0, 0, width, height);

			// render scene here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0, 1.0, 0.0, 1.0);
		};

		/*
		* Window manager update events and Callbacks
		*/
		std::mutex swapBufferControl;
		std::condition_variable allowBufferSwap;
		bool canRender = true;
		bool isFirstThreadTurn = true;

		std::function<void(std::shared_ptr<Window>, std::function<void()>&)> updateWindow = [&swapBufferControl, &allowBufferSwap, &canRender, &isFirstThreadTurn](std::shared_ptr<Window> display, std::function<void()>& render) {
			while (!display->getEvents().shouldClose()) {
				//swapBufferControl.lock();
				std::unique_lock<std::mutex> lock(swapBufferControl);

				allowBufferSwap.wait(lock, [&canRender, &isFirstThreadTurn] { return (canRender && isFirstThreadTurn) || (!canRender && !isFirstThreadTurn); });
				isFirstThreadTurn = !isFirstThreadTurn;

				// render the content of the application
				render();

				// update the content of the display
				glfwSwapBuffers(*display);

				canRender = !canRender;
				lock.unlock();
				allowBufferSwap.notify_one();
			}
		};

		/*
		* Create Rendering threads
		*/
		std::vector<std::thread> renderThreads;

		renderThreads.push_back(std::thread([&display1, &render1, &updateWindow]() {

			glfwMakeContextCurrent(*display1);
			
			updateWindow(display1, render1);
		}));

		renderThreads.push_back(std::thread([&display2, &render2, &updateWindow]() {
			
			glfwMakeContextCurrent(*display2);
			
			updateWindow(display2, render2);
		}));

		// test if any of the windows should close
		auto isAnyActive = [&display1, &display2]() -> bool {
			return !display1->getEvents().shouldClose() || !display2->getEvents().shouldClose();
		};
		
		/*
		*  Update callbacks from each window
		*/
		while (isAnyActive()) {
			glfwPollEvents();
		}

		// Join all render Threads
		for (auto& renderThread : renderThreads)
			renderThread.join();

		// dispose all windows
		display1.reset();
		display2.reset();

		// Dispose all threads
		renderThreads.clear();

		//while (!display1->getEvents().shouldClose() && !display2->getEvents().shouldClose()) {

		//	glfwMakeContextCurrent(*display1);

		//	// check if window has resized
		//	int width, height;
		//	glfwGetFramebufferSize(*display1, &width, &height);
		//	glViewport(0, 0, width, height);

		//	// render scene here
		//	glClear(GL_COLOR_BUFFER_BIT);
		//	glClearColor(1.0, 0.0, 0.0, 1.0);

		//	// TODO: fix when multi-threaded
		//	glfwSwapBuffers(*display1);


		//	glfwMakeContextCurrent(*display2);

		//	glfwGetFramebufferSize(*display2, &width, &height);
		//	glViewport(0, 0, width, height);

		//	// render scene here
		//	glClear(GL_COLOR_BUFFER_BIT);
		//	glClearColor(0.0, 1.0, 0.0, 1.0);

		//	// TODO: fix when multi-threaded
		//	glfwSwapBuffers(*display2);

		//	glfwPollEvents();
		//}
		//
		//// release the window reference
		//display1.reset();
		//display2.reset();
	}

	void BaseEngine::initManagers() {
		using namespace Platform::Display;

		windowManager = new WindowManager();
	}

	void BaseEngine::disposeManagers() {

		delete windowManager;
	}
}