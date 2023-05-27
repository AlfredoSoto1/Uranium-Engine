#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"

using namespace Uranium::Graphics::Meshes;

Model::Model() 
{
	
}

Model::~Model() {
	
}

void Model::bind() const {
	
}

void Model::unbind() const {
	
}

void Model::bindToRender() const {
	
}

void Model::unbindToRender() const {
	
}

Model::operator unsigned int() {
	return vao;
}

void Model::selectIndexBuffer(unsigned int iboSelected) {
	
}