#ifndef VERTEXBUFFERS_H
#define VERTEXBUFFERS_H

#include "../glad/glad.h"
#include "../glm/glm.hpp"
struct Vertex {
    float x,y,z,u,v;
    Vertex(float _x , float _y, float _z, float _u, float _v) {
        x = _x;
        y = _y;
        z = _z;
        u = _u;
        v = _v;
    }
};

class VertexBuffers {
    public:
        unsigned int VAO, VBO, EBO, index_count, vertex_count;

        VertexBuffers(Vertex vertices[],  int construct_vertex_count,
                      unsigned int indices[], int construct_index_count)     { //constructor
            //0. Bind Vertex Array Object
            unsigned int construct_VAO;
            glGenVertexArrays(1, &construct_VAO);
            glBindVertexArray(construct_VAO);

            //1. Copy verticies & indicies array in a buffer for OpenGL to use
            
            unsigned int construct_VBO;
            glGenBuffers(1, &construct_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, construct_VBO);
            glBufferData(GL_ARRAY_BUFFER,
                         construct_vertex_count*sizeof(vertices[0]), vertices,
                         GL_STATIC_DRAW);
            
            if( (indices != nullptr) && (construct_index_count > 0)) {
                unsigned int construct_EBO;
                glGenBuffers(1, &construct_EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, construct_EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                             construct_index_count*sizeof(indices[0]), indices,
                             GL_STATIC_DRAW);
                EBO = construct_EBO;
                index_count = construct_index_count;
            } else {
                EBO = 0;
                index_count = 0;
            }

            //2. set vertex attributes pointers
                //2.0 Position Attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void*)0);
            glEnableVertexAttribArray(0);
                //2.1 Texture Attributes
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

            VAO = construct_VAO;
            VBO = construct_VBO;
            vertex_count = construct_vertex_count;
        }

        void draw(unsigned int shader) {
            //4. Draw the Object
                //4.1 set Shader Program to to use
            glUseProgram(shader);
                //4.2 Bind vertex array object we want to use
            glBindVertexArray(VAO);
                //4.3 Use openGl function to draw to screen
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//draw wireframe
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//draw triangles

            if(index_count > 0) {
                glDrawElements(GL_TRIANGLES, index_count,
                               GL_UNSIGNED_INT, 0);

            }
            else {
                glDrawArrays(GL_TRIANGLES,0 ,vertex_count);
            }
                //4.4 Unbind Vertex array object
            glBindVertexArray(0);

        }

        ~VertexBuffers() {
            glDeleteBuffers(1,&VBO);
            glDeleteBuffers(1,&EBO);
            glDeleteVertexArrays(1,&VAO);
        }

};


#endif
