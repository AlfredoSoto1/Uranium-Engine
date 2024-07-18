#pragma once

#include <memory>

namespace Uranium::States {
	class State;
}

namespace Uranium::Engine {

	class StateManager final {
	public:
		friend class BaseEngine;

	public:
		~StateManager();

		/*
		* Delete the copy/move constructor since
		* there must be one scene manager instance
		* recognized by the engine
		*/
		StateManager(StateManager&) = delete;
		StateManager(StateManager&&) = delete;
		StateManager& operator=(const StateManager&) = delete;

	private:
		/*
		* Creates center crontrol that manages
		* all states in our Application program
		*/
		explicit StateManager() noexcept;

	private:
		std::shared_ptr<States::State> currentState;
	};
}