#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG
#include <string>

#include "RenderManager.h"

#include "BaseEngine.h"
#include "Core/Application.h"
#include "Platform/Display/Window.h"

namespace Uranium::Engine {

	RenderManager::RenderManager() noexcept :
		lastFrame(0),
		lastMeasuredFrame(0),
		elapsedRenderTime(0),

		frameCount(0),
		targetFramerate(10000) // unlimited
	{

		std::string vertex = R"(
			#version 450 core

			layout(location = 0) in vec2 position;
			
			void main() {
				gl_Position = vec4(position.xy, 0, 1);
			}
		)";

		std::string fragment = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;
			
			void main() {
				color = vec4(1.0, 0, 0, 1);
			}
		)";

		unsigned int program = glCreateProgram();

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		const char* vs_src = vertex.c_str();
		glShaderSource(vs, 1, &vs_src, nullptr);
		glCompileShader(vs);

		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fs_src = fragment.c_str();
		glShaderSource(fs, 1, &fs_src, nullptr);
		glCompileShader(fs);

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		glLinkProgram(program);
		glValidateProgram(program);

		int success;
		char infoLog[512];

		// Check vertex shader compilation
		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vs, 512, nullptr, infoLog);
			std::cerr << "Vertex shader compilation error:\n" << infoLog << std::endl;
		}

		// Check fragment shader compilation
		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fs, 512, nullptr, infoLog);
			std::cerr << "Fragment shader compilation error:\n" << infoLog << std::endl;
		}

		// Check program linking
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cerr << "Program linking error:\n" << infoLog << std::endl;
		}

		glDetachShader(program, vs);
		glDetachShader(program, fs);

		glDeleteShader(vs);
		glDeleteShader(fs);

		glUseProgram(program);

		float positions[6] = {
			-0.5f, -0.5f,
			 0.0f,  0.5f,
		  	 0.5f, -0.5f
		};

		unsigned int buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	}

	RenderManager::~RenderManager() {
	
	}

	void RenderManager::render() {
		double currentFrame = glfwGetTime() * 1000.0;
		double elapsedTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		elapsedRenderTime += elapsedTime;

		// Check to see if its time to render
		if (targetFramerate * elapsedRenderTime < 1000.0)
			return;

		elapsedRenderTime = 0.0;

		// Choose the type of rendering mode
		// and call it here to start rendering
		linearRender();

		//glfwSwapBuffers(Core::Application::instance().getBaseEngine().getWindow());
	
		frameCount++;

		if (glfwGetTime() * 1000.0 < lastMeasuredFrame + 1000.0)
			return;

#ifdef UR_DEBUG
		std::cout << "FPS: " << frameCount << std::endl;
#endif // UR_DEBUG

		frameCount = 0;
		lastMeasuredFrame = glfwGetTime() * 1000.0;
	}

	void RenderManager::linearRender() {
		// render scene here
		glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(1.0, 0.0, 0.0, 1.0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}