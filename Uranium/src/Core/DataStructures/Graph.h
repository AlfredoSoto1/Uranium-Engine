#pragma once

#include "List.h"
#include "Container.h"

namespace Uranium::Core::DataStructures {

	template<class Element> class Graph : public Container {
	public:
		/*
		* Returns a list in the order of which it 
		* traversed the graph.
		* @return (List<Element>) list of elements
		*/
		virtual List<Element> depthFirstSearch(const Element& obj) = 0;
	
		/*
		* Returns a list in the order of which it
		* traversed the graph.
		* @return (List<Element>) list of elements
		*/
		virtual List<Element> breadthFirstSearch(const Element& obj) = 0;

	};
}