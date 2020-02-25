#include <array>

#include <gloomy/gloomy.hpp>
#include <learnopengl/learnopengl.hpp>

constexpr auto SCR_WIDTH = 800;
constexpr auto SCR_HEIGHT = 600;

int main(int argc, char *argv[]) {
  return learnopengl::glfw_context(SCR_WIDTH, SCR_HEIGHT, "gloomy", [&](GLFWwindow &window) {
    using Vec3 = std::array<gloomy::Float, 3>;
    
    using Position = gloomy::Attribute<struct PositionTag, Vec3>;
    
    using Vertex = gloomy::Vertex<Position>;
    using Attributes = gloomy::Attributes<Position>;
    using Index = gloomy::U32;

    std::array<Vertex, 4> vertices = {
        Vertex{{ 0.5f,  0.5f, 0.0f}},  // top right
        Vertex{{ 0.5f, -0.5f, 0.0f}},  // bottom right
        Vertex{{-0.5f, -0.5f, 0.0f}},  // bottom left
        Vertex{{-0.5f,  0.5f, 0.0f}}   // top left 
    };
    std::array<Index, 6> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    const auto program = gloomy::make_ready<gloomy::Program>(
      gloomy::make_ready<gloomy::VertexShader>(gloomy::src::VertexShader(R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
          gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
      )")),
      gloomy::make_ready<gloomy::FragmentShader>(gloomy::src::FragmentShader(R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
          FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
      )"))
    );
    
    const auto index_buffer = gloomy::make_ready<gloomy::IndexBuffer>(indices);
    const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(vertices);
    const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());

    gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer, index_buffer);

    learnopengl::loop(window, [&] {
      gloomy::fill(0.2f, 0.3f, 0.3f, 1.0f);
      gloomy::bind(vertex_array, program);
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
