#define GLEW_STATIC
#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Graphics/Meshes/Model.h"

namespace Uranium::Graphics::Buffers {

	IndexBuffer::IndexBuffer(AccessFormat format, unsigned int indCount) noexcept :
		indCount(indCount),
		format(format)
	{
		// create buffer id
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), nullptr, accessFormat);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::IndexBuffer(AccessFormat format, unsigned int indCount, const void* data) noexcept :
		indCount(indCount),
		format(format)
	{
		// create buffer id
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), data, accessFormat);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &ibo);
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::operator unsigned int() const {
		return ibo;
	}

	inline unsigned int IndexBuffer::bufferSize() const {
		return indCount * sizeof(unsigned int);
	}

	unsigned int IndexBuffer::indexCount() const {
		return indCount;
	}

	void IndexBuffer::getIndices(void* outDataCopy) const {
		// bind the vbo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indCount * sizeof(unsigned int), outDataCopy);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::getTriangle(unsigned int index, unsigned int* index1, unsigned int* index2, unsigned int* index3) const {
		// bind the vbo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		unsigned int triangle[3];
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(unsigned int), 3 * sizeof(unsigned int), triangle);

		// copy the values to the out
		// triangle indices
		*index1 = triangle[0];
		*index2 = triangle[1];
		*index3 = triangle[2];

		// unbind the vbo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::setIndices(const void* data) {
		// bind buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indCount * sizeof(unsigned int), data);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::setTriangle(unsigned int index, unsigned int index1, unsigned int index2, unsigned int index3) {
		// bind buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// create triangle
		unsigned int arr[3] = {index1, index2, index3};
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(unsigned int), 3 * sizeof(unsigned int), arr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
