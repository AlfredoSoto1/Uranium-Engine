#pragma once

#include "HashTable.h"

namespace Uranium::DataStructures::HashTables {

	template<class Element> class HashTableOpenAddress : public HashTable<Element> {
	public:
		HashTableOpenAddress(unsigned int initialCapacity, double loadfactor, HashCode(*function)(const Element&));
		virtual ~HashTableOpenAddress();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		HashCode hashOf(const Element& obj);

		void put(HashCode hashCode, const Element& obj);

		std::optional<Element> get(HashCode hashCode);

		std::optional<Element> get(HashCode hashCode, const std::function<bool(const Element&)>& testElement);

		std::optional<Element> remove(HashCode hashCode, const std::function<bool(const Element&)>& testElement);

		void reHash(unsigned int newCapacity);

	private:
		/*
		* private members
		*/
		void quadraticProbing(char* elInitArray, Element* tableArray, unsigned int capacity, HashCode hashCode, const Element& obj);

	private:
		/*
		* private members
		*/
		constexpr static char FREE_MEMORY = 0;
		constexpr static char USED_MEMORY = 1;
		constexpr static char USING_MEMORY = 2;

		char* elInit;
		Element* table;

		HashCode(*function)(const Element&);

		unsigned int capacity;
		unsigned int tableSize;
		unsigned int initialCapacity;

		double loadfactor;
	};

#define HASH_OP(returnType) template<class Element> returnType HashTableOpenAddress<Element>

	HASH_OP()::HashTableOpenAddress(unsigned int initialCapacity, double loadfactor, HashCode(*function)(const Element&)) :
		tableSize(0),
		capacity(initialCapacity),
		initialCapacity(initialCapacity),

		loadfactor(loadfactor),
		function(function)
	{
		elInit = new char[initialCapacity](FREE_MEMORY);
		table = new Element[initialCapacity];
	}

	HASH_OP()::~HashTableOpenAddress() {
		clear();
		delete[] table;
		delete[] elInit;
	}

	HASH_OP(inline unsigned int)::size() {
		return tableSize;
	}

	HASH_OP(inline bool)::isEmpty() {
		return tableSize == 0;
	}

	HASH_OP(void)::clear() {
		// delete old data
		delete[] table;
		delete[] elInit;
		// reset capacity to initial
		capacity = initialCapacity;
		// re-create table with initial capacity
		elInit = new char[capacity](FREE_MEMORY);
		table = new Element[capacity];
		// reset size to zero
		tableSize = 0;
	}

	HASH_OP(HashCode)::hashOf(const Element& obj) {
		return function(obj);
	}

	HASH_OP(void)::put(HashCode hashCode, const Element& obj) {

		// increase table size
		tableSize++;

		// increase 100%
		if ((tableSize / (double)capacity) >= loadfactor)
			reHash(capacity * 2);

		// do probing to put elements in table
		quadraticProbing(elInit, table, capacity, hashCode, obj);
	}

	HASH_OP(std::optional<Element>)::get(HashCode hashCode) {
		if(elInit[hashCode] == USING_MEMORY)
			return table[hashCode];
		return {};
	}

	HASH_OP(std::optional<Element>)::get(HashCode hashCode, const std::function<bool(const Element&)>& testElement) {
		// if hashcode points to
		// an invalid memory, return empty optional
		if (elInit[hashCode] == FREE_MEMORY)
			return {};

		for (HashCode i = 0; i < capacity; i++) {
			// generate index with quadratic probing
			HashCode quadraticProbIndex = (hashCode + i * i) % capacity;
			// if hashcode points to an invalid memory,
			// finish the probing, since element is not
			// in the table
			if (elInit[quadraticProbIndex] == FREE_MEMORY)
				return {};

			// compare; If they are not equal, continue
			// the quadratic probing
			if (!testElement(table[quadraticProbIndex]) || elInit[quadraticProbIndex] == USED_MEMORY)
				continue;

			return table[quadraticProbIndex];
		}
		// return by default and empty optional
		// this happens when we traversed the entire table
		// and there was no element found
		return {};
	}

	HASH_OP(std::optional<Element>)::remove(HashCode hashCode, const std::function<bool(const Element&)>& testElement) {
		
		// if hashcode points to
		// an invalid memory, return empty optional
		if (elInit[hashCode] == FREE_MEMORY)
			return {};

		for (HashCode i = 0; i < capacity; i++) {
			// generate index with quadratic probing
			HashCode quadraticProbIndex = (hashCode + i * i) % capacity;
			// if hashcode points to an invalid memory,
			// finish the probing, since element is not
			// in the table
			if (elInit[quadraticProbIndex] == FREE_MEMORY)
				return {};

			// compare; If they are not equal, continue
			// the quadratic probing
			if (!testElement(table[quadraticProbIndex]) || elInit[quadraticProbIndex] == USED_MEMORY)
				continue;

			// unlink table content
			elInit[quadraticProbIndex] = USED_MEMORY;
			
			return table[quadraticProbIndex];
		}
		// return by default and empty optional
		// this happens when we traversed the entire table
		// and there was no element found
		return {};
	}

	HASH_OP(void)::reHash(unsigned int newCapacity) {
		Element* newTable = new Element[newCapacity];
		char* elInitTemp = new char[newCapacity](FREE_MEMORY);

		// transfer all elements to new table
		for (HashCode i = 0; i < capacity; i++) {
			// skip if bucket is not being used
			if (elInit[i] != USING_MEMORY)
				continue;
			// generate new hashCode for element
			HashCode newCode = hashOf(table[i]);
			
			// do the probing to put
			// element to new table
			quadraticProbing(elInitTemp, newTable, newCapacity, newCode, table[i]);
		}
		// free old memory
		delete[] table;
		delete[] elInit;

		// re-define memory with new array
		table = newTable;
		elInit = elInitTemp;

		// reset capacity
		capacity = newCapacity;
	}

	HASH_OP(void)::quadraticProbing(char* elInitArray, Element* tableArray, unsigned int capacity, HashCode hashCode, const Element& obj) {
		for (HashCode i = 0; i < capacity; i++) {
			// generate index with quadratic probing
			HashCode quadraticProbIndex = (hashCode + i * i) % capacity;
			if (elInitArray[quadraticProbIndex] == USING_MEMORY)
				continue;
			// put element
			tableArray[quadraticProbIndex] = std::move(obj);
			// set flag to USING_MEMORY
			// since we initialized this block of memory
			elInitArray[quadraticProbIndex] = USING_MEMORY;
			// exit loop
			break;
		}
	}
}