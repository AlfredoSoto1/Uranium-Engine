#pragma once

#include <functional>
#include "DataStructures/Containers/Container.h"

namespace Uranium::DataStructures::Trees {

	template<class Element> class Tree : public Containers::Container<Element> {
	public:
		/*
		*/
		virtual Element* getRoot() = 0;

		/*
		*/
		virtual bool isFull() = 0;
		
		/*
		*/
		virtual bool isComplete() = 0;
		
		/*
		*/
		virtual bool isBalanced() = 0;

		/*
		*/
		virtual unsigned int depth() = 0;
		
		/*
		*/
		virtual unsigned int height() = 0;

		/*
		*/
		virtual void inOrder(const std::function<void(Element*)>& functionTraversal) = 0;

		/*
		*/
		virtual void preOrder(const std::function<void(Element*)>& functionTraversal) = 0;

		/*
		*/
		virtual void postOrder(const std::function<void(Element*)>& functionTraversal) = 0;
	};

}