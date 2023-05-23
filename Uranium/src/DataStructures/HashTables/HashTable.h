#pragma once

#include <optional>
#include <functional>

#include "HashCode.h"
#include "DataStructures/Containers/Container.h"
#include "DataStructures/Containers/Comparable.h"

namespace Uranium::DataStructures::HashTables {

	template<class Element> class HashTable : public Containers::Container<Element> {
	public:

		/*
		* Returns the hashcode of the given 
		* parameter element
		*/
		virtual HashCode hashOf(const Element& obj) = 0;

		/*
		* It puts the given parameter
		* (Element - obj) inside the hash table
		*/
		virtual void put(HashCode hashCode, const Element& obj) = 0;

		/*
		* Returns an optional containing the possible element
		* inside the table that can be found with the target
		* parameter: hashcode
		*/
		virtual std::optional<Element> get(HashCode hashCode) = 0;

		/*
		* Returns an optional containing the possible element
		* inside the table that can be found with the target
		* It uses a lambda function to compare the element if
		* it matches the one from the hashCode given
		*/
		virtual std::optional<Element> get(HashCode hashCode, const std::function<bool(const Element&)>& testElement) = 0;

		/*
		* It removes the element as an optional inside the table
		* that matches the hashcode provided. It uses a reference
		* of a lambda function to compare the element found using
		* the hashcode. If the elements are not the same once compared
		* then it will use quadratic probing to search
		* for the element in the table. If the element is not found, then
		* returns an empty optional.
		*/
		virtual std::optional<Element> remove(HashCode hashCode, const std::function<bool(const Element&)>& testElement) = 0;

		/*
		* This re-hashes the entire table
		* when it needs to resize
		*/
		virtual void reHash(unsigned int newCapacity) = 0;
	};
}