#include <array>

#include <gloomy/gloomy.hpp>
#include <learnopengl/learnopengl.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr auto SCR_WIDTH = 800;
constexpr auto SCR_HEIGHT = 600;

namespace learnopengl {
  inline void setup_camera(learnopengl::CameraContext& context, GLFWwindow& window);
  inline void process_input(learnopengl::Camera& camera, float delta_time, GLFWwindow& window);
}

int main(int argc, char *argv[]) {
  return learnopengl::glfw_context(SCR_WIDTH, SCR_HEIGHT, "gloomy", [&](GLFWwindow &window) {
    gloomy::gl::enable(gloomy::Capability::DEPTH_TEST);

    using Position = gloomy::Attribute<struct PositionTag, glm::vec3>;
    using TextureCoord = gloomy::Attribute<struct TextureCoordTag, glm::vec2>;

    using Attributes = gloomy::Attributes<Position, TextureCoord>;
    using Vertex = gloomy::Vertex<Position, TextureCoord>;

    const auto cube = learnopengl::make_cube();
    const auto cube_positions = std::array<glm::vec3, 10>{
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    const auto texture1 = gloomy::make_ready<gloomy::Texture2D>(learnopengl::load_image("assets/images/lenna.png").value());
    const auto texture2 = gloomy::make_ready<gloomy::Texture2D>(learnopengl::load_image("assets/images/awesomeface.png").value());

    const auto program = gloomy::make_ready<gloomy::Program>(
      gloomy::make_ready<gloomy::VertexShader>(learnopengl::load_vertex_shader("assets/shaders/VertexShader.hlsl").value()),
      gloomy::make_ready<gloomy::FragmentShader>(learnopengl::load_fragment_shader("assets/shaders/FragmentShader.hlsl").value())
    );

    const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(cube);
    const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());

    gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer);

    auto camera = learnopengl::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    auto last_position = glm::vec2(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);
    bool first_mouse = true;
    auto context = learnopengl::CameraContext{camera, last_position, first_mouse};

    learnopengl::setup_camera(context, window);

    auto delta_time = 0.0f;
    auto last_frame = 0.0f;

    learnopengl::loop(window, [&](double time) {
      auto current_frame = static_cast<float>(time);
      delta_time = current_frame - last_frame;
      last_frame = current_frame;
      
      learnopengl::process_input(camera, delta_time, window);

      gloomy::gl::clear_color(0.2f, 0.3f, 0.3f, 1.0f);
      gloomy::gl::clear(gloomy::BufferBit::COLOR | gloomy::BufferBit::DEPTH);

      program.bind();
      program.uniform("u_texture1").sampler(0);
      program.uniform("u_texture2").sampler(1);

      texture1.bind_at_slot(0);
      texture2.bind_at_slot(1);
      
      glm::mat4 view = camera.get_view();
      glm::mat4 projection = glm::perspective(glm::radians(camera.get_fov()), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
      
      program.uniform("u_projection").matrix<4>(glm::value_ptr(projection));
      program.uniform("u_view").matrix<4>(glm::value_ptr(view));

      vertex_array.bind();

      for (auto i = 0; i < cube_positions.size(); i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cube_positions[i]);
        
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        
        program.uniform("u_model").matrix<4>(glm::value_ptr(model));
        gloomy::gl::draw_arrays(gloomy::PrimitiveKind::TRIANGLES, cube.size());
      }
    });
  });
}

#if defined(_WIN32) || defined(__CYGWIN__)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow) {
  return main(__argc, __argv);
}
#endif

inline void learnopengl::setup_camera(learnopengl::CameraContext& context, GLFWwindow& window) {
  glfwSetWindowUserPointer(&window, &context);

  glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
  glfwSetCursorPosCallback(&window, [](GLFWwindow* window, double xpos, double ypos) {
    auto context = static_cast<learnopengl::CameraContext*>(glfwGetWindowUserPointer(window));

    if (context->first_mouse) {
      context->last_position = glm::vec2(xpos, ypos);
      context->first_mouse = false;
    }

    float xoffset = xpos - context->last_position.x;
    float yoffset = context->last_position.y - ypos;
    context->last_position = glm::vec2(xpos, ypos);

    context->camera.process_mouse_movement(xoffset, yoffset);
  });
    
  glfwSetScrollCallback(&window, [](GLFWwindow* window, double xoffset, double yoffset) {
    auto context = static_cast<learnopengl::CameraContext*>(glfwGetWindowUserPointer(window));

    context->camera.process_mouse_scroll(yoffset);
  });
}

inline void learnopengl::process_input(learnopengl::Camera& camera, float delta_time, GLFWwindow& window) {
  if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS)
    camera.process_keyboard(learnopengl::CameraMovement::FORWARD, delta_time);
  else if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS)
    camera.process_keyboard(learnopengl::CameraMovement::BACKWARD, delta_time);
  else if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS)
    camera.process_keyboard(learnopengl::CameraMovement::LEFT, delta_time);
  else if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS)
    camera.process_keyboard(learnopengl::CameraMovement::RIGHT, delta_time);
}