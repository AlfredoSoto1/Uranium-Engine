#pragma once

namespace Uranium::DataStructures::Containers {

	/*
	* This interface will be implemented to
	* other interfaces or classes that are constructed
	* internally by using an array as its building blocks
	* 
	* Any other data structure built with nodes, will not
	* implement this interface since its not built with a
	* raw array. This interface will be incharge of providing
	* the user the constant raw representation of its data
	* and its capacity.
	*/
	template<class Element> class ArrayVariant {
	public:

		/*
		* Returns the represented data of current
		* structure as a const array.
		*/
		virtual const Element* asArray() = 0;

		/*
		* Returns the actual capacity of current
		* array data structure
		*/
		virtual unsigned int actualCapacity() = 0;
	};
}