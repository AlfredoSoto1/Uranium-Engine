#include "State.h"

namespace Uranium::States {

	State::State() noexcept :
		finished(false),
		nextState(nullptr)
	{

	}

	State::~State() {

	}

	bool State::hasFinished() const {
		return finished;
	}

	std::shared_ptr<State> State::getNextState() const {
		return nextState;
	}

	void State::setNextState(std::shared_ptr<State> next) {
		nextState = next;
	}
}
