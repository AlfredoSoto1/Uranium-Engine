#pragma once

#include "DataStructures/Lists/List.h"
#include "DataStructures/Containers/Container.h"
#include "DataStructures/Containers/GraphEdge.h"

#include <memory>
#include <functional>

namespace Uranium::DataStructures::Graphs {

	template<class Element, class Weight> class WeightedGraph : public Containers::Container<Element> {
	public:
		/*
		* Custom alias
		*/
		template<class Element>
		using List = Lists::List<Element>;
		template<class Weight>
		using GraphEdge = Containers::GraphEdge<Weight>;
		using GraphAddress = Containers::GraphAddress;

		/*
		* Adds an element to the graph and
		* returns a Graph Address that contains the
		* location of where the Element was stored in memory
		*/
		virtual GraphAddress add(const Element& obj) = 0;

		/*
		* Adds an element to the graph with a list of
		* Edges containing the weight and the address
		* to which the element is connected to and
		* returns a Graph Address that contains the
		* location of where the Element was stored in memory
		*/
		virtual GraphAddress add(const Element& obj, std::shared_ptr<List<GraphEdge<Weight>>> neighborAddress) = 0;

		/*
		* Returns the address of the element inside the
		* graph
		*/
		virtual GraphAddress addressOf(const Element& obj) = 0;

		/*
		* Returns a weak pointer that contains a list of
		* weighted edges from target element. If element is
		* not present in graph or has no neighbors, pointer will
		* be null or list will just be empty respectively
		*/
		virtual std::weak_ptr<List<GraphEdge<Weight>>> getNeighbors(const Element& obj) = 0;

		/*
		* Returns a weak pointer that contains a list of
		* weighted edges from target element. If element is
		* not present in graph or has no neighbors, pointer will
		* be null or list will just be empty respectively
		*/
		virtual std::weak_ptr<List<GraphEdge<Weight>>> getNeighbors(const GraphAddress& address) = 0;

		/*
		* Returns a table containing the shortest path
		* for all elements that are connected to target
		* start element. This also includes the address
		* of the elements that form the shortes path for
		* the starting element
		*/
		virtual void getShortPath(const Element& start) = 0;

		/*
		* Finds the shortes path from vertex to
		* vertex inside graph
		* @return shortest path as an edge
		*/
		virtual void findShortPath(const Element& start, const Element& dest) = 0;

		/*
		* Traverses the graph starting from an element
		* No traversal will be made if element is not connected
		* to any other element or is not present in graph
		*/
		virtual void depthFirstSearch(const Element& start, const std::function<void(const Element&)>& inTraversal) = 0;

		/*
		* Traverses the graph starting from an element
		* No traversal will be made if element is not connected
		* to any other element or is not present in graph
		*/
		virtual void breadthFirstSearch(const Element& start, const std::function<void(const Element&)>& inTraversal) = 0;

		/*
		* Traverses the graph starting from an address
		* No traversal will be made if element is not connected
		* to any other element or is not present in graph
		*/
		virtual void depthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal) = 0;

		/*
		* Traverses the graph starting from an address
		* No traversal will be made if element is not connected
		* to any other element or is not present in graph
		*/
		virtual void breadthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal) = 0;
	};
}