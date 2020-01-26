#include <gloomy/gloomy.hpp>
#include <sandbox/glfw_context.hpp>

int main(int argc, char* argv[]) {
    return sandbox::glfw_context(800, 800, "gloomy", [&](GLFWwindow& window) {
        using vec3 = std::array<gloomy::Float, 3>;
        using vec2 = std::array<gloomy::Float, 2>;

        using Position = gloomy::Attribute<struct PositionTag, vec3>;
        using Color = gloomy::Attribute<struct ColorTag, vec3>;
        using TextureCoord = gloomy::Attribute<struct TextureCoordTag, vec2>;

        using Attributes = gloomy::Attributes<Position, Color, TextureCoord>;
        using Vertex = gloomy::Vertex<Position, Color, TextureCoord>;
        using Index = gloomy::U8;

        const auto indices = std::array<Index, 6>{0, 1, 3, 1, 2, 3};
        const auto vertices = std::array<Vertex, 4>{
            Vertex{{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            Vertex{{ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
        };
        const auto image = gloomy::src::Image::from_file("assets/images/lenna.png").value();

        const auto index_buffer = gloomy::make_ready<gloomy::IndexBuffer>(indices);
        const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(vertices);
        const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());
        const auto texture = gloomy::make_ready<gloomy::Texture2D>(image);
        const auto program = gloomy::make_ready<gloomy::Program>(
            gloomy::make_ready<gloomy::VertexShader>(gloomy::src::VertexShader::from_file("assets/shaders/VertexShader.hlsl").value()),
            gloomy::make_ready<gloomy::FragmentShader>(gloomy::src::FragmentShader::from_file("assets/shaders/FragmentShader.hlsl").value())
        );
        
        gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer, index_buffer);

        while (!glfwWindowShouldClose(&window)) {
            gloomy::gl::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
            gloomy::gl::clear(gloomy::gl::COLOR_BUFFER_BIT);

            gloomy::use([&] { gloomy::draw_triangles<Index>(indices.size()); }, vertex_array, program, texture);

            glfwSwapBuffers(&window);
            glfwPollEvents();
        }
    });
}

int WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow
) {
    return main(__argc, __argv);
}