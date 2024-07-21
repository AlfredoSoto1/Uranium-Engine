#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include "Shader.h"
#include "Uniform.h"
#include "ShaderProgram.h"

using namespace Uranium::Graphics::Shaders;

ShaderProgram::~ShaderProgram() {
	
	/*
	* deletes 'this' current shader program
	* detaching automatically the shaders
	* attached to 'this' program
	*/
	glDeleteProgram(program);
}

ShaderProgram::operator const Program() const {
	return program;
}

void ShaderProgram::setUniform(const std::string& uniformName, std::shared_ptr<BaseUniform> baseUniform) {
	/*
	* shader program will remember the base uniform
	* from this list whenever it needs to set a value
	* to the named uniform given as parameter
	*/
	uniformVariables.push_back(baseUniform);
}

void ShaderProgram::attachShader(const Shader& shader) {
	// attach manually
	glAttachShader(program, shader);
}

void ShaderProgram::detachShader(const Shader& shader) {
	// detach manually
	glDetachShader(program, shader);
}

void ShaderProgram::create() {
	// create shader program
	program = glCreateProgram();
}

void ShaderProgram::init() {
	// link the program
	link();

	// validate the program
	validate();

	// check if program is invalid
	if (program == 0) {
		return;
		std::cout << "Current program is invalid (0)" << std::endl;
	}

	queryUniformLocations();
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
	
	UniformType type;
	GLint size, length;

	start();
	// get uniform location, uniform name and type
	for (GLuint i = 0; i < uniformCount; i++) {
		glGetActiveUniform(program, i, maxCharLength, &length, &size, &type, variableName);

		// create uniform props
		auto& typeLocation = programUniforms[variableName];
		
		// store the location as first
		typeLocation.first = glGetUniformLocation(program, variableName);

		// store the type as second
		typeLocation.second = type;
	}
	stop();

	// free memory
	delete[] variableName;
}
