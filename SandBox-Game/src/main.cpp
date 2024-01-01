
//#include <iostream>
//#include <AL/al.h>
//#include <AL/alc.h>
//
//using namespace std;
//
//int main() {
//    // Initialize OpenAL
//    ALCdevice* device = alcOpenDevice(NULL);
//    ALCcontext* context = alcCreateContext(device, NULL);
//    alcMakeContextCurrent(context);
//
//    // Load sound file
//    ALuint buffer;
//    alGenBuffers(1, &buffer);
//    ALenum format;
//    ALsizei size;
//    ALvoid* data;
//    ALsizei freq;
//    ALboolean loop = AL_FALSE;
//    alutLoadWAVFile("sound.wav", &format, &data, &size, &freq, &loop);
//    alBufferData(buffer, format, data, size, freq);
//    alutUnloadWAV(format, data, size, freq);
//
//    // Set up source
//    ALuint source;
//    alGenSources(1, &source);
//    alSourcei(source, AL_BUFFER, buffer);
//    alSourcef(source, AL_GAIN, 1.0f);
//
//    // Play sound
//    alSourcePlay(source);
//
//    // Wait for sound to finish playing
//    ALint state;
//    do {
//        alGetSourcei(source, AL_SOURCE_STATE, &state);
//    } while (state == AL_PLAYING);
//
//    // Clean up
//    alDeleteSources(1, &source);
//    alDeleteBuffers(1, &buffer);
//    alcDestroyContext(context);
//    alcCloseDevice(device);
//
//    return 0;
//}


//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <iostream>
//#include <Core/Application/Application.h>
//#include <Core/Math/vec2.h>
//#include <Core/Math/vec4.h>
//
//#include <Graphics/Display/Window.h>
//
//#include <Scenes/Scene.h>
//#include <Scenes/SceneMaster.h>
//
//#include <DataStructures/Graphs/MeshGraph.h>
//
//#include "Graphics/Meshes/Model.h"
//#include "Graphics/Buffers/VertexBuffer.h"
//#include "Graphics/Buffers/IndexBuffer.h"
//
//#include "Graphics/Shaders/Uniform.h"
//#include "Graphics/Shaders/Shader.h"
//#include "Graphics/Shaders/ShaderProgram.h"
//
//#include "Graphics/Renderer/SceneRenderer.h"
//
//#include "Cube.h"
//
//using namespace Uranium::Scenes;
//using namespace Uranium::Core::Application;
//using namespace Uranium::Core::Math;
//using namespace Uranium::Graphics::Display;
//using namespace Uranium::Graphics::Buffers;
//using namespace Uranium::Graphics::Meshes;
//using namespace Uranium::Graphics::Shaders;
//using namespace Uranium::Graphics::Renderer;
//
//class MyScene : public Scene {
//public:
//
//	ShaderProgram* program;
//
//	Model* model;
//
//	std::shared_ptr<Uniform<vec4>> color;
//
//	struct Vertex {
//		vec2 position;
//	};
//
//	/*
//	* load and unload dynamically
//	*/
//
//	void load() {
//
//		Vertex vertices[] = {
//			vec2(-0.5, -0.5),
//			vec2( 0.5, -0.5),
//			vec2( 0.5,  0.5)
//		};
//
//		unsigned int indices[] = {
//			0, 1, 2
//		};
//
//		model = new Model();
//
//		// create buffer
//		IndexBuffer indexBuf = IndexBuffer(*model, GL_STATIC_DRAW, sizeof(indices) / sizeof(unsigned int), indices);
//
//		// create buffer
//		VertexBuffer verBuff = VertexBuffer(*model, GL_STATIC_DRAW, sizeof(vertices) / sizeof(Vertex), sizeof(Vertex), vertices);
//
//		VertexBuffer::VertexAttribute attributes;
//		attributes.location = 0;
//		attributes.componentCount = 2;
//		attributes.readType = GL_FLOAT;
//		attributes.typeNormalization = GL_FALSE;
//		attributes.attribIndex = 0;
//
//		verBuff.setLayout(attributes);
//
//		Shader vertexShader = Shader("src/testV.glsl", GL_VERTEX_SHADER);
//		Shader fragmentShader = Shader("src/testF.glsl", GL_FRAGMENT_SHADER);
//
//		program = new ShaderProgram(vertexShader, fragmentShader);
//
//		// white color
//		*color = vec4(1.0);
//
//		program->setUniform("u_Color", color);
//
//		
//	}
//
//	void unload() {
//		delete model;
//		delete program;
//	}
//
//	/*
//	* update / render scene
//	*/
//
//	void update() {
//
//	}
//
//	void render() {
//		
//		// clear screen buffers
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glClearColor(0.1, 0.6, 0.85, 1.0);
//		
//		//getRenderer().drawCollection(entities);
//	}
//};
//
//class MyApp : public ApplicationProgram {
//public:
//
//	std::shared_ptr<Window> window;
//	std::shared_ptr<MyScene> scene1;
//
//	void init() {
//		window = std::make_shared<Window>("First display", 1280, 720);
//		window->init();
//
//		scene1 = std::make_shared<MyScene>();
//
//		// share references mutually
//		//scene1->linkScene(scene2);
//
//		scene1->setTargetUpdate(30);
//		scene1->setTargetFramerate(144);
//
//		this->push(window, scene1);
//	}
//
//	void dispose() {
//		window->dispose();
//	}
//};
//
//int main() {
//
//	/*
//	* Start program
//	*/
//	Application::start(std::make_shared<MyApp>());
//}

