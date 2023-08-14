#pragma once

namespace Uranium::Renderer {

	class Texture {
	private:
		int width;
		int height;
		int channels;

		unsigned int texture;

		unsigned char* localImageData;

	public:
		Texture(const char* _path);
		virtual ~Texture();

		operator unsigned int();

		void bind(unsigned int _slot = 0) const;
		void unbind() const;

	};
}