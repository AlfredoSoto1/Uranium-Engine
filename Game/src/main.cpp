
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






//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <GLFW/glfw3.h>
//
//std::mutex mutex;
//std::condition_variable cv;
//bool renderingStopped = false;
//
//void renderingThread(GLFWwindow* window) {
//    // Set the rendering thread's OpenGL context
//    glfwMakeContextCurrent(window);
//
//    // Rendering loop
//    while (!renderingStopped) {
//        // Clear the framebuffer
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Render your objects here
//        std::cout << "render" << std::endl;
//        // Swap buffers
//        glfwSwapBuffers(window);
//
//        // Poll for events
//        glfwPollEvents();
//    }
//}
//
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return 1;
//    }
//
//    // Create the main OpenGL context
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Multi-threaded GLFW", nullptr, nullptr);
//    if (!window) {
//        std::cerr << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return 1;
//    }
//
//    // Spawn the rendering thread
//    std::thread thread(renderingThread, window);
//
//    // Handle input events in the main thread
//    while (!glfwWindowShouldClose(window)) {
//        // Handle input events here
//        std::cout << "main" << std::endl;
//        glfwPollEvents();
//    }
//
//    // Signal the rendering thread to stop
//    {
//        std::lock_guard<std::mutex> lock(mutex);
//        renderingStopped = true;
//    }
//    cv.notify_all();
//
//    // Wait for the rendering thread to finish
//    thread.join();
//
//    // Clean up and terminate GLFW
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}

//#include <iostream>
//#include <GLFW/glfw3.h>
//
//void errorCallback(int error, const char* description) {
//    std::cerr << "GLFW Error: " << description << std::endl;
//}
//
//void render(GLFWwindow* window, const std::string& windowName) {
//    glfwMakeContextCurrent(window);
//
//    while (!glfwWindowShouldClose(window)) {
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Render your objects here
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    std::cout << windowName << " rendering finished." << std::endl;
//}
//
//int main() {
//    // Set the error callback function
//    glfwSetErrorCallback(errorCallback);
//
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return 1;
//    }
//
//    // Create the first window
//    GLFWwindow* window1 = glfwCreateWindow(640, 480, "Window 1", nullptr, nullptr);
//    if (!window1) {
//        std::cerr << "Failed to create GLFW window 1" << std::endl;
//        glfwTerminate();
//        return 1;
//    }
//
//    // Create the second window
//    GLFWwindow* window2 = glfwCreateWindow(640, 480, "Window 2", nullptr, nullptr);
//    if (!window2) {
//        std::cerr << "Failed to create GLFW window 2" << std::endl;
//        glfwTerminate();
//        return 1;
//    }
//
//    // Render for the first window
//    render(window1, "Window 1");
//
//    // Render for the second window
//    render(window2, "Window 2");
//
//    // Clean up and terminate GLFW
//    glfwDestroyWindow(window1);
//    glfwDestroyWindow(window2);
//    glfwTerminate();
//
//    return 0;
//}

//#include <GLFW/glfw3.h>
//
//int main(void)
//{
//    GLFWwindow* window1;
//    GLFWwindow* window2;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window1 = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
//    if (!window1)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Create a second windowed mode window and its OpenGL context */
//    window2 = glfwCreateWindow(1280, 720, "World Hello", NULL, NULL);
//    if (!window2)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window1) && !glfwWindowShouldClose(window2))
//    {
//        /* Make the window's context current */
//        glfwMakeContextCurrent(window1);
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window1);
//
//        /* Make the second window's context current */
//        glfwMakeContextCurrent(window2);
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window2);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}



