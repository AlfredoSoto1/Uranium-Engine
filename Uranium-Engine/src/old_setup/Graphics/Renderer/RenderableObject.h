#pragma once

#include <memory>

namespace Uranium::Graphics::Meshes {
	class Model;
}

namespace Uranium::Graphics::Materials {
	class Assets;
	class Material;
}

namespace Uranium::Graphics::Shaders {
	class ShaderProgram;
}

namespace Uranium::Graphics::Renderer {

	/*
	* Blueprint for abstract 
	* Renderable Object class
	* 
	*/
	class RenderableObject {
	public:
		/*
		* custom alias
		*/
		using Model = Meshes::Model;
		using Assets = Materials::Assets;
		using Material = Materials::Material;
		using ShaderProgram = Shaders::ShaderProgram;

	public:
		/*
		* getters
		*/
		std::shared_ptr<Model> getModel() const;
		std::shared_ptr<Assets> getAssets() const;
		std::shared_ptr<Material> getMaterial() const;
		std::shared_ptr<ShaderProgram> getShaderProgram() const;

	public:
		/*
		* setters
		*/
		void setModel(std::shared_ptr<Model> model);
		void setAssets(std::shared_ptr<Assets> assets);
		void setMaterial(std::shared_ptr<Material> material);
		void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	private:
		/*
		* private members
		*/
		std::shared_ptr<Model> model;
		std::shared_ptr<Assets> assets;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderProgram> shaderProgram;
	};
}