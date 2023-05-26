#pragma once

#include <functional>

#include "HashTable.h"

namespace Uranium::DataStructures::HashTables {

	template<class Element> class HashTableOpenAddress : public HashTable<Element> {
	public:
		HashTableOpenAddress(unsigned int initialCapacity, double loadfactor,
			const std::function<HashCode(const Element&)>&,
			const std::function<int(const Element&, const Element&)>&);
		virtual ~HashTableOpenAddress();

		const Element* asArray();

		unsigned int actualCapacity();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		std::optional<HashCode> availableHash(char* activeBuckets, unsigned int capacity, const Element& obj);

		std::optional<HashCode> searchHash(char* activeBuckets, unsigned int capacity, const Element& obj);

		bool put(const Element& obj);

		Element* get(const Element& obj);

		HashCode search(const Element& obj);

		bool remove(const Element& obj);

		void reHash(unsigned int newCapacity);

	private:
		/*
		* private members
		*/
		constexpr static char FREE_MEMORY = 0;
		constexpr static char USED_MEMORY = 1;
		constexpr static char USING_MEMORY = 2;

		char* activeBucket;
		Element* table;

		std::function<int(const Element&, const Element&)> comparator;

		std::function<HashCode(const Element&)> hashCodeFunction;

		unsigned int capacity;
		unsigned int tableSize;
		unsigned int initialCapacity;

		double loadfactor;
	};

#define HASH_OP(returnType) template<class Element> returnType HashTableOpenAddress<Element>

	HASH_OP()::HashTableOpenAddress(unsigned int initialCapacity, double loadfactor,
		const std::function<HashCode(const Element&)>& hashCodeFunction, const std::function<int(const Element&, const Element&)>& comparator) :
		tableSize(0),
		capacity(initialCapacity),
		initialCapacity(initialCapacity),

		loadfactor(loadfactor),
		comparator(comparator),
		hashCodeFunction(hashCodeFunction)
	{
		activeBucket = new char[initialCapacity](FREE_MEMORY);
		table = new Element[initialCapacity];
	}

	HASH_OP()::~HashTableOpenAddress() {
		clear();
		delete[] table;
		delete[] activeBucket;
	}

	HASH_OP(const Element*)::asArray() {
		return table;
	}

	HASH_OP(unsigned int)::actualCapacity() {
		return capacity;
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
		delete[] activeBucket;
		// reset capacity to initial
		capacity = initialCapacity;
		// re-create table with initial capacity
		activeBucket = new char[capacity](FREE_MEMORY);
		table = new Element[capacity];
		// reset size to zero
		tableSize = 0;
	}

	HASH_OP(std::optional<HashCode>)::availableHash(char* activeBuckets, unsigned int capacity, const Element& obj) {

		// generate a hashCode with function
		HashCode hashCode = hashCodeFunction(obj) % capacity;

		// if active bucket is available
		// return its hashCode
		if (activeBuckets[hashCode] == FREE_MEMORY || activeBuckets[hashCode] == USED_MEMORY)
			return hashCode;

		// do quadratic probing to search for
		// free buckets that include free memory or used
		for (HashCode i = 0; i < capacity; i++) {
			// generate new hashCode for quadratic probing
			HashCode quadraticProbIndex = (hashCode + i * i) % capacity;
			// check if its a free bucket or used
			// and return its hashCode address
			if (activeBuckets[quadraticProbIndex] == FREE_MEMORY || activeBuckets[quadraticProbIndex] == USED_MEMORY)
				return quadraticProbIndex;

			// if we try to put the same exact element
			// in the table, it will return an empty optional
			// since elements have to be unique so they generate
			// a unique hashCode and avoid confusion in the program
			if (comparator(obj, table[quadraticProbIndex]) == 0)
				return {};
		}
		// return empty optional
		// if no hashCode could be found for given element
		// in this case, HashTable should reHash
		return {};
	}

