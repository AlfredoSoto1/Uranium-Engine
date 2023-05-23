#pragma once

#include "Graph.h"
#include "DataStructures/Lists/ArrayList.h"
#include "DataStructures/HashTables/HashTableOpenAddress.h"

namespace Uranium::DataStructures::Graphs {
	
	template<class Vertex> class MeshGraph : public Graph<Vertex> {
	public:
		MeshGraph();
		virtual ~MeshGraph();

		inline unsigned int size();

		inline bool isEmpty();

		void clear();

		Lists::List<Vertex>* depthFirstSearch(const Vertex& obj);

		Lists::List<Vertex>* breadthFirstSearch(const Vertex& obj);

		void add(const Vertex& obj, std::shared_ptr<Lists::List<Vertex*>> adjList);

		std::weak_ptr<Lists::List<Vertex*>> getNeighbors(const Vertex& obj);

	private:
		/*
		* private methods
		*/


	private:
		/*
		* private members
		*/
	};

#define MESH_GRAPH(returnType) template<class Vertex> returnType MeshGraph<Vertex>

	MESH_GRAPH()::MeshGraph() 
	{
	}

	MESH_GRAPH()::~MeshGraph() {

	}
	
	MESH_GRAPH(inline unsigned int)::size() {
		return 0;
	}

	MESH_GRAPH(inline bool)::isEmpty() {
		return false;
	}

	MESH_GRAPH(void)::clear() {

	}

	MESH_GRAPH(Lists::List<Vertex>*)::depthFirstSearch(const Vertex& obj) {
		return nullptr;
	}

	MESH_GRAPH(Lists::List<Vertex>*)::breadthFirstSearch(const Vertex& obj) {
		return nullptr;
	}

	MESH_GRAPH(void)::add(const Vertex& obj, std::shared_ptr<Lists::List<Vertex*>> adjList) {

	}

	MESH_GRAPH(std::weak_ptr<Lists::List<Vertex*>>)::getNeighbors(const Vertex& obj) {
		std::shared_ptr<Lists::List<Vertex*>> yes = nullptr;
		return yes;
	}

}