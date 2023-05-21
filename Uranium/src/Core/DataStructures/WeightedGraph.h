#pragma once

#include "Graph.h"

namespace Uranium::Core::DataStructures {

	template<class Element> class WeightedGraph : public Graph<Element> {
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

	};
}