#include "Core/Application.h"
#include "Engine/BaseEngine.h"
#include "Platform/Display/Window.h"
#include "Platform/Display/OpenGLWindow.h"
#include "Platform/Monitor/Monitor.h"
#include "Platform/Monitor/MonitorHandler.h"
#include "Scene/Scene.h"

using namespace Uranium::Core;
using namespace Uranium::Scene;
using namespace Uranium::Engine;
using namespace Uranium::Platform::Display;
using namespace Uranium::Platform::Monitor;

class VoxelScene : public Scene {

public:

	VoxelScene() :
		Scene()
	{

	}

	~VoxelScene() {

	}

	void update() override {

	}

	void reset() override {

	}

	void load() override {
		//Vertex vertices[] = {
		//	vec2(-0.5, -0.5),
		//	vec2( 0.5, -0.5),
		//	vec2( 0.5,  0.5)
		//};

		//unsigned int indices[] = {
		//	0, 1, 2
		//};

		//model = new Model();

		//// create buffer
		//IndexBuffer indexBuf = IndexBuffer(*model, GL_STATIC_DRAW, sizeof(indices) / sizeof(unsigned int), indices);

		//// create buffer
		//VertexBuffer verBuff = VertexBuffer(*model, GL_STATIC_DRAW, sizeof(vertices) / sizeof(Vertex), sizeof(Vertex), vertices);

		//VertexBuffer::VertexAttribute attributes;
		//attributes.location = 0;
		//attributes.componentCount = 2;
		//attributes.readType = GL_FLOAT;
		//attributes.typeNormalization = GL_FALSE;
		//attributes.attribIndex = 0;

		//verBuff.setLayout(attributes);

		//Shader vertexShader = Shader("src/testV.glsl", GL_VERTEX_SHADER);
		//Shader fragmentShader = Shader("src/testF.glsl", GL_FRAGMENT_SHADER);

		//program = new ShaderProgram(vertexShader, fragmentShader);

		//// white color
		//*color = vec4(1.0);

		//program->setUniform("u_Color", color);
	}

	void unload() override {

	}

};

class GameApplication : public Application {
public:

	GameApplication() noexcept:
		Application()
	{
		// Initialize any member
	}

	~GameApplication() {
		// Delete any member
	}

	std::unique_ptr<Window> createWindow() override {
		auto window = std::make_unique<OpenGLWindow>();

		window->setDimension(glm::ivec2(1280, 720));
		window->center(MonitorHandler::getPrimary());

		return window;
	}
};

std::unique_ptr<Application> createApplication() {
	/*
	* Create a unique application
	*/
	return std::make_unique<GameApplication>();
}
