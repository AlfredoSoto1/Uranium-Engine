//#pragma once
//
//#include "ArrayList.h"
//#include "WeightedGraph.h"
//
//#include <memory>
//
//namespace Uranium::Core::DataStructures {
//
//	template<class Element, class Weight> class SparseGraph : public WeightedGraph<Element, Weight> {
//	public:
//		explicit SparseGraph();
//		~SparseGraph();
//
//		inline unsigned int size();
//
//		inline bool isEmpty();
//
//		void clear();
//
//		List<Element>* depthFirstSearch(const Element& obj);
//		List<Element>* breadthFirstSearch(const Element& obj);
//
//		void getShortPath(const Element& start);
//		void findShortPath(const Element& start, const Element& dest);
//
//		void add(const Element& obj, List<Element*>* adjList);
//		void add(const Element& obj, List<GraphWeight<Weight, Element*>>* adjList);
//
//	private:
//		/*
//		* private members
//		*/
//		template<class Edge> using AdjList = std::shared_ptr<List<Edge>>;
//
//		ArrayList<Element> vertices;
//		ArrayList<AdjList<GraphWeight<Weight, Element*>>> edges;
//	};
//
//#define SPARSE_GRAPH(returnType) template<class Element, class Weight> returnType SparseGraph<Element, Weight>
//
//	SPARSE_GRAPH()::SparseGraph() :
//		vertices(ArrayList<Element>(5)),
//		edges(ArrayList<AdjList<GraphWeight<Weight, Element*>>>(5))
//	{
//
//	}
//
//	SPARSE_GRAPH()::~SparseGraph() {
//		// free memory
//		clear();
//	}
//
//	SPARSE_GRAPH(inline unsigned int)::size() {
//		return vertices.size();
//	}
//
//	SPARSE_GRAPH(inline bool)::isEmpty() {
//		return vertices.isEmpty();
//	}
//
//	SPARSE_GRAPH(void)::clear() {
//		vertices.clear();
//		edges.clear();
//	}
//
//	SPARSE_GRAPH(List<Element>*)::depthFirstSearch(const Element& obj) {
//		return nullptr;
//	}
//
//	SPARSE_GRAPH(List<Element>*)::breadthFirstSearch(const Element& obj) {
//		return nullptr;
//	}
//
//	SPARSE_GRAPH(void)::getShortPath(const Element& start) {
//
//	}
//
//	SPARSE_GRAPH(void)::findShortPath(const Element& start, const Element& dest) {
//
//	}
//
//	SPARSE_GRAPH(void)::add(const Element& obj, List<Element*>* adjList) {
//
//	}
//
//	SPARSE_GRAPH(void)::add(const Element& obj, List<GraphWeight<Weight, Element*>>* adjList) {
//
//	}
//
//}