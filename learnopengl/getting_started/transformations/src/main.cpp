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
    using Vec3 = std::array<gloomy::Float, 3>;
    using Vec2 = std::array<gloomy::Float, 2>;

    using Position = gloomy::Attribute<struct PositionTag, Vec3>;
    using TextureCoord = gloomy::Attribute<struct TextureCoordTag, Vec2>;

    using Attributes = gloomy::Attributes<Position, TextureCoord>;
    using Vertex = gloomy::Vertex<Position, TextureCoord>;
    using Index = gloomy::U32;

    const auto indices = std::array<Index, 6>{0, 1, 3, 1, 2, 3};
    const auto vertices = std::array<Vertex, 4>{
      Vertex{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}},
      Vertex{{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
      Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
      Vertex{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}}
    };

    const auto texture1 = gloomy::make_ready<gloomy::Texture2D>(learnopengl::load_image("assets/images/lenna.png").value());
    const auto texture2 = gloomy::make_ready<gloomy::Texture2D>(learnopengl::load_image("assets/images/awesomeface.png").value());

    const auto program = gloomy::make_ready<gloomy::Program>(
      gloomy::make_ready<gloomy::VertexShader>(learnopengl::load_vertex_shader("assets/shaders/VertexShader.hlsl").value()),
      gloomy::make_ready<gloomy::FragmentShader>(learnopengl::load_fragment_shader("assets/shaders/FragmentShader.hlsl").value())
    );

    const auto index_buffer = gloomy::make_ready<gloomy::IndexBuffer>(indices);
    const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(vertices);
    const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());

    gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer, index_buffer);

    learnopengl::loop(window, [&](double time) {
      gloomy::fill(0.2f, 0.3f, 0.3f, 1.0f);

      program.bind();
      program.uniform("u_texture1").sampler(0);
      program.uniform("u_texture2").sampler(1);
      
      auto transform = glm::mat4(1.0f);
      transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
      transform = glm::rotate(transform, static_cast<float>(time), glm::vec3(0.0f, 0.0f, 1.0f));

      program.uniform("u_transform").matrix<4>(glm::value_ptr(transform));

      texture1.bind_at_slot(0);
      texture2.bind_at_slot(1);

      vertex_array.bind();
      gloomy::draw_indexed<Index>(gloomy::PrimitiveKind::TRIANGLES, indices.size());
    });
  });
}

#if defined(_WIN32) || defined(__CYGWIN__)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nCmdShow) {
  return main(__argc, __argv);
}
#endif
