#pragma once

#include <cmath>
#include "BinarySearchTree.h"

namespace Uranium::DataStructures::Trees {

	template<class Element> class BSTArray : public BinarySearchTree<Element> {
	public:
		BSTArray(unsigned int initialCapacity, double loadFactor, const std::function<int(const Element& obj1, const Element& obj2)>& compare);
		virtual ~BSTArray();

		void add(const Element& obj);
		void remove(const Element& obj);
		bool contains(const Element& obj);

		Element* getRoot();

		bool isFull();

		bool isComplete();

		bool isBalanced();

		unsigned int depth();

		unsigned int height();

		void complete();

		void inOrder(const std::function<void(Element*)>& functionTraversal);

		void preOrder(const std::function<void(Element*)>& functionTraversal);

		void postOrder(const std::function<void(Element*)>& functionTraversal);

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

	private:
		/*
		* private methods
		*/
		void completeReallocation(unsigned int newCapacity);

		unsigned int left(unsigned int index);
		unsigned int right(unsigned int index);
		unsigned int parent(unsigned int index);

	private:
		/*
		* private members
		*/
		constexpr static char FREE_MEMORY = 0;
		constexpr static char USED_MEMORY = 1;
		constexpr static char USING_MEMORY = 2;

		unsigned int bstSize;
		unsigned int capacity;
		unsigned int initialCapacity;

		double loadFactor;

		Element* treeArray;
		char* availableRoot;

		std::function<int(const Element&, const Element&)> compare;

	};

#define BST_ARRAY(returnType) template<class Element> returnType BSTArray<Element>

	BST_ARRAY()::BSTArray(unsigned int initialCapacity, double loadFactor, const std::function<int(const Element& obj1, const Element& obj2)>& compare) :
		bstSize(0),
		loadFactor(loadFactor),
		initialCapacity(initialCapacity),

		compare(compare)
	{
		capacity = initialCapacity;
		treeArray = new Element[initialCapacity];
		availableRoot = new char[initialCapacity](FREE_MEMORY);
	}
	BST_ARRAY()::~BSTArray() {
		clear();
		delete[] treeArray;
		delete[] availableRoot;
	}

	BST_ARRAY(unsigned int)::left(unsigned int index) {
		return 2 * index + 1;
	}

	BST_ARRAY(unsigned int)::right(unsigned int index) {
		return 2 * index + 2;
	}

	BST_ARRAY(unsigned int)::parent(unsigned int index) {
		return (unsigned int)std::floor((index - 1) / 2.0);
	}

	BST_ARRAY(void)::completeReallocation(unsigned int newCapacity) {
		Element* newTree = new Element[newCapacity];
		char* newRoots = new char[newCapacity](FREE_MEMORY);

		for (unsigned int i = 0; i < capacity; i++) {
			newTree[i] = std::move(treeArray[i]);
			newRoots[i] = availableRoot[i];
		}

		delete[] treeArray;
		delete[] availableRoot;

		capacity = newCapacity;

		treeArray = newTree;
		availableRoot = newRoots;
	}

	BST_ARRAY(void)::add(const Element& obj) {
		
		std::cout << " ========= " << std::endl;
		for (unsigned int i = 0; i < capacity; i++)
		{
			std::cout << treeArray[i] << " -- " << (int)availableRoot[i] << std::endl;
		}
		std::cout << " ========= " << std::endl;

		unsigned int indexInTree = 0;

		if (isEmpty()) {
			// if BST is empty, just add the element
			treeArray[indexInTree] = std::move(obj);
			availableRoot[indexInTree] = USING_MEMORY;
			bstSize++;
			return;
		}
		
		// if size of tree is greater than the load
		// factor, then it has to resize in a complete tree
		if ((bstSize / (double)capacity) >= loadFactor)
			completeReallocation(capacity * 2);

		while (true) {

			std::cout << treeArray[indexInTree] << " -- " << (int)availableRoot[indexInTree] << std::endl;

			int comparisonResult = compare(treeArray[indexInTree], obj);

			// If they are the same, return because 
			// a set must not have duplicates
			if (comparisonResult == 0)
				break;

			if (comparisonResult > 0) {
				// move to left node of tree
				indexInTree = left(indexInTree);
			}
			else {
				// move to right node of tree
				indexInTree = right(indexInTree);
			}

			// check if node is free of data
			if (availableRoot[indexInTree] == FREE_MEMORY || availableRoot[indexInTree] == USED_MEMORY) {
				// if free of data, insert data
				treeArray[indexInTree] = std::move(obj);
				availableRoot[indexInTree] = USING_MEMORY;
				bstSize++;
				// end traversal
				break;
			}
		}

	}
	BST_ARRAY(void)::remove(const Element& obj) {
	
	}
	BST_ARRAY(bool)::contains(const Element& obj) {
		return false;
	}

	BST_ARRAY(Element*)::getRoot() {
		return nullptr;
	}

	BST_ARRAY(bool)::isFull() {
		return false;
	}

	BST_ARRAY(bool)::isComplete() {
		return false;
	}

	BST_ARRAY(bool)::isBalanced() {
		return false;
	}

	BST_ARRAY(unsigned int)::depth() {
		return 0;
	}

	BST_ARRAY(unsigned int)::height() {
		return 0;
	}

	BST_ARRAY(void)::complete() {
	
	}

	BST_ARRAY(void)::inOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}

	BST_ARRAY(void)::preOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}

	BST_ARRAY(void)::postOrder(const std::function<void(Element*)>& functionTraversal) {
	
	}

	BST_ARRAY(inline unsigned int)::size() {
		return bstSize;
	}

	BST_ARRAY(inline bool)::isEmpty() {
		return bstSize == 0;
	}

	BST_ARRAY(void)::clear() {
		
		delete[] treeArray;
		delete[] availableRoot;

		bstSize = 0;
		capacity = initialCapacity;
		treeArray = new Element[initialCapacity];
		availableRoot = new char[initialCapacity](FREE_MEMORY);
	}

}