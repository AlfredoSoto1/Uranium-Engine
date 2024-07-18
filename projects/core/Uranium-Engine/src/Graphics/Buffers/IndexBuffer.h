#pragma once

#include "AccessFormat.h"

namespace Uranium::Graphics::Buffers {

	class IndexBuffer final {
	public:
		/*
		* Construct an Index Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		* indCount - determines the count of indices inside the buffer
		*/		
		explicit IndexBuffer(AccessFormat format, unsigned int indCount) noexcept;
		
		/*
		* Construct an Index Buffer inside a given Model
		* 
		* accessFormat - determines how the program should read this buffer
		* indCount - determines the count of indices inside the buffer
		* data* - determines the initial data to be *copied* to the buffer
		*/
		explicit IndexBuffer(AccessFormat format, unsigned int indCount, const void* data) noexcept;

		/*
		*/
		~IndexBuffer();

	public:
		/*
		* Bind the buffer so that
		* OpenGL knows when to use all of its content
		*/
		void bind() const;

		/*
		* UnBind the buffer when no longer is being used
		*/
		void unbind() const;

	public:
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
		unsigned int indexCount() const;

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
		unsigned int ibo;
		unsigned int indCount;

		AccessFormat format;
	};
}