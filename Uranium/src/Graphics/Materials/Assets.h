#pragma once

namespace Uranium::Graphics::Materials {

	class Assets {
	public:

		Assets();
		virtual ~Assets();

		void loadUniforms();

		void bindResources() const;
		void unbindResources() const;
	private:
		/*
		* private members
		*/

	};
}