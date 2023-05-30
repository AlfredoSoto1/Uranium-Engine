#pragma once

#include "Renderer.h"

namespace Uranium::Graphics::Renderer {

	class ModelRenderer : public Renderer {
	public:
		ModelRenderer();
		virtual ~ModelRenderer();

		/*
		* Methods Overrided from renderer
		*/
		void draw() const override;
		void bindResources() const override;
		void prepareRenderStates() const override;
		void cleanUpRenderStates() const override;

	public:
		/*
		* getters and setters
		*/

	private:
		/*
		* private methods
		*/

	private:
		/*
		* private members
		*/

	};
}