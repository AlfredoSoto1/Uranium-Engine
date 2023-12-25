#include "ThreadManager.h"

namespace Uranium::Engine {

	ThreadManager::ThreadManager() noexcept :
		threadPool(),
		threadWorkers()
	{

	}

	ThreadManager::~ThreadManager() {
		disposeThreads();
	}

	void ThreadManager::enqueTask(const std::function<void()>& functionTask) {

		// Gets the least working thread index
		size_t availableWorkerIndex = getLeastWorkingThread();

		// Gets the worker assigned to such thread
		Worker& worker = threadWorkers[availableWorkerIndex];

		std::unique_lock<std::mutex> lock(queueMutex);

		// Pass the function task to the worker
		worker.tasks.push_back(functionTask);
	}

	size_t ThreadManager::getLeastWorkingThread() const {

		std::unique_lock<std::mutex> lock(queueMutex);

		size_t threadIndex = 0;
		size_t leastTaskCount = threadWorkers[0].taskCount;

		// Simple linear search to find the thread index
		// with the least task count
		for (size_t i = 1; i < threadWorkers.size(); i++) {
			if (threadWorkers[i].taskCount < leastTaskCount) {
				threadIndex = i;
				leastTaskCount = threadWorkers[i].taskCount;
			}
		}

		lock.unlock();
		condition.notify_one();

		return threadIndex;
	}

	void ThreadManager::createThreadPool(size_t threadCount) {
		// Initialize all working threads
		for (size_t i = 0; i < threadCount; i++) {
			threadWorkers.emplace_back(true, 0, i, std::vector<Task>());
			
			// Initialize and start the thread after the struct is created properly
			threadPool[i] = std::thread(&ThreadManager::executeWork, this, std::ref(threadWorkers.back()));
		}
	}

	void ThreadManager::killAll() {
		std::unique_lock<std::mutex> lock(queueMutex);

		for (size_t i = 0; i < threadWorkers.size(); i++)
			threadWorkers[i].isAlive = false;

		lock.unlock();
		condition.notify_one();
	}

	void ThreadManager::disposeThreads() {
		// Kills all threads that are alive
		killAll();

		// joins all threads after being killed
		for (auto& thread : threadPool)
			thread.join();

		// clears all threads from memory
		threadPool.clear();
		threadWorkers.clear();
	}

	void ThreadManager::executeWork(Worker& worker) {
		
		while (worker.isAlive) {

		}
	}
}