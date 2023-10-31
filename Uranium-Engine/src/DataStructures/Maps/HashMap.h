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

		std::optional<Value> put(const Key& key, const Value& val);

		Value* get(const Key& key);

		std::optional<Value> remove(const Key& key);

		bool contains(const Key& obj);

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

	HASH_MAP(std::optional<Value>)::put(const Key& key, const Value& val) {

		Bucket bucket = {key, 0};

		// put in the table a bucket with and a reference of zero

		std::optional<HashTables::HashCode> address = hashTable->put(bucket);

		// check if the added bucket is unique
		if (address.has_value()) {
			// if its unique, add the value to
			// the values list and get the bucket
			// to update its reference to the location of
			// the value in the Values list
			values->add(val);

			// get address of element in table
			Bucket* fromTable = hashTable->get(address.value());
			
			// link address to location of list of values
			fromTable->valueLocation = values->size() - 1;

			return {};
		}
		else {
			// if element is not unique
			// loock for the location in memory of it and
			// update the value from the Values list from the bucket
			std::optional<HashTables::HashCode> address = hashTable->hashOf(bucket);

			Bucket* fromTable = hashTable->get(address.value());

			return values->set(fromTable->valueLocation, val);
		}
	}

	HASH_MAP(Value*):: get(const Key& key) {
		Bucket bucket = { key, 0 };

		// put in the table a bucket with and a reference of zero
		std::optional<HashTables::HashCode> address = hashTable->hashOf(bucket);

		if (address.has_value()) {
			Bucket* fromTable = hashTable->get(address.value());

			return &values->get(fromTable->valueLocation);
		}
		return nullptr;
	}

	HASH_MAP(std::optional<Value>)::remove(const Key& key) {
		Bucket bucket = { key, 0 };

		// put in the table a bucket with and a reference of zero
		std::optional<HashTables::HashCode> address = hashTable->hashOf(bucket);

		if (address.has_value()) {
			Bucket* fromTable = hashTable->get(address.value());

			Value valueOut = values->get(fromTable->valueLocation);

			values->remove(fromTable->valueLocation);
			hashTable->remove(address.value());
			
			return valueOut;
		}
		return {};
	}

	HASH_MAP(bool)::contains(const Key& key) {
		Bucket bucket = { key, 0 };
		std::optional<HashTables::HashCode> hashCodeAddress = hashTable->hashOf(bucket);
		// if it has a value, then exists in table
		return hashCodeAddress.has_value();
	}
}