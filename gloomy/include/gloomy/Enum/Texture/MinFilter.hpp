#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class TextureMinFilter {
        NEAREST = gl::NEAREST,
        LINEAR = gl::LINEAR,
        NEAREST_MIPMAP_NEAREST = gl::NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST = gl::LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = gl::NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR = gl::LINEAR_MIPMAP_LINEAR
	};
}