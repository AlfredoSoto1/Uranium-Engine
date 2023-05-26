#pragma once

#include "DataStructures/HashTables/HashCode.h"
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

		/*
		* It will return the HashCode of the element
		* inside the table if it exists. If such element
		* is not in table, it will throw an exception
		*/
		virtual HashTables::HashCode search(const Element& obj) = 0;
	};
}