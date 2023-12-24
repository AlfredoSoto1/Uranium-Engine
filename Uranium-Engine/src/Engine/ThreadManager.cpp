#include "ThreadManager.h"

namespace Uranium::Engine {

	ThreadManager::ThreadManager() noexcept :
		pool(),
		tasks(),
		stop(false)
	{

	}

	ThreadManager::~ThreadManager() {

	}

	void ThreadManager::enqueTask(const std::function<void()>& functionTask) {
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			tasks.emplace(0L, functionTask);
		}
		condition.notify_one();
	}

	size_t ThreadManager::getThreadWorkload(size_t threadIndex) const {
		return pool[threadIndex].taskCount;
	}

	size_t ThreadManager::getLeastWorkingThread() const {
#ifdef UR_DEBUG
		if (pool.empty())
			throw std::exception("No working thread available!");
#endif // UR_DEBUG

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
#ifdef UR_DEBUG
		if (!pool.empty())
			throw std::exception("Thread pool already created!");
#endif // UR_DEBUG

		// Initialize all working threads
		for (size_t i = 0; i < threadCount; i++)
			pool.emplace_back(true, i, std::thread());

		// Start running all threads
		for (size_t i = 0; i < threadCount; i++)
			pool[i].thread = std::thread(&ThreadManager::workerThread, this, pool[i]);
	}

	void ThreadManager::killAll() {
		for (size_t i = 0; i < pool.size(); i++)
			pool[i].isAlive = false;
	}

	void ThreadManager::disposeThreads() {
#ifdef UR_DEBUG
		if (pool.empty())
			throw std::exception("No working thread to dispose!");
#endif // UR_DEBUG

		// Kills all threads that are alive (if any)
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