//#include <GLFW/glfw3.h>
//#include <iostream>
//
//const int RENDER_FPS = 5;
//const int UPDATE_FPS = 2;
//
//void renderMethod() {
//    // Your rendering logic here
//    //std::cout << "rendering"<< std::endl;
//}
//
//void updateMethod() {
//    // Your update logic here
//    std::cout << "updating"<< std::endl;
//}
//
//int main() {
//    // Initialize GLFW and create a window
//    if (!glfwInit()) {
//        // Handle initialization failure
//        return -1;
//    }
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Custom FPS Example", nullptr, nullptr);
//    if (!window) {
//        // Handle window creation failure
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    // Set the swap interval to control the render frame rate
//    glfwSwapInterval(0);
//
//    // Set up timing
//    double renderFrameTime = 1.0 / RENDER_FPS;
//    double updateFrameTime = 1.0 / UPDATE_FPS;
//    double previousRenderTime = glfwGetTime();
//    double previousUpdateTime = glfwGetTime();
//
//    double renderTimer = 0.0;
//    double updateTimer = 0.0;
//
//    int frames = 0;
//    int updates = 0;
//
//    // Main loop
//    while (!glfwWindowShouldClose(window)) {
//        // Process events
//        glfwPollEvents();
//
//        // Calculate elapsed time
//        double currentFrameTime = glfwGetTime();
//        double elapsedFrameTime = currentFrameTime - previousRenderTime;
//        previousRenderTime = currentFrameTime;
//
//        // Update render timer
//        renderTimer += elapsedFrameTime;
//
//        // Check if it's time to render
//        if (renderTimer >= renderFrameTime) {
//            // Perform rendering logic
//            renderMethod();
//
//            // Reset render timer
//            renderTimer = 0.0;
//
//            ++frames;
//
//            if (frames == RENDER_FPS) {
//                std::cout << "FPS: " << frames << std::endl;
//                frames = 0;
//            }
//        }
//
//        // Calculate elapsed time
//        elapsedFrameTime = currentFrameTime - previousUpdateTime;
//        previousUpdateTime = currentFrameTime;
//
//        // Update update timer
//        updateTimer += elapsedFrameTime;
//
//        // Check if it's time to update
//        if (updateTimer >= updateFrameTime) {
//            // Perform update logic
//            updateMethod();
//
//            // Reset update timer
//            updateTimer = 0.0;
//
//
//            ++updates;
//
//            if (updates == UPDATE_FPS) {
//                std::cout << "UPS: " << updates  << std::endl;
//                updates = 0;
//            }
//        }
//
//        // Swap buffers
//        glfwSwapBuffers(window);
//    }
//
//    // Cleanup
//    glfwTerminate();
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

// Define the necessay macros to launch the application
//#define UR_PLATFORM_WINDOWS
//
//#include <Uranium.h>
//#include <Core/UnitProgram.h>
//
//class MyGame : public Uranium::Core::Application {
//public:
//
//	using Position = Uranium::Utils::Position;
//	using Dimension = Uranium::Utils::Dimension;
//
//	using Window = Uranium::Graphics::Display::Window;
//	using WindowMode = Uranium::Graphics::Display::WindowMode;
//	using WindowProps = Uranium::Graphics::Display::WindowProps;
//	
//	using Monitor = Uranium::Graphics::Display::Monitor;
//
//	std::shared_ptr<Window> window;
//	std::shared_ptr<Window> second;
//
//	/*
//	* This constructor is the start of
//	* the main application.
//	*/
//	MyGame() :
//		Application()
//	{
//		Monitor monitor = Monitor::getPrimary();
//
//		window = std::make_shared<Window>();
//
//		WindowProps& props = window->getProps();
//
//		props.setGLVersion(4, 6);
//
//		props.setTitle("First Window Display :) 1");
//		props.setPosition(Position(0, 0));
//
//		WindowMode& winMode1 = window->getModes();
//
//		winMode1.setVisible(true);
//		winMode1.setResizable(true);
//		winMode1.setDecorated(true);
//		winMode1.setAlwaysOnTop(true);
//
//		// register window to display it
//		registerWindow(window);
//	}
//
//	/*
//	* This destructor is the end of the
//	* application where everything gets
//	* released from memory.
//	*/
//	~MyGame() {
//		
//		Uranium::Core::UnitProgram program;
//
//	}
//};
//
//// 
//// Uranium Engine's entry-point definition
////
//Uranium::Core::Application* Uranium::createApplication() {
//	// Create and return a new instance
//	// of the main application to be executed
//	return new MyGame();
//}

import Uranium.Core.Application;

#include <memory>
#include <iostream>

using namespace Uranium::Core;

class MyGame : public Application {
public:
	MyGame() :
		Application() 
	{
		std::cout << "Application created" << std::endl;
	}

	~MyGame() {

	}
};

std::unique_ptr<Application> createApplication() {
	return std::make_unique<MyGame>();
}
