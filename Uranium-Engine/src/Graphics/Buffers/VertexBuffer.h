#pragma once

#include <memory>
#include <vector>
#include "AccessFormat.h"

namespace Uranium::Graphics::Buffers {

	class VertexBuffer final {
	public:
		/*
		* Buffer layout struct
		* This will determine the layout of how
		* the VBO should read each attribute inside each vertex
		*/
		struct VertexAttribute {
			unsigned int location;          // defines a location as to which attribute enable
			unsigned int componentCount;    // determines the count of elements that a single attribute can have (Must be: 1, 2, 3, 4)
			unsigned int readType;          // determines the type that we are storing in the attribute ex:(GL_FLOAT, GL_INT, GL_UNSIGNED_BYTE, etc...)
			unsigned int typeNormalization;	// determines if the type should be normalized ex: (GL_BYTE -> reads in shader as a float from 0.0 - 1.0)
			unsigned int attribIndex;       // determines the offset of which this attribute fits inside the actual Vertex
		};

	public:
		/*
		* Construct a Vertex Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		* vertexCount - determines how many vertices are inside the buffer
		* vertexSize - determines the size of the individual vertex - in bytes
		*/
		explicit VertexBuffer(AccessFormat format, unsigned int vertexCount, unsigned int vertexSize) noexcept;

		/*
		* Construct a Vertex Buffer inside a given Model
		*
		* accessFormat - determines how the program should read this buffer
		* vertexCount - determines how many vertices are inside the buffer
		* vertexSize - determines the size of the individual vertex - in bytes
		* attribCount - determines how many attributes or elements are inside the vertex
		* data* - determines the initial data to be *copied* to the buffer
		*/
		explicit VertexBuffer(AccessFormat format, unsigned int vertexCount, unsigned int vertexSize, void* data) noexcept;

		/*
		* Deletes the buffer and all the data loaded to the GPU
		*/
		~VertexBuffer();

	public:
		/*
		* Binds/unbinds the current instance of the buffer
		*/
		void bind() const;
		void unbind() const;

	public:
		/*
		* Returns the actual vbo ID of 'this' buffer
		*/
		operator unsigned int() const;

		/*
		* Returns the buffer size of 'this' buffer
		*/
		inline unsigned int bufferSize() const;
		
		/*
		* Returns the vertex count of 'this' buffer
		*/
		inline unsigned int vertexCount() const;

		/*
		* Returns a void* to a copy of the data in 'this' buffer
		*/
		std::unique_ptr<char> getSubData(unsigned int location, unsigned int size) const;

		/*
		* sets data to 'this' buffer
		*/
		void setVertices(const void* data);
		void setVertex(unsigned int index, const void* data);

		/*
		* Sets a buffer layout for each of 'this'
		* vertex buffer's vertex
		*/
		void setLayout(const VertexAttribute& layout);
		void setLayout(const VertexAttribute&& layout);

	private:
		/*
		* Enables the attributes from this buffer
		*/
		void enableAttribs() const;

		/*
		* Disables the attributes from this buffer
		*/
		void disableAttribs() const;

		size_t getSizeType(unsigned int type);

	private:
		unsigned int vbo;
		unsigned int vertSize;
		unsigned int vertCount;

		AccessFormat format;

		std::vector<VertexAttribute> attributes;
	};

}