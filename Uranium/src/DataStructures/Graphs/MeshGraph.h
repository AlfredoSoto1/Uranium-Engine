#pragma once

#include "Graph.h"
#include "DataStructures/Sets/HashSet.h"
#include "DataStructures/Maps/HashMap.h"
#include "DataStructures/Lists/ArrayList.h"

#include <stack>

namespace Uranium::DataStructures::Graphs {
	
	template<class Vertex> class MeshGraph : public Graph<Vertex> {
	public:
		/*
		* custom alias
		*/
		template<class Vertex>
		using List = Lists::List<Vertex>;
		using GraphAddress = Containers::GraphAddress;

	public:
		MeshGraph(unsigned int initialVertexCapacity, 
			const std::function<unsigned int(const Vertex&)>&,
			const std::function<int(const Vertex&, const Vertex&)>&);
		virtual ~MeshGraph();

		/*
		*/
		const Vertex* asVertexArray();
		
		/*
		*/
		const unsigned int* asIndexArray();

		/*
		*/
		inline unsigned int size();

		/*
		*/
		inline bool isEmpty();

		/*
		*/
		void clear();

		/*
		*/
		GraphAddress add(const Vertex& obj);

		/*
		*/
		void addIndex(const GraphAddress& address);

	private:
		/*
		* Hidden ADT methods
		* Currently not used / needed for this implementation
		* of mesh graph
		*/
		GraphAddress addressOf(const Vertex& obj);

		Vertex* elementAt(const GraphAddress& address);

		void addNeighbor(const GraphAddress& VertexAddress, const GraphAddress& address);

		std::weak_ptr<List<GraphAddress>> getNeighbors(const GraphAddress& address);

		void depthFirstSearch(const Vertex& start, const std::function<void(const Vertex&)>& inTraversal);

		void breadthFirstSearch(const Vertex& start, const std::function<void(const Vertex&)>& inTraversal);

		void depthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal);

		void breadthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal);
		
	private:
		/*
		* private members
		*/

		/*
		* Struct representation of a triangle
		* containing the indices that form a triangle
		* this can be dereferenced into an array of integers
		*/
		struct Triangle {
			unsigned int index1;
			unsigned int index2;
			unsigned int index3;
		};

		// count of all indices formed
		// when adding a vertex and connect it
		// to another vertex
		int indexCounter;

		// standard hasher from STD
		std::hash<unsigned int> indexHashder;

		Sets::HashSet<Triangle>* triangleSet;
		Maps::HashMap<Vertex, int>* vertexMap;

		Lists::ArrayList<Vertex>* vertices;
		Lists::ArrayList<unsigned int>* triangleIndices;

		std::stack<GraphAddress> groupIndices;
		
	};

#define MESH_GRAPH(returnType) template<class Vertex> returnType MeshGraph<Vertex>

	MESH_GRAPH()::MeshGraph(unsigned int initialVertexCapacity, 
		const std::function<unsigned int(const Vertex&)>& vertexHashFunction,
		const std::function<int(const Vertex&, const Vertex&)>& vertexComparator) :
		indexCounter(0) // begin count at zero
	{
		// lambda expression used to
		// compare triangle indices IN-ORDER
		auto triangleComparator = [](const Triangle& tri1, const Triangle& tri2) {
			if ((tri1.index1 == tri2.index1) && (tri1.index2 == tri2.index2) && (tri1.index3 == tri2.index3))
				return 0; // are equal in order
			return 1; // are different
		};
		
		// lambda expression with custom hash funcion for hashSet
		auto hashFunction = [this](const Triangle& obj) {
			return (unsigned int)(indexHashder(obj.index1) + indexHashder(obj.index2) + indexHashder(obj.index3));
		};
		
		// triangle set that will ensure that no indices are repeated
		triangleSet = new Sets::HashSet<Triangle>(initialVertexCapacity, 0.75, hashFunction, triangleComparator);

		// vertex map that will check if vertices repeat
		vertexMap = new Maps::HashMap<Vertex, int>(initialVertexCapacity, 0.75, vertexHashFunction, vertexComparator);

		// actual lists that will contain the mesh data
		// that OpenGl can understand when passing them to the buffers
		vertices = new Lists::ArrayList<Vertex>(initialVertexCapacity);
		triangleIndices = new Lists::ArrayList<unsigned int>(initialVertexCapacity);
	}

	MESH_GRAPH()::~MeshGraph() {
		// clear all data before
		// deleting
		this->clear();
		// delete all data
		delete vertices;
		delete vertexMap;
		delete triangleSet;
		delete triangleIndices;
	}

	MESH_GRAPH(const Vertex*)::asVertexArray() {
		return vertices->asArray();
	}

	MESH_GRAPH(const unsigned int*)::asIndexArray() {
		return triangleIndices->asArray();
	}

	MESH_GRAPH(inline unsigned int)::size() {
		return vertices->size();
	}

	MESH_GRAPH(inline bool)::isEmpty() {
		return vertices->isEmpty();
	}

	MESH_GRAPH(void)::clear() {
		vertices->clear();
		vertexMap->clear();
		triangleSet->clear();
		triangleIndices->clear();
	}

	MESH_GRAPH(Containers::GraphAddress)::add(const Vertex& obj) {

		std::optional<int> vertexLocation = vertexMap->put(obj, indexCounter);

		// not unique
		if (vertexLocation.has_value()) {
			return vertexLocation.value();
		}
		else {
			// add vertex to list
			vertices->add(obj);
			// return new address before increasing counter
			return { indexCounter++ }; 
		}
	}

	MESH_GRAPH(void)::addIndex(const GraphAddress& address) {
		groupIndices.push(address);

		if (groupIndices.size() == 3) {
			GraphAddress& address3 = groupIndices.top(); groupIndices.pop();
			GraphAddress& address2 = groupIndices.top(); groupIndices.pop();
			GraphAddress& address1 = groupIndices.top(); groupIndices.pop();

			bool isUnique = triangleSet->put({ (unsigned int)address1 , (unsigned int)address2, (unsigned int)address3 });

			if (!isUnique)
				return;

			triangleIndices->add(address1);
			triangleIndices->add(address2);
			triangleIndices->add(address3);
		}
	}

	MESH_GRAPH(Containers::GraphAddress)::addressOf(const Vertex& obj) {
		return {};
	}

	MESH_GRAPH(Vertex*)::elementAt(const GraphAddress& address) {
		return nullptr;
	}

	MESH_GRAPH(void)::addNeighbor(const GraphAddress& VertexAddress, const GraphAddress& address) {

	}

	MESH_GRAPH(std::weak_ptr<Lists::List<Containers::GraphAddress>>)::getNeighbors(const GraphAddress& address) {
		std::shared_ptr<Lists::List<Containers::GraphAddress>> yes;
		return yes;
	}

	MESH_GRAPH(void)::depthFirstSearch(const Vertex& start, const std::function<void(const Vertex&)>& inTraversal) {
	
	}

	MESH_GRAPH(void)::breadthFirstSearch(const Vertex& start, const std::function<void(const Vertex&)>& inTraversal) {
	
	}

	MESH_GRAPH(void)::depthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal) {
	
	}

	MESH_GRAPH(void)::breadthFirstSearch(const GraphAddress& address, const std::function<void(const GraphAddress&)>& inTraversal) {
	
	}

}