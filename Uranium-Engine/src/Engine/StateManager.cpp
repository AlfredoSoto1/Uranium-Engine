#include "States/State.h"
#include "StateManager.h"

namespace Uranium::Engine {

	StateManager::StateManager() noexcept :
		currentState(nullptr)
	{
	}

	StateManager::~StateManager() {
	
	}
}

