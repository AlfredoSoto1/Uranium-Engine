//#include <iostream>
//#include <thread>
//#include <GLFW/glfw3.h>
//
//class OpenGLApplication {
//public:
//    OpenGLApplication(int width, int height, const char* title) :
//        m_width(width),
//        m_height(height),
//        m_title(title),
//        m_window(nullptr),
//        m_shouldClose(false)
//    {}
//
//    bool init() {
//        // Initialize GLFW
//        if (!glfwInit()) {
//            std::cerr << "Failed to initialize GLFW\n";
//            return false;
//        }
//
//        // Set OpenGL version and profile
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//        // Create the window
//        m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
//        if (!m_window) {
//            std::cerr << "Failed to create GLFW window\n";
//            glfwTerminate();
//            return false;
//        }
//
//        // Make the OpenGL context current
//        glfwMakeContextCurrent(m_window);
//
//        return true;
//    }
//
//    void run() {
//        // Start the rendering thread
//        m_renderThread = std::thread(&OpenGLApplication::renderThreadFunc, this);
//
//        // Main loop
//        while (!m_shouldClose) {
//            // Poll for events
//            glfwPollEvents();
//        }
//
//        // Wait for the rendering thread to finish
//        m_renderThread.join();
//    }
//
//    void close() {
//        // Set the should-close flag to true
//        m_shouldClose = true;
//
//        // Wait for the rendering thread to finish
//        m_renderThread.join();
//
//        // Destroy the window
//        glfwDestroyWindow(m_window);
//        glfwTerminate();
//    }
//
//private:
//    int m_width;
//    int m_height;
//    const char* m_title;
//    GLFWwindow* m_window;
//    std::thread m_renderThread;
//    bool m_shouldClose;
//
//    void render() {
//        // Implement your rendering code here
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Swap buffers
//        glfwSwapBuffers(m_window);
//    }
//
//    void renderThreadFunc() {
//        // Make the OpenGL context current
//        glfwMakeContextCurrent(m_window);
//
//        // Main rendering loop
//        while (!m_shouldClose) {
//            // Call the render method
//            render();
//
//            // Poll for events
//            glfwPollEvents();
//        }
//    }
//};
//
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW\n";
//        return -1;
//    }
//
//    // Create the windows
//    OpenGLApplication app1(640, 480, "Window 1");
//    OpenGLApplication app2(640, 480, "Window 2");
//
//    // Initialize the windows
//    if (!app1.init() || !app2.init()) {
//        return -1;
//    }
//
//    // Run the windows in separate threads
//    std::thread thread1(&OpenGLApplication::run, &app1);
//    std::thread thread2(&OpenGLApplication::run, &app2);
//
//    // Wait for the threads to finish
//    thread1.join();
//    thread2.join();
//
//    // Clean up
//    app1.close();
//    app2.close();
//
//    return 0;
//}

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






#include <iostream>
#include <Core/Application/Application.h>

#include <Graphics/Display/Window.h>

#include <Scenes/Scene.h>
#include <Scenes/SceneMaster.h>

#include <DataStructures/Graphs/MeshGraph.h>

using namespace Uranium::Scenes;
using namespace Uranium::Core::Application;
using namespace Uranium::Graphics::Display;

class MyScene : public Scene {
public:
	void init() {

	}

	void dispose() {

	}

	void load() {

		struct Vertex {
			float x, y, z;
		};

	}

	void unload() {

	}

	void update() {

	}

	void render() {

	}
};

class MyApp : public ApplicationProgram {
public:

	std::shared_ptr<Window> window;
	std::shared_ptr<MyScene> scene1;

	void init() {
		window = std::make_shared<Window>("First display", 1280, 720);
		window->init();

		scene1 = std::make_shared<MyScene>();

		// share references mutually
		//scene1->linkScene(scene2);

		scene1->setTargetUpdate(30);
		scene1->setTargetFramerate(144);

		this->push(window, scene1);
	}

	void dispose() {
		window->dispose();
	}
};

#include <DataStructures/HashTables/HashTableOpenAddress.h>

using namespace Uranium::DataStructures::HashTables;
using namespace Uranium::DataStructures::Containers;

int main() {

	auto hashFunction = [](const unsigned int& num) {
		return ((num * 321) % 3);
	};

	HashTableOpenAddress<unsigned int> table = HashTableOpenAddress<unsigned int>(5, 0.75, hashFunction);

	table.put(table.hashOf(45), 45);
	table.put(table.hashOf(76), 76);
	table.put(table.hashOf(17), 17);
	table.put(table.hashOf(18), 18);
	table.put(table.hashOf(39), 39);

	std::optional<unsigned int> val = table.remove(table.hashOf(18), [](const unsigned int& obj) {
		return obj == 18;
		});

	val = table.remove(table.hashOf(18), [](const unsigned int& obj) {
		return obj == 18;
		});

	std::cout << "ended" << std::endl;

	/*
	* Start program
	*/
	//Application::start(std::make_shared<MyApp>());
}