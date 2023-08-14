#pragma once

#include <vector>
#include <memory>

namespace Uranium::Graphics::Meshes {

	namespace UBuffers = Uranium::Graphics::Buffers;

	class UBuffers::IndexBuffer;
	class UBuffers::VertexBuffer;

	class Model {
	public:
		Model();
		virtual ~Model();

		operator unsigned int();

		unsigned int getIndexCount() const;

		void bind() const;
		void unbind() const;

		void enableAttribs() const;
		void disableAttribs() const;

		void bindIbo(const unsigned int _boundIbo);

	private:
		friend UBuffers::IndexBuffer;
		friend UBuffers::VertexBuffer;

		unsigned int vao;
		unsigned int boundIbo;

		mutable std::vector<unsigned int> attribs;
		mutable std::vector<std::shared_ptr<UBuffers::IndexBuffer>> ibos;
		mutable std::vector<std::shared_ptr<UBuffers::VertexBuffer>> vbos;

	};
}