#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class TextureComparisonFunction {
		LEQUAL = gl::LEQUAL,
		GEQUAL = gl::GEQUAL,
		LESS = gl::LESS,
		GREATER = gl::GREATER,
		EQUAL = gl::EQUAL,
		NOTEQUAL = gl::NOTEQUAL,
		ALWAYS = gl::ALWAYS,
		NEVER = gl::NEVER
	};
}