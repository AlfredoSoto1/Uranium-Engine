#pragma once

namespace Uranium::DataStructures::Containers {

	template<class Weight, class Vertex> class GraphWeight {
	public:
		/*
		* Construct a Graph weight by copying
		* the parameters
		*/
		GraphWeight(const Weight& weight, Vertex* vertex);
		/*
		* Construct a Graph weight inplace
		*/
		GraphWeight(const Weight&& weight, Vertex* vertex);

		/*
		* getters
		*/
		Weight& getWeight();
		Vertex* getVertex();

	private:
		/*
		* private members
		*/
		Weight weight;
		Vertex* vertex;
	};

#define GRAPH_WEIGHT(returnType) template<class Weight, class Vertex> returnType GraphWeight<Weight, Vertex>

	GRAPH_WEIGHT()::GraphWeight(const Weight& weight, Vertex* vertex) :
		weight(weight),
		vertex(vertex)
	{

	}

	GRAPH_WEIGHT()::GraphWeight(const Weight&& weight, Vertex* vertex) :
		weight(weight),
		vertex(vertex)
	{

	}

	GRAPH_WEIGHT(Weight&)::getWeight() {
		return weight;
	}

	GRAPH_WEIGHT(Vertex*)::getVertex() {
		return vertex;
	}
}