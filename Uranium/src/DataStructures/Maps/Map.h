#pragma once

#include "DataStructures/HashTables/HashCode.h"
#include "DataStructures/Containers/Container.h"

namespace Uranium::DataStructures::Maps {

	template<class Key, class Value> class Map : public Containers::Container<Key> {
	public:

		/*
		* puts Key and value in the map
		*/
		virtual bool put(const Key& key, const Value& val) = 0;
		
		/*
		* Returns the value mapped to the key.
		* If key is not in the map, it will throw 
		* and exception.
		*/
		virtual Value& get(const Key& key) = 0;

		/*
		* removes key from map and returns
		* a copy of the value to be removed
		*/
		virtual Value remove(const Key& key) = 0;

		/*
		* returns a boolean whether if the target
		* element is in the map
		*/
		virtual bool contains(const Key& obj) = 0;

		/*
		* It will return the HashCode of the element
		* inside the table if it exists. If such element
		* is not in table, it will throw an exception
		*/
		virtual HashTables::HashCode search(const Key& obj) = 0;
	};
}