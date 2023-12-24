#pragma once

#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>
#include <condition_variable>

namespace Uranium::Engine {

	class ThreadManager final {
	public:
		friend class BaseEngine;

	public:
		~ThreadManager();

		/*
		* Delete the copy/move constructor since
		* there must be one scene manager instance
		* recognized by the engine
		*/
		ThreadManager(ThreadManager&) = delete;
		ThreadManager(ThreadManager&&) = delete;
		ThreadManager& operator=(const ThreadManager&) = delete;

	private:
		/*
		* Creates center crontrol that manages
		* all threads in our Application program
		*/
		explicit ThreadManager() noexcept;

		/*
		* Struct definition of a task that an
		* individual thread can work on
		*/
		struct Task {
			size_t threadIndex;
			std::function<void()> task;
		};

		struct WorkingThread {
			volatile bool isAlive;
			size_t taskCount;
			std::thread thread;
		};

	private:

		void enqueTask(const std::function<void()>& functionTask);

		/*
		* Returns the number workload in the provided thread index
		*/
		size_t getThreadWorkload(size_t threadIndex) const;

		/*
		* Returns the threadIndex of which is the
		* one with least tasks assigned.
		*/
		size_t getLeastWorkingThread() const;

		/*
		* Creates a threadpool with the provided
		* count
		*/
		void createThreadPool(size_t threadCount);

		/*
		* Kills all processes and ends each thread
		*/
		void killAll();

		/*
		* Disposes all the generated threads
		*/
		void disposeThreads();

		/*
		*/
		void workerThread(WorkingThread& workingThread);

	private:
		std::vector<WorkingThread> pool;
		
		std::queue<Task> tasks;
		
		mutable std::mutex queueMutex;
		mutable std::condition_variable condition;
		
		volatile bool stop;
	};
}