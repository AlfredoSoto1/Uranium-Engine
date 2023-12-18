#pragma once

#include <memory>
#include <vector>
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
		//void init();

		bool allWindowsClosed() const;

		void update();

		//void dispose();

	private:
		std::vector<std::function<void()>> renderCallFunctions;

		std::vector<std::shared_ptr<Window>> windows;
	};
}