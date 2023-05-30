#pragma once

namespace Uranium::Graphics::Materials {
	
	class Material {
	public:
		Material();
		virtual ~Material();

		void loadUniforms();

		void bindResources() const;
		void unbindResources() const;
	private:

	};
}