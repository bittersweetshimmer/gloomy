#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace learnopengl {
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    struct Camera {
    private:
        constexpr static auto YAW           = -90.0f;
        constexpr static auto PITCH         =  0.0f;
        constexpr static auto SPEED         =  2.5f;
        constexpr static auto SENSITIVITY   =  0.1f;
        constexpr static auto FIELD_OF_VIEW =  45.0f;
    public:
        Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = Camera::YAW, float pitch = Camera::PITCH
        ) :
            position(position),
            up(up),
            world_up(up),
            yaw(yaw),
            pitch(pitch),
            front(glm::vec3(0.0f, 0.0f, -1.0f)),
            movement_speed(Camera::SPEED),
            mouse_sensitivity(Camera::SENSITIVITY),
            field_of_view(Camera::FIELD_OF_VIEW) {
                this->recalculate();
        }

        inline glm::mat4 get_view() const { return glm::lookAt(this->position, this->position + this->front, this->up); }

        void process_keyboard(CameraMovement direction, float dt) {
            float velocity = this->movement_speed * dt;
            if (direction == CameraMovement::FORWARD)
                this->position += this->front * velocity;
            else if (direction == CameraMovement::BACKWARD)
                this->position -= this->front * velocity;
            else if (direction == CameraMovement::LEFT)
                this->position -= this->right * velocity;
            else if (direction == CameraMovement::RIGHT)
                this->position += this->right * velocity;
        }

        void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true) {
            this->yaw   += xoffset * this->mouse_sensitivity;
            this->pitch += yoffset * this->mouse_sensitivity;

            if (constrain_pitch) { this->pitch = std::clamp(this->pitch, -89.0f, 89.0f); }

            this->recalculate();
        }

        void process_mouse_scroll(float yoffset) {
            this->field_of_view = std::clamp(this->field_of_view - yoffset, 1.0f, 90.0f);
        }

        inline float get_fov() const { return this->field_of_view; } 
            
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        
        glm::vec3 world_up;

        float yaw;
        float pitch;
        float movement_speed;
        float mouse_sensitivity;
        float field_of_view;

        void recalculate() {
            this->front = glm::normalize(glm::vec3(
                cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
                sin(glm::radians(this->pitch)),
                sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
            ));
            this->right = glm::normalize(glm::cross(this->front, this->world_up));
            this->up = glm::normalize(glm::cross(this->right, this->front));
        }
    };
}