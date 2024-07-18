#include <GL/glew.h>

#include "Model.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
 
namespace Uranium::Graphics::Meshes {

	Model::Model() noexcept :
		iboSelected(0) // first ibo as default
	{
		// create vao id for 'this' model
		glGenVertexArrays(1, &vao);
	}

	Model::~Model() {
		//// delete vbos and ibos
		//for (VertexBuffer& vbo : vbos)
		//	glDeleteBuffers(1, &vbo.vbo);
		//for (IndexBuffer& ibo: ibos)
		//	glDeleteBuffers(1, &ibo.ibo);
		//// delete vao
		glDeleteVertexArrays(1, &vao);
		// delete all vbo objects
		vbos.clear();
		ibos.clear();
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

	void Model::bind() const {
		glBindVertexArray(vao);
		
		ibos[iboSelected].bind();

		//for (VertexBuffer& vertexBuffer : vbos)
			//vertexBuffer.enableAttribs();
	}

	void Model::unbind() const {
		ibos[iboSelected].unbind();

		//for (VertexBuffer& vertexBuffer : vbos)
			//vertexBuffer.disableAttribs();

		glBindVertexArray(0);
	}
}