#pragma once

#include "Map.h"
#include "DataStructures/Lists/ArrayList.h"
#include "DataStructures/HashTables/HashTableOpenAddress.h"

namespace Uranium::DataStructures::Maps {

	template<class Key, class Value> class HashMap : public Map<Key, Value> {
	public:
		/*
		* custom alias
		*/
		using HashCode = HashTables::HashCode;
		template<class Element> using List = Lists::List<Element>;
		template<class Element> using ArrayList = Lists::ArrayList<Element>;
		
	public:
		HashMap(unsigned int initialCapacity, double loadFactor,
			const std::function<HashCode(const Key&)>& hashFunction,
			const std::function<int(const Key&, const Key&)>& compare);

		virtual ~HashMap();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		bool put(const Key& key, const Value& val);

		Value& get(const Key& key);

		Value remove(const Key& key);

		bool contains(const Key& obj);

		HashCode search(const Key& obj);

	private:
		/*
		* private members
		*/
		struct Bucket {
			Key key;
			unsigned int valueLocation;
		};

		List<Value>* values;
		
		HashTables::HashTableOpenAddress<Bucket>* hashTable;

	};

#define HASH_MAP(returnType) template<class Key, class Value> returnType HashMap<Key, Value>

	HASH_MAP()::HashMap(unsigned int initialCapacity, double loadFactor,
		const std::function<HashCode(const Key&)>& hashFunction,
		const std::function<int(const Key&, const Key&)>& compare)

	{
		// lambda expression used to generate 
		// a hash code from the hash function of a key from a bucket
		auto hashMapFunc = [hashFunction](const Bucket& bucket) {
			return hashFunction(bucket.key); // use bucket key
		};

		// lambda expression used to compare the keys from two buckets
		auto keyComparator = [compare](const Bucket& bucket1, const Bucket& bucket2) {
			return compare(bucket1.key, bucket2.key); // use keys from buckets
		};

		values = new ArrayList<Value>(initialCapacity);
		hashTable = new HashTables::HashTableOpenAddress<Bucket>(initialCapacity, loadFactor, hashMapFunc, keyComparator);
	}

	HASH_MAP()::~HashMap() {
		delete hashTable;
		delete values;
	}

	HASH_MAP(inline unsigned int)::size() {
		return hashTable->size();
	}

	HASH_MAP(inline bool)::isEmpty() {
		return hashTable->isEmpty();
	}

	HASH_MAP(void)::clear() {
		values->clear();
		hashTable->clear();
	}

	HASH_MAP(bool)::put(const Key& key, const Value& val) {

		Bucket bucket = {key, 0};
		// put in the table a bucket with and a reference of zero
		bool isUnique = hashTable->put(bucket);

		// check if the added bucket is unique
		if (isUnique) {
			// if its unique, add the value to
			// the values list and get the bucket
			// to update its reference to the location of
			// the value in the Values list
			values->add(val);

			Bucket* bucket = hashTable->get(bucket);

			bucket->valueLocation = values->size() - 1;
		}
		else {
			// if element is not unique
			// loock for the location in memory of it and
			// update the value from the Values list from the bucket
			Bucket* bucket = hashTable->get(bucket);

			values->set(bucket->valueLocation, val);
		}

		// added successfully
		return true;
	}

	HASH_MAP(Value&):: get(const Key& key) {
		
	}

	HASH_MAP(Value)::remove(const Key& key) {
		
	}

	HASH_MAP(bool)::contains(const Key& obj) {
		return hashTable->get(key) != nullptr;
	}

	HASH_MAP(HashTables::HashCode)::search(const Key& obj) {
		return hashTable->search(obj);
	}
}