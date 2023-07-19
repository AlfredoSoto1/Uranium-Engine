# Uranium-Engine

```c++
#include <iostream>
#include <thread>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Function called when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Function for rendering and handling events on the first window
void renderWindow1()
{

    // Create the first GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Window 1", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window 1" << std::endl;
        return;
    }

    // Set the current context to window 1
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glewExperimental = GL_TRUE;     // Enable GLEW experimental features
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        return;
    }

    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (glVersion != nullptr)
    {
        std::cout << "OpenGL version: " << glVersion << std::endl;
    }
    else
    {
        std::cerr << "Failed to retrieve OpenGL version" << std::endl;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
}

// Function for rendering and handling events on the second window
void renderWindow2()
{
    // Create the second GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Window 2", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window 2" << std::endl;
        return;
    }

    // Set the current context to window 2
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;     // Enable GLEW experimental features
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        return;
    }

    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (glVersion != nullptr)
    {
        std::cout << "OpenGL version: " << glVersion << std::endl;
    }
    else
    {
        std::cerr << "Failed to retrieve OpenGL version" << std::endl;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile (optional)
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create threads for rendering each window
    std::thread thread1(renderWindow1);
    std::thread thread2(renderWindow2);

    // Wait for the threads to finish
    thread1.join();
    thread2.join();

    // Cleanup
    glfwTerminate();
    return 0;
}
```
