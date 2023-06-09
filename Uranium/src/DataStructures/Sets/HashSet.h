#pragma once

#include "Set.h"
#include "DataStructures/HashTables/HashTableOpenAddress.h"

namespace Uranium::DataStructures::Sets {

	template<class Element> class HashSet : public Set<Element> {
	public:
		HashSet(unsigned int initialCapacity, double loadFactor, 
			const std::function<HashTables::HashCode(const Element&)>& hashFunction, 
			const std::function<int(const Element&, const Element&)>& compare);
		virtual ~HashSet();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		bool put(const Element& obj);

		bool remove(const Element& obj);

		bool contains(const Element& obj);

		//HashTables::HashCode search(const Element& obj);

	private:
		/*
		* private members
		*/
		HashTables::HashTableOpenAddress<Element>* hashTable;

	};

#define HASH_SET(returnType) template<class Element> returnType HashSet<Element>

	HASH_SET()::HashSet(unsigned int initialCapacity, double loadFactor, 
		const std::function<HashTables::HashCode(const Element&)>& hashFunction,
		const std::function<int(const Element&, const Element&)>& compare) 
	{
		hashTable = new HashTables::HashTableOpenAddress<Element>(initialCapacity, loadFactor, hashFunction, compare);
	}

	HASH_SET()::~HashSet() {
		delete hashTable;
	}

	HASH_SET(inline unsigned int)::size() {
		return hashTable->size();
	}

	HASH_SET(inline bool)::isEmpty() {
		return hashTable->isEmpty();
	}

	HASH_SET(void)::clear() {
		hashTable->clear();
	}

	HASH_SET(bool)::put(const Element& obj) {
		// put element in table		
		std::optional<HashTables::HashCode> hashCodeAddress = hashTable->put(obj);
		// return true if element could be placed in table
		return hashCodeAddress.has_value();
	}

	HASH_SET(bool)::remove(const Element& obj) {
		// obtain hash Address of element
		std::optional<HashTables::HashCode> hashCodeAddress = hashTable->hashOf(obj);

		// return true if element could be removed - false otherwise
		if(hashCodeAddress.has_value())
			return hashTable->remove(hashCodeAddress.value());
		return false;
	}

	HASH_SET(bool)::contains(const Element& obj) {
		std::optional<HashTables::HashCode> hashCodeAddress = hashTable->hashOf(obj);
		// if it has a value, then exists in table
		return hashCodeAddress.has_value();
	}

	//HASH_SET(HashTables::HashCode)::search(const Element& obj) {
	//	return hashTable->search(obj);
	//}

}