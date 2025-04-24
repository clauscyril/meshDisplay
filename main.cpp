#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callback Function for errors handling GLFW
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }


    glfwSetErrorCallback(error_callback);

    // GLFW Options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Creating GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test GLFW + GLAD", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window the current context
    glfwMakeContextCurrent(window);

    // Load all OpenGL functions with GLAD
    if (const int version = gladLoadGL(glfwGetProcAddress); version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }


    // Set the background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
