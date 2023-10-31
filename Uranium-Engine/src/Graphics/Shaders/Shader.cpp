#define GLEW_STATIC
#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <malloc.h>
#include <memory>
#include <string>
#include <iostream>

#include "Shader.h"
#include "ShaderProgram.h"

using namespace Uranium::Graphics::Shaders;

Shader::Shader(const std::string& filePath, unsigned int shaderType) :
	filePath(filePath),
	sType(shaderType)
{
	// read the file and copy the source code
	// in the shader source variable
	toSourceCode(filePath, &shaderSource);

	// compile the shader with
	// the copy of the source code
	shaderId = compile(shaderSource);
}

Shader::Shader(const Shader& copy) :
	sType(copy.sType),
	filePath(filePath),
	shaderSource(copy.shaderSource),
	shaderId(copy.shaderId)
{
	
}
Shader::Shader(Shader&& move) noexcept:
	sType(move.sType),
	shaderId(move.shaderId),
	shaderSource(std::move(move.shaderSource)),
	filePath(std::move(move.filePath))
{
	
}

Shader::~Shader() {
	// delete the shader from memory
	glDeleteShader(shaderId);
}

Shader::operator const ShaderId() const {
	return shaderId;
}

inline unsigned int Shader::shaderType() const {
	return sType;
}

void Shader::toSourceCode(const std::string& filePath, std::string* sourceCode) {
	std::ifstream file;
	file.open(filePath, std::ios::in);

	if (!file.is_open()) {
		std::cout << "File at \"" << filePath << "\" \nwas not found." << std::endl;
		return;
	}

	std::string line;
	std::stringstream stream;
	// read every line from shader
	while (getline(file, line))
		stream << line << "\n";
	// append the extracted source code
	// from file path shader to out string
	sourceCode->append(stream.str());

	file.close();
}

ShaderId Shader::compile(const std::string& sourceCode) {
	// create shader
	GLuint shaderId = glCreateShader(sType);

	// get address of first character of source code
	// so that OpenGl knows where to start reading the code
	const char* src = &(sourceCode.c_str())[0];
	glShaderSource(shaderId, 1, &src, nullptr);

	// compile the shader
	glCompileShader(shaderId);

	// check if shader compiled successfully
	GLint result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result); 

	// If shader compiled successfully
	// return the shader ID
	if (result != GL_FALSE)
		return shaderId;

	// Display compilation error of shader type
	GLint messageLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);

	char* message = (char*)alloca(messageLength * sizeof(char));
	glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);

	const char* shaderType = nullptr;
	switch (sType) {
	case GL_VERTEX_SHADER:
		shaderType = "Vertex Shader";	break;
	case GL_FRAGMENT_SHADER:
		shaderType = "Fragment Shader";	break;
	case GL_COMPUTE_SHADER:
		shaderType = "Compute Shader";	break;
	case GL_GEOMETRY_SHADER:
		shaderType = "Geometry Shader";	break;
	}

	std::cout << "[Failed to compile shader] <type: " << shaderType << ">\n" << message << std::endl;
	
	// delete the shader
	glDeleteShader(shaderId);

	// default shader bound ID (0) error
	return 0;
}