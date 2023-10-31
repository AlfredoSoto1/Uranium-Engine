#pragma once

#include <vector>

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"

namespace Uranium::Graphics::Meshes {

	class Model {
	public:
		/*
		* custom alias
		*/
		using IndexBuffer = Buffers::IndexBuffer;
		using VertexBuffer = Buffers::VertexBuffer;

	public:
		/*
		* Constructs a model and assigns a proper vao
		* for any bound buffer that this model will use
		* to be rendered
		*/
		Model();
		
		/*
		* deletes all data from vao, including all
		* the buffers linked to it
		*/
		virtual ~Model();
		
		/*
		* binds the vao
		*/
		void bind() const;
		
		/*
		* unbinds the vao
		*/
		void unbind() const;

		/*
		* It binds the vao
		* and the proper index buffers and
		* enables the attributes before rendering
		* it also has an unbind method that unbinds all
		* these actions done by the bindToRender()
		*/
		void bindToRender() const;
		void unbindToRender() const;

	public:
		/*
		* getters and setters
		*/

		/*
		* Returns the vao Id
		*/
		operator unsigned int();

		/*
		* selects the index buffer to 
		* be used to render the vertex buffer from
		*/
		void selectIndexBuffer(unsigned int iboSelected);

		/*
		* Returns the total index count from the
		* current seleced ibo
		*/
		unsigned int indexCount() const;

	private:
		/*
		* friends with other classes
		*/
		friend IndexBuffer;
		friend VertexBuffer;

	private:
		/*
		* private members
		*/
		unsigned int vao;
		unsigned int iboSelected;

		mutable std::vector<IndexBuffer> ibos;
		mutable std::vector<VertexBuffer> vbos;
	};
}