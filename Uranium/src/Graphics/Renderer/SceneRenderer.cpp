#define GLEW_STATIC
#include <GL/glew.h>

#include "SceneRenderer.h"

#include "Scenes/Cameras/Camera.h"
#include "Scenes/Objects/Entity.h"

#include "Graphics/Meshes/Model.h"
#include "Graphics/Meshes/RigidBody.h"

#include "Graphics/Materials/Assets.h"
#include "Graphics/Materials/Material.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/ShaderMaterial.h"
#include "Graphics/Shaders/LoadableShader.h"

using namespace Uranium::Scenes::Cameras;
using namespace Uranium::Scenes::Objects;

using namespace Uranium::Graphics::Meshes;
using namespace Uranium::Graphics::Shaders;
using namespace Uranium::Graphics::Renderer;
using namespace Uranium::Graphics::Materials;

SceneRenderer::SceneRenderer() :
	shaderProgram(nullptr),
	renderOnWireframe(false)
{

}

SceneRenderer::~SceneRenderer() {

}

void SceneRenderer::linkShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
	this->shaderProgram = shaderProgram;
}

void SceneRenderer::unlinkShaderProgram() const {
	this->shaderProgram = nullptr;
}

bool SceneRenderer::isShaderProgramLinked() const {
	return shaderProgram != nullptr;
}

void SceneRenderer::drawCollection(const DrawableCollection& drawableCollection) const {

	// if shader program is not linked,
	// we can't draw the collection
	if (!isShaderProgramLinked())
		return;

	// start shader here
	shaderProgram->start();

	// iterate over the group (model - entity list)
	for (auto& [shadedModel, entities] : drawableCollection) {

		// unpack references as const reference
		// since we are not going to modify them
		const std::shared_ptr<Model>& model = shadedModel.first;
		const std::shared_ptr<ShaderMaterial>& shaderMaterial = shadedModel.second;

		// bind model vao and index buffer
		model->bindToRender();

		bindShaderMaterial(shaderMaterial);

		// prepare rendering states
		prepareRenderStates();

		// iterate over all entities
		for (auto& entity : *entities) {

			// update rigid body here (Temporarely, must be done in update() method/thread)
			//entity.getRigidBody().update();

			// update entity's uniforms
			std::static_pointer_cast<LoadableShader>(entity)->updateUniforms(shaderProgram);

			// Draw model
			if (renderOnWireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLES, entity->getModel()->indexCount(), GL_UNSIGNED_INT, nullptr);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glDrawElements(GL_TRIANGLES, entity->getModel()->indexCount(), GL_UNSIGNED_INT, nullptr);
			}
		}

		// clean rendering states HERE
		cleanUpRenderStates();

		// unbind resources *optional*
		unbindShaderMaterial(shaderMaterial);

		model->unbind();
	}
	// stop shader 
	shaderProgram->stop();

	// unlink the program
	unlinkShaderProgram();
}

void SceneRenderer::prepareRenderStates() const {
	glEnable(GL_DEPTH_TEST);
}

void SceneRenderer::cleanUpRenderStates() const {
	glDisable(GL_DEPTH_TEST);
}

void SceneRenderer::bindShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial) const {
	// bind material and assets resources
	shaderMaterial->getAssets()->bindResources();
	shaderMaterial->getMaterial()->bindResources();
}

void SceneRenderer::unbindShaderMaterial(std::shared_ptr<ShaderMaterial> shaderMaterial) const {
	// unbinds the resources
	// this method is completely
	// optional to call
	shaderMaterial->getAssets()->unbindResources();
	shaderMaterial->getMaterial()->unbindResources();
}

void SceneRenderer::updateMaterialUniforms(std::shared_ptr<ShaderMaterial> shaderMaterial) const {
	// update the uniform data for the 
	// shader material provided as parameter
	std::static_pointer_cast<LoadableShader>(shaderMaterial->getAssets())->updateUniforms(shaderProgram);
	std::static_pointer_cast<LoadableShader>(shaderMaterial->getMaterial())->updateUniforms(shaderProgram);
}
