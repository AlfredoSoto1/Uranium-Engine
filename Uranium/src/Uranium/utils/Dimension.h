#pragma once

namespace Uranium::Utils {
	
	/*
	* Dimension Struct
	* 
	* This structure holds the dimensions of
	* some X object that may require to be
	* represented as a dimension or contains
	* some dimensions.
	*/
	struct Dimension {
	public:
		uint32_t width;
		uint32_t height;

		explicit Dimension(uint32_t width, uint32_t height) 
			: width(width), height(height)
		{
		
		}
	};
}