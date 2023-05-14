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
