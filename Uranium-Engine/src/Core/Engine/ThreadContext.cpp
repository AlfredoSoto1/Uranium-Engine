#include "ThreadContext.h"

namespace Uranium::Core::Engine {

	ThreadContext::ThreadContext() noexcept :
		contextThread()
	{
		
	}

	void ThreadContext::start(std::function<void()> run) {
		if (!contextThread.joinable())
			return;
		// If joinable, start the thread on the member method run()
		contextThread = std::thread(run);
	}

	void ThreadContext::dispose() {
		if (!contextThread.joinable())
			return;
		// join the current thread
		contextThread.join();
	}
}