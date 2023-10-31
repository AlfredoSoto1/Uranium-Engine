#pragma once

#include "Heap.h"
#include <cmath>
#include <functional>

namespace Uranium::DataStructures::Trees {

	template<class Element> class HeapSetArray : public Heap<Element>{
	public:
		HeapSetArray(unsigned int initialCapacity, double loadFactor, const std::function<int(const Element&, const Element&)>& compare);
		virtual ~HeapSetArray();

		Element* removeRoot();

		unsigned int insert(const Element& obj);

		unsigned int get(const Element& obj);

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		Element* getRoot();

		bool isFull();

		bool isComplete();

		bool isBalanced();

		unsigned int depth();

		unsigned int height();

		void inOrder(const std::function<void(Element*)>& functionTraversal);

		void preOrder(const std::function<void(Element*)>& functionTraversal);

		void postOrder(const std::function<void(Element*)>& functionTraversal);
		
	private:
		/*
		* private methods
		*/
		void swap(unsigned int e1, unsigned int e2);

		void reallocate(unsigned int newCapacity);

	private:
		/*
		* private members
		*/
		double loadFactor;

		unsigned int capacity; 
		unsigned int heapSize; 
		unsigned int initialLevels;
		
		std::function<int(const Element&, const Element&)> compare;

		Element* heapArray;
	};

#define HEAP_SET_ARR(returnType) template<class Element> returnType HeapSetArray<Element>

	HEAP_SET_ARR()::HeapSetArray(unsigned int initialLevels, double loadFactor, const std::function<int(const Element&, const Element&)>& compare) :
		compare(compare),
		loadFactor(loadFactor),
		initialLevels(initialLevels),

		heapSize(0)
	{
		capacity = (unsigned int)std::pow(2, initialLevels + 1);
		heapArray = new Element[capacity];
	}

	HEAP_SET_ARR()::~HeapSetArray() {
		
		clear();
		delete[] heapArray;
	}

	HEAP_SET_ARR(void)::swap(unsigned int e1, unsigned int e2) {
		Element elementCopy = heapArray[e1];
		heapArray[e1] = heapArray[e2];
		heapArray[e2] = std::move(elementCopy);
	}

	HEAP_SET_ARR(void)::reallocate(unsigned int newCapacity) {

		Element* newHeap = new Element[newCapacity];

		// transfer all elements to new array
		for (unsigned int i = 0; i < capacity; i++) {
			newHeap[i] = std::move(heapArray[i]);
		}
		// free old memory
		delete[] heapArray;

		// reset capacity
		capacity = newCapacity;

		// re-define memory with new array
		heapArray = newHeap;
	}

	HEAP_SET_ARR(Element*)::removeRoot() {
		return nullptr;
	}

	HEAP_SET_ARR(unsigned int)::insert(const Element& obj) {

		if ((heapSize / (double)capacity) >= loadFactor)
			reallocate(capacity * 2);
		
		// insert element to the end of the array
		heapArray[heapSize++] = obj;

		unsigned int indexInHeap = heapSize - 1;
		// do an up heap
		while (indexInHeap != 0) {

			unsigned int parentIndex = (unsigned int)std::floor((indexInHeap - 1) / 2.0);

			// compare the parent with child
			if (compare(heapArray[parentIndex], obj) <= 0) {
				return indexInHeap;
			}
			
			// swap parent with child
			swap(parentIndex, indexInHeap);

			// move up in heap
			indexInHeap = parentIndex;
		}
		return indexInHeap;
	}

	HEAP_SET_ARR(unsigned int)::get(const Element& obj) {
		return 0;
	}

	HEAP_SET_ARR(inline unsigned int)::size() {
		return heapSize;
	}

	HEAP_SET_ARR(inline bool)::isEmpty() {
		return heapSize == 0;
	}

	HEAP_SET_ARR(void)::clear() {

		delete[] heapArray;

		heapSize = 0;
		capacity = (unsigned int)std::pow(2, initialLevels + 1);
		heapArray = new Element[capacity];
	}

	HEAP_SET_ARR(Element*)::getRoot() {
		return &heapArray[0];
	}

	HEAP_SET_ARR(bool)::isFull() {
		return (heapSize % 2 == 0);
	}

	HEAP_SET_ARR(bool)::isComplete() {
		return true; // this implementation is always a complete tree
	}

	HEAP_SET_ARR(bool)::isBalanced() {
		return true; // this implementation is always a balanced tree
	}

	HEAP_SET_ARR(unsigned int)::depth() {
		return 0;
	}

	HEAP_SET_ARR(unsigned int)::height() {
		return 0;
	
	}

	HEAP_SET_ARR(void)::inOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}

	HEAP_SET_ARR(void)::preOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}

	HEAP_SET_ARR(void)::postOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}
}