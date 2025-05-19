#include "render/shader.h"
#include "render/vertexbuffers.h"
#include "Window/window.h"
#include <cmath>
#define SHADER_DIR(a) "shaders/" a
void processInput(GLFWwindow *window);

int main() {
    GLFWwindow* main_window = create_new_window("Mathicians",800,600); 

    while(!glfwWindowShouldClose(main_window)){
        // input
        processInput(main_window);

        //rendering commands hee 

        float vertices[] = {
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        unsigned int indices[] = { 0,1,2 };
      
        
        VertexBuffers vertexbuffers(vertices, sizeof(vertices)/sizeof(vertices[0]),
                                    indices,  sizeof(indices)/sizeof(indices[0])); 
        Shader basicShader(SHADER_DIR("vert.vert"),SHADER_DIR("frag.frag"));  
        vertexbuffers.draw(basicShader.ID);

        // check and call events and swap the buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
