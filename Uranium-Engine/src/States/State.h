#pragma once

#include <memory>

namespace Uranium::Engine {
	class StateManager;
}

namespace Uranium::Scene {
	class Scene;
}

namespace Uranium::States {

	class State {
	public:
		friend Engine::StateManager;

	public:
		/*
		* Returns true if the current state has finished
		*/
		bool hasFinished() const;

		/*
		* Returns a reference of the next state to be changed
		*/
		std::shared_ptr<State> getNextState() const;

	public:
		/*
		* Sets the next state to be changed after event
		*/
		void setNextState(std::shared_ptr<State> next);

	protected:
		/*
		* Construct an abstract State
		*/
		explicit State() noexcept;

		virtual ~State();

	protected:
		/*
		* Updates the state
		*/
		virtual void update() = 0;

		/*
		* Resets the state content
		*/
		virtual void reset() = 0;

	private:
		bool finished;

		std::shared_ptr<State> nextState;
	};
}