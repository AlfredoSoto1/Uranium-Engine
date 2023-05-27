#pragma once

namespace Uranium::Graphics::Meshes {
	class Model;
}

namespace Uranium::Graphics::Buffers {

	class IndexBuffer {
	public:
		/*
		* Custom alias
		*/
		using Model = Meshes::Model;

	public:

		/*
		* Construct an Index Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		*	~ STATIC_DRAW
		*	~ DYNAMIC_DRAW
		* 
		* indCount - determines the count of indices inside the buffer
		*/		
		IndexBuffer(const Model& model, unsigned int accessFormat, unsigned int indCount);
		
		/*
		* Construct an Index Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		*	~ STATIC_DRAW
		*	~ DYNAMIC_DRAW
		* 
		* indCount - determines the count of indices inside the buffer
		* 
		* data* - determines the initial data to be *copied* to the buffer
		*/
		IndexBuffer(const Model& model, unsigned int accessFormat, unsigned int indCount, const void* data);

		/*
		* Copy constructor; This copies all private
		* members to the new instance of the Buffer that
		* is being copied to
		*/
		IndexBuffer(const IndexBuffer&);

		/*
		* assign operator overloaded to copy
		* all data from 'this' buffer to new buffer
		*/
		IndexBuffer& operator=(const IndexBuffer&);

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
		* Returns the actual ibo ID of 'this' buffer
		*/
		operator unsigned int() const;

		/*
		* Returns the buffer size of 'this' buffer
		*/
		inline unsigned int bufferSize() const;

		/*
		* Returns the index count of 'this' buffer
		*/
		inline unsigned int indexCount() const;

		/*
		* Returns a void* to a copy of the data in 'this' buffer
		*/
		void getIndices(void* outDataCopy) const;
		void getTriangle(unsigned int index, unsigned int* index1, unsigned int* index2, unsigned int* index3) const;

		/*
		* sets data to 'this' buffer
		*/
		void setIndices(const void* data);
		void setTriangle(unsigned int index, unsigned int index1, unsigned int index2, unsigned int index3);

	private:
		/*
		* private members
		*/
		const Model& model;

		unsigned int ibo;
		unsigned int indCount;
		unsigned int accessFormat;
	};
}