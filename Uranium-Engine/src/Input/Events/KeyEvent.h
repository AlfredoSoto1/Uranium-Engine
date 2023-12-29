#pragma once

#include "Event.h"

namespace Uranium::Events {
	
	class KeyEvent : public Event {
	public:
		int getKeyCode();

	protected:
		explicit KeyEvent(int keyCode) noexcept;
		
	private:
		int keyCode;
	};
}