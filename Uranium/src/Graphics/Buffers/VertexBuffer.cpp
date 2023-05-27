#define GLEW_STATIC
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "Graphics/Meshes/Model.h"

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Buffers;

VertexBuffer::VertexBuffer(const Model& model, unsigned int accessFormat, unsigned int vertexCount, unsigned int vertexSize) :
	model(model),
	vertSize(vertexSize),
	vertCount(vertexCount),
	accessFormat(accessFormat)
{
	// bind model vao
	model.bind();

	// create a new buffer
	glGenBuffers(1, &vbo);
	
	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	// tell opengl how large the buffer should be
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, nullptr, accessFormat);

	// unbinds the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// pass a copy of 'this' buffer
	model.vbos.push_back(*this);
}

VertexBuffer::VertexBuffer(const Model& model, unsigned int accessFormat, unsigned int vertexCount, unsigned int vertexSize, void* data) :
	model(model),
	vertSize(vertexSize),
	vertCount(vertexCount),
	accessFormat(accessFormat)
{
	
}

VertexBuffer::VertexBuffer(const VertexBuffer& copy) :
	vbo(copy.vbo),
	model(copy.model),
	vertSize(copy.vertSize),
	vertCount(copy.vertCount),
	accessFormat(copy.accessFormat)
{
	
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& copyFrom) {
	return *this;
}

void VertexBuffer::bind() const {
	// bind buffer to vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::unbind() const {
	// unbind buffer to zero
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::dispose() const {
	// erase the buffer from list
	auto vboIterator = model.vbos.begin();
	while (vboIterator != model.vbos.end()) {
		if (vboIterator->vbo == this->vbo)
			vboIterator = model.vbos.erase(vboIterator);
		else
			++vboIterator;
	}

	// delete the data from the buffer
	glDeleteBuffers(1, &vbo);
}

VertexBuffer::operator unsigned int() const {
	return vbo;
}

inline unsigned int VertexBuffer::bufferSize() const {
	return vertCount * vertSize;
}

inline unsigned int VertexBuffer::vertexCount() const {
	return vertCount;
}

void VertexBuffer::setLayout(const VertexAttribute& layout) {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// size of the attribute (bytes)
	unsigned int attribSize = getSizeType(layout.readType) * layout.componentCount;
	// location of the attribute in vertex (bytes)
	unsigned int offset = layout.attribIndex * attribSize;

	// set the attribute to single vertex
	glVertexAttribPointer(layout.location, layout.componentCount, layout.readType, layout.typeNormalization, attribSize, (const void*)offset);

	// unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout(const VertexAttribute&& layout) {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// size of the attribute (bytes)
	unsigned int attribSize = getSizeType(layout.readType) * layout.componentCount;
	// location of the attribute in vertex (bytes)
	unsigned int offset = layout.attribIndex * attribSize;

	// set the attribute to single vertex
	glVertexAttribPointer(layout.location, layout.componentCount, layout.readType, layout.typeNormalization, attribSize, (const void*)offset);

	// unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::getVertices(void* outDataCopy) const {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Get the size of the buffer
	//GLint bufferSize;
	//glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	// Retrieve the buffer data
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, vertCount * vertSize, outDataCopy);

	// unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::getVertex(unsigned int index, void* outDataCopy) const {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Get the size of the buffer
	//GLint bufferSize;
	//glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	// Retrieve the buffer data
	glGetBufferSubData(GL_ARRAY_BUFFER, index * vertSize, vertCount * vertSize, outDataCopy);

	// unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setVertex(unsigned int index, const void* data) {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/*
	* set data to a single vertex at a specific offset
	* with the corresponding size of the vertex
	* both vertex and offset are in bytes
	*/
	glBufferSubData(GL_ARRAY_BUFFER, index * vertSize, vertSize, data);

	// unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setVertices(const void* data) {
	model.bind();

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// offset of 0 since we are going to start
	// from the beginning of the buffer
	// this sets the data for the entire buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize * vertCount, data);

	// unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t VertexBuffer::getSizeType(unsigned int type) {
	switch (type) {
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		return sizeof(GLbyte);
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
		return sizeof(GLshort);
	case GL_INT:
	case GL_UNSIGNED_INT:
		return sizeof(GLint);
	case GL_HALF_FLOAT:
		return sizeof(GLhalf);
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_DOUBLE:
		return sizeof(GLdouble);
	default:
		// Handle unsupported types
		return 0;
	}
}