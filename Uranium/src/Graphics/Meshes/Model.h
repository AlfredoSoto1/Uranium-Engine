#pragma once

#include <memory>
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
		*/
		Model();
		
		/*
		*/
		virtual ~Model();
		
		/*
		*/
		void bind() const;
		
		/*
		*/
		void unbind() const;

		/*
		*/
		void bindToRender() const;
		void unbindToRender() const;

	public:
		/*
		* getters and setters
		*/

		/*
		*/
		operator unsigned int();

		/*
		*/
		void selectIndexBuffer(unsigned int iboSelected);

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