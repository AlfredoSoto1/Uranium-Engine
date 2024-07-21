#pragma once

#include "Event.h"

namespace Uranium::Input::Events {

	class EventDispatcher {
	public:
		explicit EventDispatcher() noexcept;

		~EventDispatcher();

	public:
		template<class T>
		void dispatch(const Event& event) {
			if(event.getEventType() == Event)
		}

	private:

	};
}