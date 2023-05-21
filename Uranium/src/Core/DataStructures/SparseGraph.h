#pragma once

#include "Graph.h"
#include "ArrayList.h"

namespace Uranium::Core::DataStructures {

	template<class Element> class SparseGraph : public Graph<Element> {
	public:
		explicit SparseGraph();
		~SparseGraph();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		List<Element>* depthFirstSearch(const Element& obj);
		List<Element>* breadthFirstSearch(const Element& obj);

		void add(const Element& obj, std::shared_ptr<List<Element*>> adjList);

		std::weak_ptr<List<Element*>> getNeighbors(const Element& obj);

	private:
		/*
		* private members
		*/
		template<class Edge> using AdjList = std::shared_ptr<List<Edge>>;

		ArrayList<Element> vertices;
		ArrayList<AdjList<Element*>> edges;
	};

#define SPARSE_GRAPH(returnType) template<class Element> returnType SparseGraph<Element>
	
	SPARSE_GRAPH()::SparseGraph() :
		vertices(ArrayList<Element>(5)),
		edges(ArrayList<AdjList<Element*>>(5))
	{

	}

	SPARSE_GRAPH()::~SparseGraph() {
		// free memory
		clear();
	}

	SPARSE_GRAPH(inline unsigned int)::size() {
		return vertices.size();
	}

	SPARSE_GRAPH(inline bool)::isEmpty() {
		return vertices.isEmpty();
	}

	SPARSE_GRAPH(void)::clear() {
		vertices.clear();
		edges.clear();
	}

	SPARSE_GRAPH(List<Element>*)::depthFirstSearch(const Element& obj) {
		return nullptr;
	}

	SPARSE_GRAPH(List<Element>*)::breadthFirstSearch(const Element& obj) {
		return nullptr;
	}

	SPARSE_GRAPH(void)::add(const Element& obj, std::shared_ptr<List<Element*>> adjList) {
		vertices.add(obj);
		edges.add(adjList);
	}

	SPARSE_GRAPH(std::weak_ptr<List<Element*>>)::getNeighbors(const Element& obj) {
		return edges.get(0);
	}
}