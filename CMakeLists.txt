cmake_minimum_required(VERSION 3.10)
project(meshDisplay)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/glfw")
# set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad")
# set(GLM_DIR "${CMAKE_SOURCE_DIR}/libs/glm")

add_executable(meshDisplay
        main.cpp
        main
)

target_include_directories(meshDisplay PRIVATE
        #${GLAD_DIR}/include
        ${GLFW_DIR}/include
       # ${GLM_DIR}
)

add_subdirectory(libs/glfw)

target_include_directories(meshDisplay PRIVATE
        libs/glfw/include
)

target_link_libraries(meshDisplay PRIVATE glfw)


if (WIN32)
    target_link_libraries(meshDisplay PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(meshDisplay PRIVATE OpenGL::GL)
endif()
