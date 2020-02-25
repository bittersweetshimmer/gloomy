#pragma ocne

#include <optional>
#include <filesystem>
#include <sstream>
#include <fstream>

#include <gloomy/Sources/Shader.hpp>

namespace learnopengl {
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