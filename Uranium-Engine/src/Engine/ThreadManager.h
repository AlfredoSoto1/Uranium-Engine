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

		struct Task {
			std::function<void()> task;
			size_t threadIndex;
		};

	private:
		std::vector<std::thread> threads;
		
		std::queue<Task> tasks;
		
		std::mutex queueMutex;
		std::condition_variable condition;
		
		volatile bool stop;
	};
}