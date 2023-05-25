#pragma once

#include "DataStructures/Containers/Container.h"

namespace Uranium::DataStructures::Sets {

	template<class Element> class Set : public Containers::Container<Element> {
	public:

		/*
		* puts element in the set
		*/
		virtual bool put(const Element& obj) = 0;
		
		/*
		* removes element from set
		*/
		virtual bool remove(const Element& obj) = 0;

		/*
		* returns a boolean whether if the target
		* element is in the set
		*/
		virtual bool contains(const Element& obj) = 0;
	};
}