#pragma once

namespace Uranium {

	template<typename Vertex, typename Index>
	class Mesh {
	private:
		unsigned int bufferCount;			// buffer count of used vertices
		unsigned int bufferCapacity;		// buffer capacity of total buffer (vertices)
		unsigned int initialBufferCapacity;	// initial capacity of buffer (vertices)

		unsigned int buffer_indexCount;				// count of total indices
		unsigned int buffer_indexCapacity;			// buffer capacity of total buffer (indices)
		unsigned int initial_Buffer_indexCapacity;	// initial capacity of buffer (indices)

		Index indexCounter;

		Index* indices;
		Vertex* vertices;
		 
		void resizeIndexBuffer();
		void resizeVertexBuffer();

		bool needToRezizeIndexBuffer();
		bool needToRezizeVertexBuffer();

		void pushBackIndex(Index _index);

	public:
		Mesh(unsigned int _initialBufferCapacity);
		~Mesh();

		bool isEmpty() const;					// returns a boolean wether if the buffer is empty

		unsigned int size() const;				// returns the sizeof the buffer
		unsigned int unallocSize() const;		// returns the total sizeof the buffer (including the unused allocated memory)
		unsigned int indexCapacity() const;		// returns the available capacity of indices
		unsigned int vertexCapacity() const;	// returns the available capacity of vertices

		unsigned int indexCount() const;		// returns the total in-use indices
		unsigned int vertexCount() const;		// returns the total count of vertices

		unsigned int indexCountSize() const;	// returns the sizeOf the count of indices used in array (bytes)
		unsigned int vertexCountSize() const;	// returns the sizeOf the count of vertices used in array (bytes)

		unsigned int indexSize() const;			// returns the sizeOf the index
		unsigned int vertexSize() const;		// returns the sizeOf the vertex

		const Index* getIndices() const;		// returns a const array of the allocated indices
		const Vertex* getVertices() const;		// returns a const array of the allocated vertices

		void fit();								// adjusts the buffer to occupy the exact count of each array reducing the unused space

		void clear();							// clears the buffer

		void pushBack(const Vertex& _vertex);	// push back a copy ref
		void pushBack(const Vertex&& _vertex);	// push back an rvalue ref

		void pushBack(const Vertex& _vertex, bool(*compare)(const Vertex& _vertex, Vertex& _other));	// push back a copy ref
		void pushBack(const Vertex&& _vertex, bool(*compare)(const Vertex&& _vertex, Vertex& _other));	// push back an rvalue ref

		template<typename... Args>
		void emplaceBack(Args&& ... _args);

	};
}

#include "Mesh_impl.h"

