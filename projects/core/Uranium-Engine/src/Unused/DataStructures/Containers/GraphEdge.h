#pragma once

#include "GraphAddress.h"

namespace Uranium::DataStructures::Containers {

	template<class Weight> class GraphEdge {
	public:
		/*
		* Construct a Graph weight by copying
		* the parameters
		*/
		GraphEdge(const Weight& weight, const GraphAddress& address);
		/*
		* Construct a Graph weight inplace
		*/
		GraphEdge(const Weight&& weight, const GraphAddress&& address);

		/*
		* getters
		*/
		Weight& getWeight();
		GraphAddress& getAddress();

	private:
		/*
		* private members
		*/
		Weight weight;
		GraphAddress address;
	};

#define GRAPH_WEIGHT(returnType) template<class Weight> returnType GraphEdge<Weight>

	GRAPH_WEIGHT()::GraphEdge(const Weight& weight, const GraphAddress& address) :
		weight(weight),
		address(address)
	{

	}

	GRAPH_WEIGHT()::GraphEdge(const Weight&& weight, const GraphAddress&& address) :
		weight(weight),
		address(address)
	{

	}

	GRAPH_WEIGHT(Weight&)::getWeight() {
		return weight;
	}

	GRAPH_WEIGHT(GraphAddress&)::getAddress() {
		return address;
	}
}