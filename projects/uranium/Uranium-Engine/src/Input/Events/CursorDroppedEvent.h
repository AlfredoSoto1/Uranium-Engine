#pragma once

#include <string>
#include <vector>
#include "Event.h"

namespace Uranium::Input::Callbacks {
	class CursorCallback;
}

namespace Uranium::Input::Events {

	class CursorDroppedEvent final : public Event {
	public:
		friend Callbacks::CursorCallback;

		/*
		*
		*/
		explicit CursorDroppedEvent() noexcept :
			Event(EventType::CURSOR_DROPPED),
			droppedPaths()
		{

		}

		~CursorDroppedEvent() {
			droppedPaths.clear();
		}

	public:
		const std::vector<std::string>& getDroppedPaths() const {
			return droppedPaths;
		}

	private:
		std::vector<std::string> droppedPaths;
	};
}