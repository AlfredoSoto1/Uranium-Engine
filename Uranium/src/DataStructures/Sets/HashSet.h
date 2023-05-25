#pragma once

#include "Set.h"
#include "DataStructures/HashTables/HashTableOpenAddress.h"

namespace Uranium::DataStructures::Sets {

	template<class Element> class HashSet : public Set<Element> {
	public:
		HashSet(unsigned int initialCapacity, double loadFactor, const std::function<int(const Element&, const Element&)>& compare);
		virtual ~HashSet();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		bool put(const Element& obj);

		bool remove(const Element& obj);

		bool contains(const Element& obj);

	private:
		/*
		* private members
		*/
		HashTables::HashTableOpenAddress<Element>* vertices;

	};

#define HASH_SET(returnType) template<class Element> returnType HashSet<Element>

	HASH_SET()::HashSet(unsigned int initialCapacity, double loadFactor, const std::function<int(const Element&, const Element&)>& compare) {
		
		std::hash<Element> elementHasher;
		auto hashFunction = [elementHasher](const Element& obj) {
			return elementHasher(obj);
		};

		vertices = new HashTables::HashTableOpenAddress<Element>(initialCapacity, loadFactor, hashFunction, compare);
	}

	HASH_SET()::~HashSet() {
		delete vertices;
	}

	HASH_SET(inline unsigned int)::size() {
		return vertices->size();
	}

	HASH_SET(inline bool)::isEmpty() {
		return vertices->isEmpty();
	}

	HASH_SET(void)::clear() {
		vertices->clear();
	}

	HASH_SET(bool)::put(const Element& obj) {
		return vertices->put(obj);
	}

	HASH_SET(bool)::remove(const Element& obj) {
		return vertices->remove(obj);
	}

	HASH_SET(bool)::contains(const Element& obj) {
		return vertices->get(obj) != nullptr;
	}

}