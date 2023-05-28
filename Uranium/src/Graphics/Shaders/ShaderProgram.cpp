#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include "Shader.h"
#include "ShaderProgram.h"

using namespace Uranium::Graphics::Shaders;

ShaderProgram::ShaderProgram()
{
	program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {

	// if program is invalid clear list of shaders
	if (program == 0) {
		shaders.clear();
		return;
	}

	// if list is not empty, detach the shaders
	if (!shaders.empty()) {
		for (const auto& shader : shaders)
			glDetachShader(program, *shader);
	}
	
	// delete shader program
	glDeleteProgram(program);
	
	shaders.clear();
}

ShaderProgram::operator const Program() const {
	return program;
}

void ShaderProgram::attachShader(const std::shared_ptr<Shader>& shader) {
	// dont add null shaders
	if (shader == nullptr)
		return;
	shaders.push_back(shader);
}

void ShaderProgram::init() {

	// no need to initialize program
	// if there are no shaders
	if (shaders.empty())
		return;

	// attach shaders
	for (const auto& shader : shaders)
		glAttachShader(program, *shader);

	// link the program
	link();

	// validate the program
	validate();

	if (program == 0)
		std::cout << "Current program is invalid (0)" << std::endl;
}

void ShaderProgram::link() const {

	// do not link if program is on default (0) - error
	if (program == 0)
		return;

	// link the program
	glLinkProgram(program);

	// verify if program could link successfully
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_FALSE)
		return;

	// Report any linking failure
	GLint infoLogLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

	GLchar* infoLog = new GLchar[infoLogLength];

	glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);

	std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
	
	// free error message
	delete[] infoLog;

	glDeleteProgram(program);

	// set program to be default (0) - error
	program = Program(0);
}

void ShaderProgram::validate() const {

	// do not validate if program is on default (0) - error
	if (program == 0)
		return;

	// validate the program
	glValidateProgram(program);

	// verify if program could validate successfully
	GLint validateStatus;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validateStatus);
	if (validateStatus != GL_FALSE)
		return;

	// Report any validation failure
	GLint infoLogLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	
	GLchar* infoLog = new GLchar[infoLogLength];
	glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);

	std::cout << "Shader program validation failed:\n" << infoLog << std::endl;
	
	// free error message
	delete[] infoLog;

	glDeleteProgram(program);

	// set program to be default (0) - error
	program = Program(0);
}

void ShaderProgram::start() const {
	// bind current shader
	glUseProgram(program);
}

void ShaderProgram::stop() const {
	// unbind current shader
	glUseProgram(0);
}

void ShaderProgram::queryUniformLocations() {
	// retrieve the uniform count inside the shader
	GLint uniformCount;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

	// gets max length of uniform name in program
	GLint maxCharLength;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLength);

	// create an array of size of the maximum length
	// a variable has inside the shader program
	GLchar* variableName = new GLchar[maxCharLength];
	
	GLuint type;
	GLint size, length;

	// get uniform location, uniform name and type
	for (GLuint i = 0; i < uniformCount; i++) {
		glGetActiveUniform(program, i, maxCharLength, &length, &size, &type, variableName);

		// store the uniform name and its type
		uniformNames[variableName] = type;
	}

	// free memory
	delete[] variableName;
}