#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Buffers;
 
Model::Model() :
	iboSelected(0) // first ibo as default
{
	// create vao id for 'this' model
	glGenVertexArrays(1, &vao);
}

Model::~Model() {
	// delete vbos and ibos
	for (VertexBuffer& vbo : vbos)
		glDeleteBuffers(1, &vbo.vbo);
	for (IndexBuffer& ibo: ibos)
		glDeleteBuffers(1, &ibo.ibo);
	// delete vao
	glDeleteVertexArrays(1, &vao);
	// delete all vbo objects
	vbos.clear();
	ibos.clear();
}

void Model::bind() const {
	glBindVertexArray(vao);
}

void Model::unbind() const {
	glBindVertexArray(0);
}

void Model::bindToRender() const {
	// bind vao
	glBindVertexArray(vao);
	// bind selected ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[iboSelected]);

	// enable attributes for each vbo
	for (VertexBuffer& vertexBuffer : vbos)
		vertexBuffer.enableAttribs();
}

void Model::unbindToRender() const {
	// bind selected ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// enable attributes for each vbo
	for (VertexBuffer& vertexBuffer : vbos)
		vertexBuffer.disableAttribs();
	
	// unbind vao
	glBindVertexArray(0);
}

Model::operator unsigned int() {
	return vao;
}

void Model::selectIndexBuffer(unsigned int iboSelected) {
	this->iboSelected = iboSelected;
}

unsigned int Model::indexCount() const {
	return ibos[iboSelected].indexCount();
}