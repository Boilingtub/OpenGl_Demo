#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "../glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

GLFWwindow* create_new_window(const char Title[], int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width,height,Title,NULL,NULL);
    if(window == NULL){
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return NULL;
    }
    glViewport(0,0,width,height);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSwapInterval(0);
    return window;
}

#endif
