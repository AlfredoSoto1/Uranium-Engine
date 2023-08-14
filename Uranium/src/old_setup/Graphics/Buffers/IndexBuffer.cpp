#define GLEW_STATIC
#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Graphics/Meshes/Model.h"

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Buffers;

IndexBuffer::IndexBuffer(const Model& model, unsigned int accessFormat, unsigned int indCount) :
	model(model),
	indCount(indCount),
	accessFormat(accessFormat)
{
	// bind model vao
	model.bind();

	// create buffer id
	glGenBuffers(1, &ibo);

	// bind buffer before use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	// allocate buffer with a size in memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), nullptr, accessFormat);
	
	// unbind buffer after use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// pass a copy of 'this' buffer
	model.ibos.push_back(*this);
}

IndexBuffer::IndexBuffer(const Model& model, unsigned int accessFormat, unsigned int indCount, const void* data) :
	model(model),
	indCount(indCount),
	accessFormat(accessFormat)
{
	// bind model vao
	model.bind();

	// create buffer id
	glGenBuffers(1, &ibo);

	// bind buffer before use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// allocate buffer with a size in memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), data, accessFormat);

	// unbind buffer after use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// pass a copy of 'this' buffer
	model.ibos.push_back(*this);
}

IndexBuffer::IndexBuffer(const IndexBuffer& copy) :
	ibo(copy.ibo),
	model(copy.model),
	indCount(copy.indCount),
	accessFormat(copy.accessFormat)
{

}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer&) {
	return *this;
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::dispose() const {
	// erase the buffer from list
	auto iboIterator = model.ibos.begin();
	while (iboIterator != model.ibos.end()) {
		if (iboIterator->ibo == this->ibo)
			iboIterator = model.ibos.erase(iboIterator);
		else
			++iboIterator;
	}

	// delete the data from the buffer
	glDeleteBuffers(1, &ibo);
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
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// Retrieve the buffer data
	glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indCount * sizeof(unsigned int), outDataCopy);

	// unbind the vbo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::getTriangle(unsigned int index, unsigned int* index1, unsigned int* index2, unsigned int* index3) const {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// create simple stack alocated triangle
	unsigned int triangle[3];

	// Retrieve the buffer data
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
	model.bind();
	
	// bind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	// set data to the entire buffer
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indCount * sizeof(unsigned int), data);
	
	// unbind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setTriangle(unsigned int index, unsigned int index1, unsigned int index2, unsigned int index3) {
	model.bind();

	// bind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// create triangle
	unsigned int arr[3] = {index1, index2, index3};

	// set data to the entire buffer
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(unsigned int), 3 * sizeof(unsigned int), arr);

	// unbind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
