#include "render/window.h"
#include "render/shader.h"
#include "render/vertexbuffers.h"
#include "render/texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define SHADER_DIR(a) "shaders/" a
#define TEXTURE_DIR(a) "assets/Textures/" a

void processInput(GLFWwindow *window);

int main() {
    GLFWwindow* main_window = create_new_window("Mathicians",800,600); 

        float vertices[] = {
            // positions            // colors              // texture coords
            0.5f,  0.5f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.0f, // bottom right
           -0.5f, -0.5f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f, // bottom left
           -0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 0.0f, /**/ 0.0f, 1.0f // top left
        };
        unsigned int indices[] = {
            0,1,3, 
            1,2,3
        };
        VertexBuffers vertexbuffers(vertices, 
                                    sizeof(vertices)/sizeof(vertices[0]),
                                    indices,
                                    sizeof(indices)/sizeof(indices[0])); 

        Texture tex0(TEXTURE_DIR("paint_abstract.jpg"));
        Texture tex1(TEXTURE_DIR("face_img.jpg"));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex0.texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex1.texture);

        Shader basicShader(SHADER_DIR("vert.vert"),SHADER_DIR("frag.frag"));   
        basicShader.use();
        basicShader.setInt("texture0",0);
        basicShader.setInt("texture1",1);

    while(!glfwWindowShouldClose(main_window)){
        glClear(GL_COLOR_BUFFER_BIT);
        // input
        processInput(main_window);

        //BOOK-PG-78

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans , glm::vec3(0.5,0.5,0.5));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0,0.0,1.0)); 
        float transform_time = glm::sin((float)glfwGetTime());
        trans = glm::translate(trans, glm::vec3(0.5f,transform_time,0.0f)); 
        glUniformMatrix4fv(glGetUniformLocation(basicShader.ID,"transform"),
                           1 , GL_FALSE, glm::value_ptr(trans));
            
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
