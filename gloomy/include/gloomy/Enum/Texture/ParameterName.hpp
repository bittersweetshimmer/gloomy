#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class TextureParameterName : gloomy::Enum {
        DEPTH_STENCIL_TEXTURE_MODE = gl::raw::DEPTH_STENCIL_TEXTURE_MODE,
        BASE_LEVEL = gl::raw::TEXTURE_BASE_LEVEL,
        COMPARE_FUNC = gl::raw::TEXTURE_COMPARE_FUNC,
        COMPARE_MODE = gl::raw::TEXTURE_COMPARE_MODE,
        LOD_BIAS = gl::raw::TEXTURE_LOD_BIAS,
        MIN_FILTER = gl::raw::TEXTURE_MIN_FILTER,
        MAG_FILTER = gl::raw::TEXTURE_MAG_FILTER,
        MIN_LOD = gl::raw::TEXTURE_MIN_LOD,
        MAX_LOD = gl::raw::TEXTURE_MAX_LOD,
        MAX_LEVEL = gl::raw::TEXTURE_MAX_LEVEL,
        SWIZZLE_R = gl::raw::TEXTURE_SWIZZLE_R,
        SWIZZLE_G = gl::raw::TEXTURE_SWIZZLE_G,
        SWIZZLE_B = gl::raw::TEXTURE_SWIZZLE_B,
        SWIZZLE_A = gl::raw::TEXTURE_SWIZZLE_A,
        WRAP_S = gl::raw::TEXTURE_WRAP_S,
        WRAP_T = gl::raw::TEXTURE_WRAP_T,
        WRAP_R = gl::raw::TEXTURE_WRAP_R,
        BORDER_COLOR = gl::raw::TEXTURE_BORDER_COLOR,
        SWIZZLE_RGBA = gl::raw::TEXTURE_SWIZZLE_RGBA
    };
}
