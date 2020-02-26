#include <learnopengl/camera.hpp>

namespace learnopengl {
    struct CameraContext {
      learnopengl::Camera& camera;
      glm::vec2& last_position;
      bool& first_mouse;
    };
}