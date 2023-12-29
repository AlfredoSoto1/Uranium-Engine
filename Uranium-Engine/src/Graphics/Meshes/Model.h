#pragma once

#include <vector>

namespace Uranium::Graphics::Buffers {
	class IndexBuffer;
	class VertexBuffer;
}

namespace Uranium::Graphics::Meshes {

	class Model final {
	public:
		/*
		* Constructs a model and assigns a proper vao
		* for any bound buffer that this model will use
		* to be rendered
		*/
		explicit Model() noexcept;
		
		/*
		* deletes all data from vao, including all
		* the buffers linked to it
		*/
		~Model();

	public:
		/*
		* binds/unbinds this instance of the vao created
		*/
		void bind() const;
		void unbind() const;
	
	public:
		/*
		* Returns the vao Id
		*/
		operator unsigned int();

		/*
		* Returns the total index count from the
		* current seleced ibo
		*/
		unsigned int indexCount() const;

		/*
		* selects the index buffer to
		* be used to render the vertex buffer from
		*/
		void selectIndexBuffer(unsigned int iboSelected);

	private:
		unsigned int vao;
		unsigned int iboSelected;

		std::vector<Buffers::IndexBuffer> ibos;
		std::vector<Buffers::VertexBuffer> vbos;
	};
}