#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderable.h"
#include "GroupRenderer.h"

#include "Scenes/Cameras/Camera.h"
#include "Scenes/Objects/Entity.h"

#include "Graphics/Meshes/Model.h"
#include "Graphics/Meshes/RigidBody.h"

#include "Graphics/Materials/Assets.h"
#include "Graphics/Materials/Material.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/ShaderMaterial.h"

using namespace Uranium::Scenes::Cameras;
using namespace Uranium::Scenes::Objects;

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Shaders;
using namespace Uranium::Graphics::Renderer;
using namespace Uranium::Graphics::Materials;

GroupRenderer::GroupRenderer() {
	
}
GroupRenderer::~GroupRenderer() {
	
}

void GroupRenderer::draw() {
	// start shader here
	shaderProgram->start();
	
	// iterate over the group (model - entity list)
	for (auto&[shadedModel, renderables] : renderingGroup) {

		/*
		* unpack references as const reference
		* since we are not going to modify them
		*/
		const std::shared_ptr<Model>& model = shadedModel.first;
		
		const std::shared_ptr<Assets>& assets = shadedModel.second->getAssets();
		const std::shared_ptr<Material>& material = shadedModel.second->getMaterial();

		// bind model vao and index buffer
		model->bindToRender();

		// bind assets & load uniforms
		assets->bindResources();
		assets->loadUniforms();

		// bind material & load uniforms
		material->bindResources();
		material->loadUniforms();

		// prepare rendering states
		prepareRenderStates();

		// iterate over all entities
		for (auto& renderable : renderables) {

			// update rigid body here (Temporarely, must be done in update() method/thread)
			//entity.getRigidBody().update();

			// load uniforms from entity
			// transformation related
			renderable->loadUniforms();

			// draw the entity
			renderable->draw();
		}

		// clean rendering states HERE
		cleanUpRenderStates();

#ifdef _DEBUG
		material->unbindResources();
		assets->unbindResources();
#endif // _DEBUG
		model->unbind();
	}
	// stop shader 
	shaderProgram->stop();

	// Handle Render here
	// bind before draw
	//model->bindToRender();

	// draw model
	//glDrawElements(GL_TRIANGLES, model->indexCount(), GL_UNSIGNED_INT, nullptr);

	// unbind after render
	//model->unbindToRender();
}

void GroupRenderer::prepareRenderStates() {

}

void GroupRenderer::cleanUpRenderStates() {

}
