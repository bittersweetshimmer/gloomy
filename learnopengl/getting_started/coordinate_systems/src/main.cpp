#include <array>

#include <gloomy/gloomy.hpp>
#include <learnopengl/learnopengl.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr auto SCR_WIDTH = 800;
constexpr auto SCR_HEIGHT = 600;

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

    learnopengl::loop(window, [&](double time) {
      gloomy::gl::clear_color(0.2f, 0.3f, 0.3f, 1.0f);
      gloomy::gl::clear(gloomy::BufferBit::COLOR | gloomy::BufferBit::DEPTH);

      program.bind();
      program.uniform("u_texture1").sampler(0);
      program.uniform("u_texture2").sampler(1);

      texture1.bind_at_slot(0);
      texture2.bind_at_slot(1);
      
      glm::mat4 view          = glm::mat4(1.0f);
      glm::mat4 projection    = glm::mat4(1.0f);
      projection = glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
      view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
      
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
