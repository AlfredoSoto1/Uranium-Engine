#pragma once

#include <memory>
#include <functional>

#include "DataStructures/Lists/List.h"
#include "DataStructures/Containers/Container.h"
#include "DataStructures/Containers/GraphAddress.h"

namespace Uranium::DataStructures::Graphs {
	
	template<class Element> class Graph : public Containers::Container<Element> {
	public:
		/*
		* Custom alias
		*/
		template<class Element>
		using List = Lists::List<Element>;
		using GraphAddress = Containers::GraphAddress;

		/*
		* Adds an element to the graph and
		* returns a Graph Address that contains the
		* location of where the Element was stored in memory
		*/
		virtual GraphAddress add(const Element& obj) = 0;

		/*
		* Returns the address of the element inside the
		* graph
		*/
		virtual GraphAddress addressOf(const Element& obj) = 0;

		/*
		* Returns a reference to the element inside
		* graph that is at target address. Nullptr will
		* be returned if element is not existant in the provided address
		*/
		virtual Element* elementAt(const GraphAddress& address) = 0;

		/*
		* Adds a new address to reference a neighbor for element
		*/
		virtual void addNeighbor(const GraphAddress& elementAddress, const GraphAddress& address) = 0;

		/*
		* Returns a weak pointer that contains a list of
		* Graph Addresses from target element. If element is
		* not present in graph or has no neighbors, pointer will
		* be null or list will just be empty respectively
		*/
		virtual std::weak_ptr<List<GraphAddress>> getNeighbors(const GraphAddress& address) = 0;

		/*
		* Traverses the graph starting from an element
		* No traversal will be made if element is not connected
		* to any other element or is not present in graph
		*/
		virtual void depthFirstSearch(const Element & start, const std::function<void(const Element&)>& inTraversal) = 0;
	
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