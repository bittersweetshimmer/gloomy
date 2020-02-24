#include <array>

#include <gloomy/gloomy.hpp>
#include <learnopengl/learnopengl.hpp>

constexpr auto SCR_WIDTH = 800;
constexpr auto SCR_HEIGHT = 600;

int main(int argc, char *argv[]) {
  return learnopengl::glfw_context(SCR_WIDTH, SCR_HEIGHT, "gloomy", [&](GLFWwindow &window) {
    using Vec3 = std::array<gloomy::Float, 3>;
    using Vec2 = std::array<gloomy::Float, 2>;

    using Position = gloomy::Attribute<struct PositionTag, Vec3>;
    using Color = gloomy::Attribute<struct ColorTag, Vec3>;
    using TextureCoord = gloomy::Attribute<struct TextureCoordTag, Vec2>;

    using Attributes = gloomy::Attributes<Position, Color, TextureCoord>;
    using Vertex = gloomy::Vertex<Position, Color, TextureCoord>;
    using Index = gloomy::U32;

    const auto indices = std::array<Index, 6>{0, 1, 3, 1, 2, 3};
    const auto vertices = std::array<Vertex, 4>{
      Vertex{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
      Vertex{{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
      Vertex{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
      Vertex{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };
    const auto image = learnopengl::load_image("assets/images/lenna.png").value();

    const auto texture = gloomy::make_ready<gloomy::Texture2D>(image);
    const auto program = gloomy::make_ready<gloomy::Program>(
      gloomy::make_ready<gloomy::VertexShader>(learnopengl::load_vertex_shader("assets/shaders/VertexShader.hlsl").value()),
      gloomy::make_ready<gloomy::FragmentShader>(learnopengl::load_fragment_shader("assets/shaders/FragmentShader.hlsl").value())
    );

    const auto index_buffer = gloomy::make_ready<gloomy::IndexBuffer>(indices);
    const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(vertices);
    const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());

    gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer, index_buffer);

    learnopengl::loop(window, [&] {
      gloomy::fill(0.2f, 0.3f, 0.3f, 1.0f);
      gloomy::bind(vertex_array, program, texture);
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
