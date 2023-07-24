#pragma once

namespace Uranium::Utils {

	/*
	* Position Struct
	* 
	* This structure holds a position
	* as two unsigned intetegers
	*/
	struct Position {
	public:
		uint32_t x;
		uint32_t y;

		explicit Position(uint32_t x, uint32_t y)
			: x(x), y(y)
		{

		}
	};
}