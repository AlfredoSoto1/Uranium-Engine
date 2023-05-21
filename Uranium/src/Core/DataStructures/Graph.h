#pragma once

#include "List.h"
#include "Container.h"

#include <memory>

namespace Uranium::Core::DataStructures {

	template<class Element> class Graph : public Container {
	public:
		/*
		* Returns a list in the order of which it 
		* traversed the graph.
		* @return (List<Element>) list of elements
		*/
		virtual List<Element>* depthFirstSearch(const Element& obj) = 0;
	
		/*
		* Returns a list in the order of which it
		* traversed the graph.
		* @return (List<Element>) list of elements
		*/
		virtual List<Element>* breadthFirstSearch(const Element& obj) = 0;

		/*
		* adds an element to the graph
		* and a pointer that dictates who 
		* is the neighbor of this Element in
		* the graph
		*/
		virtual void add(const Element& obj, std::shared_ptr<List<Element*>> adjList) = 0;

		/*
		* @return a weak_ptr containing the adjacent
		* list of the pointers to which 'obj' points
		* to, refered as 'neighbors'
		*/
		virtual std::weak_ptr<List<Element*>> getNeighbors(const Element& obj) = 0;
	};
}