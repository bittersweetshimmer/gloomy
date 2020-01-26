#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class TextureParameterName : gl::Enum {
        DEPTH_STENCIL_TEXTURE_MODE = gl::DEPTH_STENCIL_TEXTURE_MODE,
        BASE_LEVEL = gl::TEXTURE_BASE_LEVEL,
        COMPARE_FUNC = gl::TEXTURE_COMPARE_FUNC,
        COMPARE_MODE = gl::TEXTURE_COMPARE_MODE,
        LOD_BIAS = gl::TEXTURE_LOD_BIAS,
        MIN_FILTER = gl::TEXTURE_MIN_FILTER,
        MAG_FILTER = gl::TEXTURE_MAG_FILTER,
        MIN_LOD = gl::TEXTURE_MIN_LOD,
        MAX_LOD = gl::TEXTURE_MAX_LOD,
        MAX_LEVEL = gl::TEXTURE_MAX_LEVEL,
        SWIZZLE_R = gl::TEXTURE_SWIZZLE_R,
        SWIZZLE_G = gl::TEXTURE_SWIZZLE_G,
        SWIZZLE_B = gl::TEXTURE_SWIZZLE_B,
        SWIZZLE_A = gl::TEXTURE_SWIZZLE_A,
        WRAP_S = gl::TEXTURE_WRAP_S,
        WRAP_T = gl::TEXTURE_WRAP_T,
        WRAP_R = gl::TEXTURE_WRAP_R,
		BORDER_COLOR = gl::TEXTURE_BORDER_COLOR,
        SWIZZLE_RGBA = gl::TEXTURE_SWIZZLE_RGBA
	};
}