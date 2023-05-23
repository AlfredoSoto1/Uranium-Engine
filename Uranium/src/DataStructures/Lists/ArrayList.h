#pragma once
	
#include "List.h"

#include <cstring>
#include <stdexcept>

namespace Uranium::DataStructures::Lists {

	constexpr unsigned int INITIAL_CAPACITY = 10;

	template<class Element> class ArrayList : public List<Element> {
	public:
		ArrayList();
		ArrayList(unsigned int initialCapacity);
		~ArrayList();

		inline unsigned int size();
		
		inline bool isEmpty();

		void add(const Element& obj);

		void add(unsigned int index, const Element& obj);

		Element& get(unsigned int index);

		Element set(int index, const Element& obj);

		void removeIndex(unsigned int index);

		bool remove(const Element& obj);

		bool contains(const Element& obj);

		void clear();

		unsigned int removeAll(const Element& obj);

		unsigned int firstIndex(const Element& obj);

		unsigned int lastIndex(const Element & obj);

		Element& first();

		Element& last();

	private:
		/*
		* private methods
		*/
		void reallocate(unsigned int newCapacity);

	private:
		/*
		* private members
		*/
		Element* elements;

		unsigned int capacity;
		unsigned int arraySize;
	};

#define ARRAY_LIST(returnType) template <class Element> returnType ArrayList<Element>

	ARRAY_LIST()::ArrayList() {
		elements = new Element[INITIAL_CAPACITY];
		arraySize = 0;
		capacity = INITIAL_CAPACITY;
	}

	ARRAY_LIST()::ArrayList(unsigned int initialCapacity) {
		elements = new Element[initialCapacity];
		arraySize = 0;
		capacity = initialCapacity;
	}

	ARRAY_LIST()::~ArrayList() {
		
		// clear the list
		clear();

		// delete array
		delete[] elements;
	}

	ARRAY_LIST(void)::reallocate(unsigned int newCapacity) {
		Element* temp = new Element[newCapacity];

		// transfer all elements to new array
		for (unsigned int i = 0; i < capacity; i++) {
			temp[i] = std::move(elements[i]);
		}
		// free old memory
		delete[] elements;

		// re-define memory with new array
		elements = temp;

		// reset capacity
		capacity = newCapacity;
	}

	ARRAY_LIST(inline unsigned int)::size() {
		return arraySize;
	}

	ARRAY_LIST(inline bool)::isEmpty() {
		return arraySize == 0;
	}

	ARRAY_LIST(void)::add(const Element& obj) {

		// increase 50%
		if (arraySize == capacity)
			reallocate(capacity + capacity / 2);

		// add element to list
		elements[arraySize++] = obj;
	}

	ARRAY_LIST(void)::add(unsigned int index, const Element& obj) {
		// Check bounds
		if (index < 0 || index >= arraySize)
			throw std::range_error("Index is out of bounds!");
		
		// Expand array by 50%
		if (arraySize == capacity)
			reallocate(capacity + capacity / 2);
		
		// Shift values to the right
		for (unsigned int i = arraySize; i > index; i--)
			elements[i] = std::move(elements[i - 1]);
		
		// Place new value
		elements[index] = obj;
		
		// Increase size
		arraySize++;
	}

	ARRAY_LIST(Element&)::get(unsigned int index) {
		
		// Check bounds
		if (index < 0 || index >= arraySize)
			throw std::range_error("Index is out of bounds!");
		// return value
		return elements[index];
	}

	ARRAY_LIST(Element)::set(int index, const Element& obj) {

		// Check bounds
		if (index < 0 || index >= arraySize)
			throw std::range_error("Index is out of bounds!");
		// Get value being replaced
		Element oldValue = elements[index];
		// Update value
		elements[index] = obj;
		// Return old value
		return oldValue;
	}

	ARRAY_LIST(void)::removeIndex(unsigned int index) {
		// Check bounds
		if (index < 0 || index >= arraySize)
			throw std::range_error("Index is out of bounds!");
		// Shift values to the left
		for (unsigned int i = index; i < arraySize - 1; i++)
			elements[i] = std::move(elements[i + 1]);
		// Decrease size
		arraySize--;
	}

	ARRAY_LIST(bool)::remove(const Element& obj) {
		// Find the FIRST instance of the obj in the array to remove it
		for (int i = 0; i < arraySize; i++) {
			if (memcmp(&elements[i], &obj, sizeof(Element)) == 0) {
				removeIndex(i);
				return true;
			}
		}
		// Did not find obj to remove
		return false;
	}

	ARRAY_LIST(bool)::contains(const Element& obj) {
		// Search the array for obj
		for (int i = 0; i < arraySize; i++) {
			// if found we are done
			if (memcmp(&elements[i], &obj, sizeof(Element)) == 0)
				return true;
		}
		// Was not found
		return false;
	}

	ARRAY_LIST(void)::clear() {
		
		// delete old data
		delete[] elements;

		// create smaller array
		// to return back to default
		elements = new Element[INITIAL_CAPACITY];

		// reset size and capacity
		capacity = INITIAL_CAPACITY;
		arraySize = 0;
	}

	ARRAY_LIST(unsigned int)::removeAll(const Element& obj) {
		unsigned int count = 0;
		while (remove(obj))
			count++;
		return count;
	}

	ARRAY_LIST(unsigned int)::firstIndex(const Element& obj) {
		// Search for obj
		for (unsigned int i = 0; i < arraySize; i++) {
			// If found we are done
			if (memcmp(&elements[i], &obj, sizeof(Element)) == 0)
				return i;
		}
		// Wasn't found
		return -1;
	}

	ARRAY_LIST(unsigned int)::lastIndex(const Element& obj) {
		// Search for obj
		// To be more efficient we start from position size-1 and move towards 0
		for (unsigned int i = arraySize - 1; i >= 0; i--) {
			// If found we are done
			if (memcmp(&elements[i], &obj, sizeof(Element)) == 0)
				return i;
		}
		// Wasn't found
		return -1;
	}

	ARRAY_LIST(Element&)::first() {
		if (isEmpty())
			throw std::runtime_error("No such element in list.");
		return elements[0];
	}

	ARRAY_LIST(Element&)::last() {
		if (isEmpty())
			throw std::runtime_error("No such element in list.");
		return elements[arraySize - 1];
	}
}