#pragma once
#include <gloomy/gl.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

namespace learnopengl {
    template<typename Fn>
    int glfw_context(int width, int height, const char* window_name, Fn callable) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        callable(*window);

        glfwTerminate();

        return 0;
    }

    template<typename Fn>
    void loop(GLFWwindow& window, Fn callable) {
        while (!glfwWindowShouldClose(&window)) {
            if (glfwGetKey(&window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(&window, true);

            callable();

            glfwSwapBuffers(&window);
            glfwPollEvents();
        }
    }
}