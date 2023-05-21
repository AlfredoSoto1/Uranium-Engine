#pragma once

#include "Graph.h"
#include "GraphWeight.h"

namespace Uranium::Core::DataStructures {

	template<class Element, class Weight> class WeightedGraph : public Graph<Element> {
	public:
		/*
		* @return an array of entries containing
		* the distance to each vertex inside the graph
		* from start element
		*/
		virtual void getShortPath(const Element& start) = 0;

		/*
		* Finds the shortes path from vertex to
		* vertex inside graph
		* @return shortest path as an edge
		*/
		virtual void findShortPath(const Element& start, const Element& dest) = 0;

		/*
		* adds an element to the graph
		* and a list of weighted pointers that dictates who
		* is the neighbor of this Element in the graph
		*/
		virtual void add(const Element& obj, List<GraphWeight<Weight, Element*>>* adjList) = 0;
	};
}