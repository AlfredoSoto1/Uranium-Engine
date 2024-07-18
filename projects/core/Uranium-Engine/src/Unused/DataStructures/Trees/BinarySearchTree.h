#pragma once

#include "Tree.h"

namespace Uranium::DataStructures::Trees {

	template<class Element> class BinarySearchTree : public Tree<Element> {
	public:
		/*
		*/
		virtual void add(const Element& obj) = 0;
		
		/*
		*/
		virtual void remove(const Element& obj) = 0;
		
		/*
		*/
		virtual bool contains(const Element& obj) = 0;

		/*
		*/
		virtual void complete() = 0;

	};
}