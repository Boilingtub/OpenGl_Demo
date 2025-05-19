#ifndef SHADER_H
#define SHADER_H

#include "../glad/glad.h" //glad for OpenGL headers
#include "../glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath) {//constructor
            //1. retrieve vertex/fragment shader source code form files
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vertexShaderFile;
            std::ifstream fragmentShaderFile;

            //ensure ifstream objects can throw exceptions
            vertexShaderFile.exceptions(std::ifstream::failbit |
                                        std::ifstream::badbit);
            fragmentShaderFile.exceptions(std::ifstream::failbit |
                                        std::ifstream::badbit);
            try {
                //open files
                vertexShaderFile.open(vertexPath);
                fragmentShaderFile.open(fragmentPath);

                std::stringstream vertexShaderStream, fragmentShaderStream;
                // read files buffer contents into streams
                vertexShaderStream << vertexShaderFile.rdbuf();
                fragmentShaderStream << fragmentShaderFile.rdbuf();
                //close file handlers
                vertexShaderFile.close();
                fragmentShaderFile.close();
                //convert stream into string
                vertexCode = vertexShaderStream.str();
                fragmentCode = fragmentShaderStream.str();
            }
            catch(std::ifstream::failure e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" 
                        << std::endl;
            }

            const char* vertexShaderCode = vertexCode.c_str();
            const char* fragmentShaderCode = fragmentCode.c_str();

            // 2. compile shaders 
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexShaderCode, NULL);
            glCompileShader(vertex);
            // print compile errors if any
            glGetShaderiv(vertex,GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                    infoLog << std::endl;
            }
           
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
            glCompileShader(fragment);
            glGetShaderiv(fragment,GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
                    infoLog << std::endl;
            }
            
            //shader program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            //print linking errors if any
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" <<
                    infoLog << std::endl;
            }

            //delete shadersl they are linked and no longere necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void use() { //activate / use shader
            glUseProgram(ID);
        }
        //utility set values for uniforms
        void setBool(const std::string &name, bool value) const {         
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
        }
    
        void setInt(const std::string &name, int value) const { 
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
        }
    
        void setFloat(const std::string &name, float value) const { 
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
        }
    
        void setVec2(const std::string &name, const glm::vec2 &value) const { 
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }

        void setVec2(const std::string &name, float x, float y) const { 
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
        }
    
        void setVec3(const std::string &name, const glm::vec3 &value) const { 
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
    
        void setVec3(const std::string &name, float x, float y, float z) const { 
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
        }
    
        void setVec4(const std::string &name, const glm::vec4 &value) const { 
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }

        void setVec4(const std::string &name, float x, float y, float z, float w) const { 
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
        }
    
        void setMat2(const std::string &name, const glm::mat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
    
        void setMat3(const std::string &name, const glm::mat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat4(const std::string &name, const glm::mat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }


};
#endif
