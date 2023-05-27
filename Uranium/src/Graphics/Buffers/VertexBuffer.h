#pragma once

namespace Uranium::Graphics::Meshes {
	class Model;
}

namespace Uranium::Graphics::Buffers {

	class VertexBuffer {
	public:
		/*
		* custom alias
		*/
		using Model = Meshes::Model;

	public:
		/*
		* Construct a Vertex Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		*	~ STATIC_DRAW
		*	~ DYNAMIC_DRAW
		* 
		* vertexCount - determines how many vertices are inside the buffer
		*
		* vertexSize - determines the size of the individual vertex - in bytes
		* 
		*/
		VertexBuffer(const Model& model, unsigned int accessFormat, unsigned int vertexCount, unsigned int vertexSize);

		/*
		* Construct a Vertex Buffer inside a given Model
		*
		* accessFormat - determines how the program should read this buffer
		*	~ STATIC_DRAW
		*	~ DYNAMIC_DRAW
		*
		* vertexCount - determines how many vertices are inside the buffer
		* 
		* vertexSize - determines the size of the individual vertex - in bytes
		* 
		* attribCount - determines how many attributes or elements are inside the vertex
		* 
		* data* - determines the initial data to be *copied* to the buffer
		*/
		VertexBuffer(const Model& model, unsigned int accessFormat, unsigned int vertexCount, unsigned int vertexSize, void* data);
		
		/*
		* Copy constructor; This copies all private
		* members to the new instance of the Buffer that
		* is being copied to
		*/
		VertexBuffer(const VertexBuffer&);

		/*
		* assign operator overloaded to copy
		* all data from 'this' buffer to new buffer
 		*/
		VertexBuffer& operator=(const VertexBuffer&);

		/*
		* Bind the buffer so that
		* OpenGL knows when to use all of its content
		*/
		void bind() const;

		/*
		* UnBind the buffer when no longer is being used
		*/
		void unbind() const;

		/*
		* Deletes the buffer from memory entirely
		* and all of its references. Any reference that
		* might still point to this buffer will either return
		* nullptr or throw an exception depending of the circumstances
		*/
		void dispose() const;

	public:
		/*
		* getters and setters
		*/

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
		void getVertices(void* outDataCopy) const;
		void getVertex(unsigned int index, void* outDataCopy) const;

		/*
		* sets data to 'this' buffer
		*/
		void setVertices(const void* data);
		void setVertex(unsigned int index, const void* data);

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

		/*
		* Sets a buffer layout for each of 'this'
		* vertex buffer's vertex
		*/
		void setLayout(const VertexAttribute& layout);
		void setLayout(const VertexAttribute&& layout);

	private:
		/*
		* friends with other classes
		*/

	private:
		/*
		* private methods
		*/
		size_t getSizeType(unsigned int type);

	private:
		/*
		* private members
		*/
		const Model& model;

		unsigned int vbo;
		unsigned int accessFormat;
		unsigned int vertCount;
		unsigned int vertSize;
		
	};

}