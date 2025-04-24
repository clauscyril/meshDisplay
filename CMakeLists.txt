cmake_minimum_required(VERSION 3.10)
project(meshDisplay)

set(CMAKE_CXX_STANDARD 20)

# === Paths ===
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/glfw")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad")

# === Executable ===
add_executable(meshDisplay
        main.cpp
)

# === GLAD ===
add_library(glad STATIC ${GLAD_DIR}/src/gl.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

# === GLFW ===
add_subdirectory(${GLFW_DIR})

# === Includes ===
target_include_directories(meshDisplay PRIVATE
        ${GLAD_DIR}/include
        ${GLFW_DIR}/include
)

# === Linking ===
target_link_libraries(meshDisplay PRIVATE
        glad
        glfw
)

# === Platform-specific OpenGL ===
if (WIN32)
    target_link_libraries(meshDisplay PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(meshDisplay PRIVATE OpenGL::GL)
endif()
