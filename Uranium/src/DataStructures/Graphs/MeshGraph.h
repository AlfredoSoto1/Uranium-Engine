//#pragma once
//
//#include "Graph.h"
//
//namespace Uranium::DataStructures::Graphs {
//	
//	template<class Vertex> class MeshGraph : public Graph<Vertex> {
//	public:
//		/*
//		* custom alias
//		*/
//		template<class Element> using List = Uranium::Core::DataStructures::List<Element>;
//		template<class Element> using ArrayList = Uranium::Core::DataStructures::ArrayList<Element>;
//
//	public:
//		MeshGraph();
//		virtual ~MeshGraph();
//
//		inline unsigned int size();
//
//		inline bool isEmpty();
//
//		void clear();
//
//		List<Vertex>* depthFirstSearch(const Vertex& obj);
//
//		List<Vertex>* breadthFirstSearch(const Vertex& obj);
//
//		void add(const Vertex& obj, std::shared_ptr<List<Vertex*>> adjList);
//
//		std::weak_ptr<List<Vertex*>> getNeighbors(const Vertex& obj);
//
//	private:
//		/*
//		* private methods
//		*/
//
//
//	private:
//		/*
//		* private members
//		*/
//		ArrayList<Vertex> vertices;
//		ArrayList<unsigned int> indices;
//
//	};
//
//#define MESH_GRAPH(returnType) template<class Vertex> returnType MeshGraph<Vertex>
//
//	MESH_GRAPH()::MeshGraph() {
//
//	}
//
//	MESH_GRAPH()::~MeshGraph() {
//
//	}
//	
//	MESH_GRAPH(inline unsigned int)::size() {
//		return 0;
//	}
//
//	MESH_GRAPH(inline bool)::isEmpty() {
//		return false;
//	}
//
//	MESH_GRAPH(void)::clear() {
//
//	}
//
//	MESH_GRAPH(Uranium::Core::DataStructures::List<Vertex>*)::depthFirstSearch(const Vertex& obj) {
//		return nullptr;
//	}
//
//	MESH_GRAPH(Uranium::Core::DataStructures::List<Vertex>*)::breadthFirstSearch(const Vertex& obj) {
//		return nullptr;
//	}
//
//	MESH_GRAPH(void)::add(const Vertex& obj, std::shared_ptr<List<Vertex*>> adjList) {
//
//	}
//
//	MESH_GRAPH(std::weak_ptr<Uranium::Core::DataStructures::List<Vertex*>>)::getNeighbors(const Vertex& obj) {
//		std::shared_ptr<List<Vertex*>> yes = nullptr;
//		return yes;
//	}
//
//}