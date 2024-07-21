#pragma once

#include "Event.h"

namespace Uranium::Input::Callbacks {
	class CursorCallback;
}

namespace Uranium::Input::Events {

	class CursorEnteredEvent final : public Event {
	public:
		friend Callbacks::CursorCallback;

		/*
		*
		*/
		explicit CursorEnteredEvent(bool entered) noexcept :
			Event(EventType::CURSOR_ENTERED),
			entered(entered)
		{

		}

		~CursorEnteredEvent() = default;

	public:
		bool hasEntered() const {
			return entered;
		}

	private:
		bool entered;
	};

}