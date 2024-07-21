#pragma once

#include <cstring>

namespace Uranium::DataStructures::Containers {

	template<class Key, class Value> class Entry {
	public:
		/*
		* Construct a an entry by copying
		* the parameters
		*/
		Entry(const Key& key, const Value& value);
		/*
		* Construct an entry inplace
		*/
		Entry(const Key&& key, const Value&& value);
		
		// default constructor
		Entry();
		
		// default destructor
		~Entry();

		/*
		* getters
		*/
		Key& getKey();
		Value& getValue();

		/*
		* setters
		*/
		void setKey(const Key& key);
		void setValue(const Value& value);

		/*
		* compares 'this' entry with target
		* and returns an int. This method is
		* marked as virtual since it can be 
		* overwritten
		*/
		virtual int equals(const Entry<Key, Value>& other);

	private:
		/*
		* private members
		*/
		Key key;
		Value value;
	};

#define ENTRY(returnType) template<class Key, class Value> returnType Entry<Key, Value>

	ENTRY()::Entry(const Key& key, const Value& value) :
		key(key),
		value(value)
	{
		
	}

	ENTRY()::Entry(const Key&& key, const Value&& value) :
		key(key),
		value(value)
	{

	}

	ENTRY()::Entry()
	{

	}

	ENTRY()::~Entry() {

	}

	ENTRY(Key&)::getKey() {
		return key;
	}

	ENTRY(Value&)::getValue() {
		return value;
	}

	ENTRY(void)::setKey(const Key& key) {
		this->key = key;
	}

	ENTRY(void)::setValue(const Value& value) {
		this->value = value;
	}

	ENTRY(int)::equals(const Entry<Key, Value>& other) {
		return memcmp(this, &other, sizeof(Entry<Key, Value>));
	}

}