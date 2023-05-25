#pragma once

#include "Tree.h"

namespace Uranium::DataStructures::Trees {

	template<class Element> class Heap : public Tree<Element> {
	public:

		/*
		*/
		virtual Element* removeRoot() = 0;
		
		/*
		*/
		virtual unsigned int insert(const Element& obj) = 0;
		
		/*
		*/
		virtual unsigned int get(const Element& obj) = 0;
	};
}