	HASH_OP(std::optional<HashCode>)::searchHash(char* activeBuckets, unsigned int capacity, const Element& obj) {

		// generate a hashCode with function
		HashCode hashCode = hashCodeFunction(obj) % capacity;

		// if generated hashCode points to
		// an empty bucket, return empty optional
		// since there is no need to search further
		if (activeBuckets[hashCode] == FREE_MEMORY)
			return {};

		// do quadratic probing to search for
		// the target Element parameter
		for (HashCode i = 0; i < capacity; i++) {
			// generate new hashCode for quadratic probing
			HashCode quadraticProbIndex = (hashCode + i * i) % capacity;

			// if current bucket points to empty block of memory,
			// return empty optional, since we probe until it wasn't found
			if (activeBuckets[quadraticProbIndex] == FREE_MEMORY)
				return {};

			// Check if bucket from table is not the same from 
			// target Element. If they are not the same, continue searching
			// also if the bucket points to used memory, continue searching aswell
			if (activeBuckets[quadraticProbIndex] == USED_MEMORY)
				continue;
			if (comparator(obj, table[quadraticProbIndex]) != 0)
				continue;

			// return hashCode for the 
			// found element in table
			return quadraticProbIndex;
		}
		// return empty optional
		// if no hashCode could be found for given element
		// in this case, HashTable should reHash
		return {};
	}

	HASH_OP(bool)::put(const Element& obj) {

		// increase table size
		tableSize++;

		// increase 100%
		if ((tableSize / (double)capacity) >= loadfactor)
			reHash(capacity * 2);

		// obtain hashCode address after reHash condition
		std::optional<HashCode> availableAddress = availableHash(activeBucket, capacity, obj);

		if(!availableAddress.has_value())
			return false; // element is duplicated

		// put element
		table[availableAddress.value()] = std::move(obj);
		// set flag to USING_MEMORY
		// since we initialized this block of memory
		activeBucket[availableAddress.value()] = USING_MEMORY;

		return true;
	}

	HASH_OP(Element*)::get(const Element& obj) {

		// look for hashCode in table of element
		std::optional<HashCode> hashCode = searchHash(activeBucket, capacity, obj);

		// element not in table
		// return nullptr
		if (!hashCode.has_value())
			return nullptr;

		// return the address of element in table
		return &table[hashCode.value()];
	}

	HASH_OP(HashCode)::search(const Element& obj) {

		// look for hashCode in table of element
		std::optional<HashCode> hashCode = searchHash(activeBucket, capacity, obj);

		// element not in table
		// return nullptr
		if (!hashCode.has_value())
			throw std::invalid_argument("Target Element is not in table");

		// return hashCode of element in table
		return hashCode.value();
	}

	HASH_OP(bool)::remove(const Element& obj) {
		
		// look for hashCode in table of element
		std::optional<HashCode> hashCode = searchHash(activeBucket, capacity, obj);

		// element not in table
		// return nullptr
		if (!hashCode.has_value())
			return false;

		// Check if element is active in bucket
		// if not return empty optional since its not in table
		if (activeBucket[hashCode.value()] != USING_MEMORY)
			return false;

		// turn USED_MEMORY flag on for this bucket
		activeBucket[hashCode.value()] = USED_MEMORY;

		// reduce size
		tableSize--;
		// return the address of element in table
		return true;
	}

	HASH_OP(void)::reHash(unsigned int newCapacity) {
		Element* newTable = new Element[newCapacity];
		char* activeBucketTemp = new char[newCapacity](FREE_MEMORY);

		// transfer all elements to new table
		for (HashCode i = 0; i < capacity; i++) {
			// skip if bucket is not being used
			if (activeBucket[i] != USING_MEMORY)
				continue;

			// obtain hashCode address
			std::optional<HashCode> availableAddress = availableHash(activeBucketTemp, newCapacity, table[i]);

			if (!availableAddress.has_value())
				break; // throw error

			// put element
			newTable[availableAddress.value()] = std::move(table[i]);
			// set flag to USING_MEMORY
			// since we initialized this block of memory
			activeBucketTemp[availableAddress.value()] = USING_MEMORY;
		}
		// free old memory
		delete[] table;
		delete[] activeBucket;

		// re-define memory with new array
		table = newTable;
		activeBucket = activeBucketTemp;

		// reset capacity
		capacity = newCapacity;
	}
}