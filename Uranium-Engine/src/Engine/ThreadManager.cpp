#include "ThreadManager.h"

namespace Uranium::Engine {

	ThreadManager::ThreadManager() noexcept :
		pool(),
		queuedTasks()
	{

	}

	ThreadManager::~ThreadManager() {
		disposeThreads();
	}

	void ThreadManager::enqueTask(const std::function<void()>& functionTask) {

		size_t availableWorkerIndex = getLeastWorkingThread();

		WorkingThread& worker = pool[availableWorkerIndex];

		std::unique_lock<std::mutex> lock(queueMutex);

	}

	size_t ThreadManager::getLeastWorkingThread() const {

		std::unique_lock<std::mutex> lock(queueMutex);

		size_t threadIndex = 0;
		size_t leastTaskCount = pool[0].taskCount;

		// Simple linear search to find the thread index
		// with the least task count
		for (size_t i = 1; i < pool.size(); i++) {
			if (pool[i].taskCount < leastTaskCount) {
				threadIndex = i;
				leastTaskCount = pool[i].taskCount;
			}
		}

		lock.unlock();
		condition.notify_one();

		return threadIndex;
	}

	void ThreadManager::createThreadPool(size_t threadCount) {
		// Initialize all working threads
		for (size_t i = 0; i < threadCount; i++) {
			// Create the worker thread struct first
			//pool.emplace_back(true, 0, i, std::thread(), std::set<Task>());
			
			// Initialize and start the thread after the struct is created properly
			pool[i].thread = std::thread(&ThreadManager::workerThread, this, std::ref(pool[i]));
		}
	}

	void ThreadManager::killAll() {
		for (size_t i = 0; i < pool.size(); i++)
			pool[i].isAlive = false;
	}

	void ThreadManager::disposeThreads() {
		// Kills all threads that are alive
		killAll();

		// joins all threads after being killed
		for (auto& threadTask : pool)
			threadTask.thread.join();

		// clears all threads from memory
		pool.clear();
	}

	void ThreadManager::workerThread(WorkingThread& workingThread) {
		
		while (workingThread.isAlive) {

		}
	}
}