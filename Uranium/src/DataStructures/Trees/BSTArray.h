#pragma once

#include "BinarySearchTree.h"

namespace Uranium::DataStructures::Trees {

	template<class Element> class BSTArray : public BinarySearchTree<Element> {
	public:
		BSTArray();
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
	};

#define BST_ARRAY(returnType) template<class Element> returnType BSTArray<Element>

	BST_ARRAY()::BSTArray() {
	
	}
	BST_ARRAY()::~BSTArray() {
	
	}

	BST_ARRAY(void)::add(const Element& obj) {
	
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
		return 0;
	}

	BST_ARRAY(inline bool)::isEmpty() {
		return false;
	}

	BST_ARRAY(void)::clear() {
	
	}

}