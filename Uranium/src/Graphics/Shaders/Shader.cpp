#define GLEW_STATIC
#include <GL/glew.h>

#include "Shader.h"

using namespace Uranium::Graphics::Shaders;

Shader::Shader(const ShaderProgram& program, const std::string& filePath, unsigned int shaderType) :
	program(program),
	filePath(filePath)
{
	
}

Shader::Shader(const Shader& copy) :
	program(copy.program),
	sType(copy.sType),
	filePath(filePath),
	shaderId(copy.shaderId)
{
	
}
Shader::Shader(const Shader&& move) noexcept:
	program(move.program),
	sType(move.sType),
	shaderId(move.shaderId),
	filePath(std::move(move.filePath))
{
	
}

void Shader::dispose() const {
	
}

Shader::operator ShaderId() {
	return shaderId;
}

inline unsigned int Shader::shaderType() const {
	return sType;
}

void Shader::toSourceCode(const std::string& filePath, std::string* sourceCode) {
	
}

ShaderId Shader::compile(const std::string& sourceCode) {
	return 0;
}