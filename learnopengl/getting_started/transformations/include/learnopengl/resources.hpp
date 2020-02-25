#pragma ocne

#include <optional>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <stb/stb_image.hpp>

#include <gloomy/Sources/Shader.hpp>
#include <gloomy/Sources/Image.hpp>

namespace learnopengl {
    inline std::optional<gloomy::src::Image> load_image(std::filesystem::path path) {
        int32_t width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        uint8_t* data = stbi_load(path.string().data(), &width, &height, &channels, 4);
        auto size = static_cast<size_t>(static_cast<int64_t>(width) * static_cast<int64_t>(height) * channels);
        auto pointer = std::unique_ptr<std::byte[]>(reinterpret_cast<std::byte*>(data));

        if (data == nullptr) return std::nullopt;
        return gloomy::src::Image{
            .data = std::move(pointer),
            .size = size,
            .width = width,
            .height = height
        };
    }
    
	template<gloomy::ShaderKind Kind>
	inline std::optional<gloomy::src::Shader<Kind>> load_shader(std::filesystem::path path) {
		std::ifstream file;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			file.open(path);
			std::stringstream string_stream;

			string_stream << file.rdbuf();
			file.close();

			return gloomy::src::Shader<Kind>(string_stream.str());
		}
		catch (std::ifstream::failure e) {
			assert(false && "I/O error.");

			return std::nullopt;
		}
	};

    inline std::optional<gloomy::src::Shader<gloomy::ShaderKind::VERTEX>> load_vertex_shader(std::filesystem::path path) {
        return load_shader<gloomy::ShaderKind::VERTEX>(path);
    }

    inline std::optional<gloomy::src::Shader<gloomy::ShaderKind::FRAGMENT>> load_fragment_shader(std::filesystem::path path) {
        return load_shader<gloomy::ShaderKind::FRAGMENT>(path);
    }
}