#pragma once

#include <memory>

namespace Uranium::Graphics::Materials {
	class Assets;
	class Material;
}

namespace Uranium::Graphics::Shaders {

	class ShaderProgram;

	/*
	* This Shader Material is a 
	* container type that holds a reference
	* to the basics of a Material related to a shader program.
	* 
	* Contents:
	* 
	* Assets - contains the actual textures for the materials
	* Material - contains the material properties that will be loaded to uniforms
	* ShaderProgram - contains the required shaders compatible with material
	*/
	class ShaderMaterial {
	public:
		/*
		* custom alias
		*/
		using Assets = Materials::Assets;
		using Material = Materials::Material;

	public:
		/*
		* getters
		*/
		std::shared_ptr<Assets> getAssets() const;
		std::shared_ptr<Material> getMaterial() const;
		std::shared_ptr<ShaderProgram> getShaderProgram() const;

	public:
		/*
		* setters
		*/
		void setAssets(std::shared_ptr<Assets> assets);
		void setMaterial(std::shared_ptr<Material> material);
		void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	private:
		/*
		* private members
		*/
		std::shared_ptr<Assets> assets;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderProgram> shaderProgram;
	};
}