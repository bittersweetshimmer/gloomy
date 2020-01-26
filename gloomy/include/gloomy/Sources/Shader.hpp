#pragma once
#include <cstddef>
#include <filesystem>
#include <vector>
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>

#include <nonstd/expected.hpp>

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Shader/Kind.hpp>
#include <gloomy/Enum/Texture/PixelFormat.hpp>
#include <gloomy/Enum/Texture/PixelDataType.hpp>
#include <gloomy/Utilities/NonCopyable.hpp>
#include <gloomy/Utilities/DynamicArray.hpp>

#include <stb/stb_image.h>

namespace gloomy::src {
	template<ShaderKind kind>
	struct Shader : public util::NonCopyable {
		constexpr static auto kind = kind;
		
		std::string source;

		Shader() = default;
		Shader(std::string&& source);
		~Shader();

		Shader(Shader&& other) = default;
		Shader<kind>& operator=(Shader&& other) noexcept {
			this->source = std::move(other.source);
		}

		inline Shader clone() const;

		static nonstd::expected<Shader, std::ifstream::failure> from_file(std::filesystem::path path);
	};

	template<ShaderKind kind>
	inline Shader<kind>::Shader(std::string&& source) : source(std::forward<std::string>(source)) {};

	template<ShaderKind kind>
	inline Shader<kind>::~Shader() {};
	
	template<ShaderKind kind>
	inline Shader<kind> Shader<kind>::clone() const {
		Shader<kind> other;
		other.source = this->source;
		return other;
	};

	template<ShaderKind kind>
	inline nonstd::expected<Shader<kind>, std::ifstream::failure> Shader<kind>::from_file(std::filesystem::path path) {
		Shader<kind> shader;

		std::ifstream file;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			file.open(path);
			std::stringstream string_stream;

			string_stream << file.rdbuf();
			file.close();

			shader.source = string_stream.str();

			return shader;
		}
		catch (std::ifstream::failure e) {
			assert(false && "I/O error.");

			return nonstd::make_unexpected(e);
		}
	};

	using VertexShader = Shader<gloomy::ShaderKind::VERTEX>;
	using FragmentShader = Shader<gloomy::ShaderKind::FRAGMENT>;
	using GeometryShader = Shader<gloomy::ShaderKind::GEOMETRY>;
}