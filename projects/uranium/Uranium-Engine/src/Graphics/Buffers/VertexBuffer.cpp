#include <GL/glew.h>

#include "VertexBuffer.h"
#include "Graphics/Meshes/Model.h"

namespace Uranium::Graphics::Buffers {

	VertexBuffer::VertexBuffer(AccessFormat format, unsigned int vertexCount, unsigned int vertexSize) noexcept :
		format(format),
		vertSize(vertexSize),
		vertCount(vertexCount)
	{
		// create a new buffer
		glGenBuffers(1, &vbo);
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// tell opengl how large the buffer should be
		//glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, nullptr, accessFormat);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::VertexBuffer(AccessFormat format, unsigned int vertexCount, unsigned int vertexSize, void* data) noexcept :
		format(format),
		vertSize(vertexSize),
		vertCount(vertexCount)
	{
		// create a new buffer
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// tell opengl how large the buffer should be
		//glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, data, accessFormat);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &vbo);
	}

	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void VertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::enableAttribs() const {
		for (const VertexAttribute& attribute : attributes)
			glEnableVertexAttribArray(attribute.location);
	}

	void VertexBuffer::disableAttribs() const {
		for (const VertexAttribute& attribute : attributes)
			glDisableVertexAttribArray(attribute.location);
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
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// size of the attribute (bytes)
		unsigned int attribSize = getSizeType(layout.readType) * layout.componentCount;
		// location of the attribute in vertex (bytes)
		unsigned int offset = layout.attribIndex * attribSize;

		// set the attribute to single vertex
		glVertexAttribPointer(layout.location, layout.componentCount, layout.readType, layout.typeNormalization, attribSize, (const void*)offset);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::setLayout(const VertexAttribute&& layout) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// size of the attribute (bytes)
		unsigned int attribSize = getSizeType(layout.readType) * layout.componentCount;
		// location of the attribute in vertex (bytes)
		unsigned int offset = layout.attribIndex * attribSize;

		// set the attribute to single vertex
		glVertexAttribPointer(layout.location, layout.componentCount, layout.readType, layout.typeNormalization, attribSize, (const void*)offset);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	std::unique_ptr<char> VertexBuffer::getSubData(unsigned int location, unsigned int size) const {
		void* outDataCopy;

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glGetBufferSubData(GL_ARRAY_BUFFER, location * vertSize, vertCount * vertSize, outDataCopy);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return std::unique_ptr<char>((char*)outDataCopy);
	}

	void VertexBuffer::setVertex(unsigned int index, const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		/*
		* set data to a single vertex at a specific offset
		* with the corresponding size of the vertex
		* both vertex and offset are in bytes
		*/
		glBufferSubData(GL_ARRAY_BUFFER, index * vertSize, vertSize, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::setVertices(const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// offset of 0 since we are going to start
		// from the beginning of the buffer
		// this sets the data for the entire buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize * vertCount, data);
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
}