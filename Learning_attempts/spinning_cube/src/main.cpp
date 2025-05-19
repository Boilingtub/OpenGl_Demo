#include "Draw_Basics/draw_basics.h"
#include "Window/window.h"
#include <math.h>

void processInput(GLFWwindow *window);

int main() {
    GLFWwindow* main_window = create_new_window("Mathicians",800,600); 

    while(!glfwWindowShouldClose(main_window)){
        // input
        processInput(main_window);
        
        //rendering commands here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*float verticies_1[] = {-0.5,-0.5,1.0, 
                              -0.25,0.5,1.0,
                              -0.0,-0.5,1.0};
 
        float verticies_2[] = {0.0,-0.5,0.0,
                               -0.25,0.5,0.0,
                               0.25,0.5,0.0};
   
        float verticies_3[] = {0.0,-0.5,1.0,
                              0.25,0.5,1.0,
                              0.5,-0.5,1.0};
        
        unsigned int indices[] = {0,1,2,3};

        struct Vertex_Buffers vertex_buffers_1 = create_Vertex_Buffers(verticies_1,
                                                                     sizeof(verticies_1)/
                                                                     sizeof(verticies_1[0]),
                                                                     indices,
                                                                     sizeof(indices)/
                                                                     sizeof(indices[0]));
        unsigned int shaderProgram_1 = create_ShaderProgram("shaders/basics/uniform.vert",
                                                            "shaders/basics/uniform.frag");

        struct Vertex_Buffers vertex_buffers_2 = create_Vertex_Buffers(verticies_2,
                                                                     sizeof(verticies_2)/
                                                                     sizeof(verticies_2[0]),
                                                                     indices,
                                                                     sizeof(indices)/
                                                                     sizeof(indices[0]));
        unsigned int shaderProgram_2 = create_ShaderProgram("shaders/basics/uniform.vert",
                                                            "shaders/basics/uniform.frag");

        struct Vertex_Buffers vertex_buffers_3 = create_Vertex_Buffers(verticies_3,
                                                                     sizeof(verticies_3)/
                                                                     sizeof(verticies_3[0]),
                                                                     indices,
                                                                     sizeof(indices)/
                                                                     sizeof(indices[0]));
        unsigned int shaderProgram_3 = create_ShaderProgram("shaders/basics/uniform.vert",
                                                            "shaders/basics/uniform.frag");
       
        int vertexColorLocation;
        int vertexPosLocation;
        float timeValue = glfwGetTime();

        float fading_RedValue = (sin(timeValue));
        float fading_GreenValue = (sin(timeValue+0.5f));
        float fading_BlueValue = (sin(timeValue+1.0f));

        //if(fading_RedValue < 0) fading_RedValue *= -1;
        //if(fading_GreenValue < 0) fading_GreenValue *= -1;
        //if(fading_BlueValue < 0) fading_BlueValue *= -1;

        vertexColorLocation = glGetUniformLocation(shaderProgram_1, "ourColor");
        glUseProgram(shaderProgram_1);
        glUniform4f(vertexColorLocation, fading_RedValue, 0.0f, fading_BlueValue, 1.0f);*/

        /*vertexColorLocation = glGetUniformLocation(shaderProgram_2, "ourColor");
        glUseProgram(shaderProgram_2);
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, fading_BlueValue, 1.0f);

        vertexPosLocation = glGetUniformLocation(shaderProgram_2, "ourPos");
        glUseProgram(shaderProgram_2);
        glUniform4f(vertexPosLocation, fading_RedValue, fading_BlueValue, 1.0, 1.0);

        vertexPosLocation = glGetUniformLocation(shaderProgram_3, "ourPos");
        glUseProgram(shaderProgram_3);
        glUniform4f(vertexPosLocation, fading_BlueValue, 1.0 , 1.0,1.0);

        vertexColorLocation = glGetUniformLocation(shaderProgram_3, "ourColor");
        glUseProgram(shaderProgram_3);
        glUniform4f(vertexColorLocation, fading_RedValue, fading_GreenValue , fading_BlueValue, 1.0f);*/


        GLfloat vertices[] = {-0.5f, 0.5f, 0.0f,
                              -0.5f,-0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                               0.5f,-0.5f, 0.0f,
                              -0.5f, 0.5f,-0.5f,
                              -0.5f,-0.5f,-0.5f,
                               0.5f, 0.5f,-0.5f,
                               0.5f,-0.5f,-0.5f};

        unsigned int indices[] = {0, 2, 3, 0, 3, 1,
                                  2, 6, 7, 2, 7, 3,
                                  6, 4, 5, 6, 5, 7,
                                  4, 0, 1, 4, 1, 5,
                                  0, 4, 6, 0, 6, 2,
                                  1, 5, 7, 1, 7, 3};


        struct Vertex_Buffers vertex_buffers = create_Vertex_Buffers(vertices,
                                                                     sizeof(vertices)/
                                                                     sizeof(vertices[0]),
                                                                     indices,
                                                                     sizeof(indices)/
                                                                     sizeof(indices[0]));
        unsigned int shaderProgram = create_ShaderProgram("shaders/basics/cube_rotate.vert",
                                                          "shaders/basics/uniform.frag");
        
   
        float timeValue = glfwGetTime();

        float ThetaX = timeValue;
        float ThetaY = timeValue;
        float ThetaZ = timeValue/2;

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

        int vertexPosLocation = glGetUniformLocation(shaderProgram, "Theta");
        glUseProgram(shaderProgram);
        glUniform3f(vertexPosLocation, ThetaX, ThetaY, ThetaZ);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        draw_Vertex_Buffers(vertex_buffers, shaderProgram);
        
        //draw_Vertex_Buffers(vertex_buffers_1,shaderProgram_1);
        //draw_Vertex_Buffers(vertex_buffers_2,shaderProgram_2);
        //draw_Vertex_Buffers(vertex_buffers_3,shaderProgram_3);*/
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
