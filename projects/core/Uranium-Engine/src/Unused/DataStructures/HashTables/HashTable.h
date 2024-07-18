#pragma once

#include <optional>

#include "HashCode.h"
#include "DataStructures/Containers/Container.h"
#include "DataStructures/Containers/ArrayVariant.h"

namespace Uranium::DataStructures::HashTables {

	template<class Element> class HashTable : public Containers::Container<Element>, public Containers::ArrayVariant<Element> {
	public:
		
		/*
		* returns an optional contaning the Hashcode
		* of an avaliable bucket inside the table.
		* It returns an empty optional if theres not
		* an available bucket for the element parameter
		* this could be because the table is full (temp~>) or has a duplicate
		*/
		virtual std::optional<HashCode> availableHash(char* activeBuckets, unsigned int capacity, const Element& obj) = 0;
		
		/*
		* returns an optional containing the Hashcode
		* of the element inside the table if found.
		* It returns an empty optional if the element was
		* not found in table
		*/
		virtual std::optional<HashCode> searchHash(char* activeBuckets, unsigned int capacity, const Element& obj) = 0;

		/*
		* This rehashes the entire table when it needs
		* more space to fit new data
		*/
		virtual void reHash(unsigned int newCapacity) = 0;

		/*
		* It puts an element in the table with
		* its corresponding position using the hashFunction
		* It will not add duplicate elements to the table 
		* to avoid confusion inside the table
		*/
		virtual std::optional<HashCode> put(const Element& obj) = 0;

		/*
		* Returns the hash code address of 
		* the element in the table
		*/
		virtual std::optional<HashCode> hashOf(const Element& obj) = 0;

		/*
		* Returns the element's address inside the table
		* from the target hashCode address parameter. If
		* element is not in table, it will return nullptr
		*/
		virtual Element* get(const HashCode& hashCodeAddress) = 0;

		/*
		* Returns a boolean (true) - if the element was removed
		* (false) - if the element could not be removed
		*/
		virtual bool remove(const HashCode& hashCodeAddress) = 0;
	};
}