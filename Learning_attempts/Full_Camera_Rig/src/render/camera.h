#ifndef CAMERA_H
#define CAMERA_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "window.h"
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

const float default_yaw = 0.0f;
const float default_pitch = 0.0f;
const float default_movementSpeed = 2.5f;
const float default_sensitivity = 0.1f;
const float default_fov = 45.0f;


class Camera {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldup;
        
        float movementSpeed;
        float yaw;
        float pitch;
        float sensitivity;
        float fov;

        Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
               float _yaw = default_yaw,
               float _pitch = default_fov) 
        : front(glm::vec3(0.0f, 0.0f, -1.0f)),
          movementSpeed(default_movementSpeed),
          sensitivity(default_sensitivity),
          fov(default_fov) {
            position = _position;
            worldup = _up;
            yaw = _yaw;
            pitch = _pitch;
            updateCameraVectors();
        }        

        glm::mat4 GetViewMatrix() {
            return glm::lookAt(position, position + front, up);
        }

        void ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch = true) {
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            if(constrainPitch) {
                if(pitch > 89.0f)
                    pitch = 89.0f;
                if(pitch < -89.0f)
                    pitch = -89.0f;
            }
            updateCameraVectors();
            //std::cout << "Camera orientation [" << yaw << "," << pitch << "]\n";
        }

        void ProcessMouseScroll(float yoffset) {
            fov -= (float)yoffset;
            if(fov < 1.0f)
                fov = 1.0f;
            if(fov > 120.0f)
                fov = 120.0f;
            //std::cout << "Camera fov = [" << fov << "]\n";
        }

        void ProcessKeyboard(Camera_Movement move_direction, float deltaTime) {
            float velocity = movementSpeed * deltaTime;
            if (move_direction == FORWARD)
                position += front * velocity;
            if (move_direction == BACKWARD)
                position -= front * velocity;
            if (move_direction == LEFT)
                position -= right * velocity;
            if (move_direction == RIGHT)
                position += right * velocity;
            if (move_direction == UP)
                position += up * velocity;
            if (move_direction == DOWN) 
                position -= up * velocity;

            //std::cout << "Camera position [" << position.x << "," << position.y << "," << position.z << "]\n";
        }

        void updateCameraVectors() {
            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(direction);
            right = glm::normalize(glm::cross(front, worldup));
            up = glm::normalize(glm::cross(right, front));
            //std::cout << "Camera front [" << front.x << "," << front.y << "," << front.z << "]\n"; 
        }
};


#endif
