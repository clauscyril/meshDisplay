#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callback Function for errors handling GLFW
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
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

    float vertices[] = {-0.2f, -0.2f, -0.2f, 0.2f, 0.2f, 0.f};

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);

    std::string vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main() {\n"
        "   gl_Position = position;\n"
        "}";

    std::string fragmentShader =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.5, 0.0, 1.0);\n"
        "}";

    unsigned int program = CreateShader(vertexShader, fragmentShader);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
