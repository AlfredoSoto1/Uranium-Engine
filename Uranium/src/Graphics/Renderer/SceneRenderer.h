#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium::Scenes::Cameras {
	class Camera;
}

namespace Uranium::Scenes::Objects {
	class Entity;
}

namespace Uranium::Graphics::Meshes {
	class Model;
}

namespace Uranium::Graphics::Materials {
	class Assets;
	class Material;
}

namespace Uranium::Graphics::Shaders {
	class ShaderProgram;
	class ShaderMaterial;
	class LoadableShader;
}

namespace Uranium::Graphics::Renderer {

	/*
	* Blueprint of Abstract SceneRenderer object
	*
	* This class operates and controls how renderable objects
	* should be rendered on to the screen
	*/
	class SceneRenderer {
	public:
		/*
		* Custom Alias
		*/
		using Model = Meshes::Model;

		using Assets = Materials::Assets;
		using Material = Materials::Material;

		using Camera = Scenes::Cameras::Camera;
		using Entity = Scenes::Objects::Entity;

		using ShaderProgram = Shaders::ShaderProgram;
		using ShaderMaterial = Shaders::ShaderMaterial;
		using LoadableShader = Shaders::LoadableShader;

		using ShadedModel = std::pair<std::shared_ptr<Model>, std::shared_ptr<ShaderMaterial>>;
		using EntityCollection = std::vector<std::shared_ptr<Entity>>;

		using DrawableCollection = std::unordered_map<ShadedModel, EntityCollection&>;

	public:
		/*
		* Default constructor
		*/
		SceneRenderer();

		/*
		* Default destructor
		*/
		virtual ~SceneRenderer();
		
	public:
		/*
		* Public methods
		*/
		/*
		* Links the shader program before
		* rendering. This is to specify what shader
		* program to use to render using any draw format
		*/
		void linkShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
		
		/*
		* Draws a collection of entities mapped to their
		* respective model and shader material
		*/
		void drawCollection(const DrawableCollection& drawableCollection) const;

	public:
		/*
		* Getters and setters
		*/

		/*
		* Returns true if program is linked
		* for rendering content
		*/
		bool isShaderProgramLinked() const;

	private:
		/*
		* Private methods
		*/

		/*
		* Unlinks the shader program. This
		* must be called after it finishes rendering
		*/
		void unlinkShaderProgram() const;

		/*
		* Bind shader material to
		* the current vao bound
		*/
		void bindShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial) const;

		/*
		* Unbind shader material after use
		*/
		void unbindShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial) const;

		/*
		* Updates the uniforms from shader material
		*/
		void updateMaterialUniforms(std::shared_ptr<ShaderMaterial> shaderMaterial) const;

		/*
		* Prepares the states before rendering
		*/
		void prepareRenderStates() const;

		/*
		* Resets the rendering states back to
		* default, so that they dont conflic with
		* possible next render call from another renderer
		*/
		void cleanUpRenderStates() const;

	private:
		/*
		* Protected members
		*/
		bool renderOnWireframe;

		mutable std::shared_ptr<ShaderProgram> shaderProgram;
	};
}