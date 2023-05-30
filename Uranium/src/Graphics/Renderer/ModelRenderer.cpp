#define GLEW_STATIC
#include <GL/glew.h>

#include "ModelRenderer.h"
#include "Graphics/Shaders/ShaderProgram.h"

using namespace Uranium::Graphics::Shaders;
using namespace Uranium::Graphics::Renderer;

ModelRenderer::ModelRenderer() {
	
}
ModelRenderer::~ModelRenderer() {
	
}

void ModelRenderer::draw() const {
	// Handle Render here
	// bind before draw
	//model->bindToRender();

	// draw model
	//glDrawElements(GL_TRIANGLES, model->indexCount(), GL_UNSIGNED_INT, nullptr);

	// unbind after render
	//model->unbindToRender();
}

void ModelRenderer::bindResources() const {
	
}

void ModelRenderer::prepareRenderStates() const {
	
}

void ModelRenderer::cleanUpRenderStates() const {
	
}