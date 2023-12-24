#pragma once

#include <mutex>
#include <queue>
#include <vector>
#include <thread>
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

	public:
		/*
		*/
		void enqueTask(const std::function<void()>& functionTask);

	private:
		/*
		* Creates center crontrol that manages
		* all threads in our Application program
		*/
		explicit ThreadManager() noexcept;

		struct Task {
			bool loop;
			std::function<void()> doTask;
		};

		struct WorkingThread {
			bool isAlive;
			size_t taskCount;
			size_t threadIndex;
			std::thread thread;
		};

	private:
		/*
		* Creates a threadpool with the provided
		* count
		*/
		void createThreadPool(size_t threadCount);

		/*
		*/
		void workerThread(WorkingThread& workingThread);

		/*
		* Kills all processes and ends each thread
		*/
		void killAll();

		/*
		* Disposes all the generated threads
		*/
		void disposeThreads();

		/*
		* Returns the threadIndex of which is the
		* one with least tasks assigned.
		*/
		size_t getLeastWorkingThread() const;

	private:
		mutable std::mutex queueMutex;
		mutable std::condition_variable condition;

		std::queue<Task> queuedTasks;
		std::vector<WorkingThread> pool;
	};
}