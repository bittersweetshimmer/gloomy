#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Shader/Kind.hpp>

namespace gloomy::src {
	template<ShaderKind Kind>
	struct Shader : public util::NonCopyable {
		constexpr static auto kind = Kind;
		
		Shader(const char* source) : source(source) {}
		Shader(const std::string& source) : source(source) {}
		Shader(std::string&& source) : source(std::forward<std::string>(source)) {}

		std::string source;
	};

	using VertexShader = Shader<gloomy::ShaderKind::VERTEX>;
	using FragmentShader = Shader<gloomy::ShaderKind::FRAGMENT>;
	using GeometryShader = Shader<gloomy::ShaderKind::GEOMETRY>;
}