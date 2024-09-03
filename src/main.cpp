#include "render/window.h"
#include "render/shader.h"
#include "render/vertexbuffers.h"
#include "render/texture.h"
#include "render/camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define SHADER_DIR(a) "shaders/" a
#define TEXTURE_DIR(a) "assets/Textures/" a 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

//timing
float deltaTime = 0.0f; //Time between frames
float lastFrame = 0.0f; //Time of last frame

Camera camera(glm::vec3(0.0f, -5.0f, 5.0f));
float lastX, lastY;
bool firstMouse = true;

int main() {
    std::ios_base::sync_with_stdio(false);
    //BOOK PG 96
    int screen_width = 800;
    int screen_height = 600;
    const char Title[] = "Osmium Engine Test Run"; 
    GLFWwindow* main_window = create_new_window(Title,screen_width,screen_height);
    glfwGetWindowSize(main_window, &screen_width, &screen_height);
    glfwMakeContextCurrent(main_window);
    glfwSetCursorPosCallback(main_window, mouse_callback);
    glfwSetScrollCallback(main_window, scroll_callback);
    
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       
    Vertex vertices[] = {
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),

        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),

        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),

        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),

        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),

        Vertex( -0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( -0.5f,  0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f)
    };
    VertexBuffers vertexbuffers(vertices, 
                                sizeof(vertices)/(sizeof(float)*5),
                                nullptr,
                                0); 
    Texture tex0(TEXTURE_DIR("paint_abstract.jpg"));
    Texture tex1(TEXTURE_DIR("lava_solidified.jpg"));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0.texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1.texture);

    Shader basicShader(SHADER_DIR("vert.vert"),SHADER_DIR("frag.frag"));   
    basicShader.use();
    basicShader.setInt("texture0",0);
    basicShader.setInt("texture1",1);



    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, -1.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f),
        glm::vec3( 1.5f, 0.2f, -10.5f),
        glm::vec3( -4.0f, 5.0f, -8.5f),
        glm::vec3( 5.5f, -6.2f, -13.5f),
        glm::vec3( 2.5f, 5.2f, -9.5f),
        glm::vec3( -5.5f, -2.2f, -11.5f),
        glm::vec3( 3.5f, 5.2f, -10.5f),
    }; 

    while(!glfwWindowShouldClose(main_window)){
        // input
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
         
        //printf("FPS: %f\n",1/deltaTime);
        
        //input
        processInput(main_window);
        //clear previous frame from screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        glfwGetWindowSize(main_window, &screen_width, &screen_height);

        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), 
                                      (float)screen_width/(float)screen_height,
                                      0.1f,  100.0f);
        basicShader.setMat4("projection",projection);

        basicShader.setMat4("view", camera.GetViewMatrix());

        for(unsigned int i = 0; i < 16; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle= 20.0f * (i+1);
            float t_x = glm::sin(glfwGetTime());
            float t_z = glm::cos(glfwGetTime());
            
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(0.5f*t_x, 0.3f, 0.5f*t_z));
        
            basicShader.setMat4("model", model);
             
            vertexbuffers.draw(basicShader.ID);
        }
        // check and call events and swap the buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
