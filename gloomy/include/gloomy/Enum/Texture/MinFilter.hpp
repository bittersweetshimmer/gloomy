#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class TextureMinFilter {
        NEAREST = gl::raw::NEAREST,
        LINEAR = gl::raw::LINEAR,
        NEAREST_MIPMAP_NEAREST = gl::raw::NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST = gl::raw::LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = gl::raw::NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR = gl::raw::LINEAR_MIPMAP_LINEAR
	};
}