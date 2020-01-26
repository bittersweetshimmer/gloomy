#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class Texture1DKind : Enum {
        TEXTURE_1D = gl::TEXTURE_1D,
        PROXY_1D = gl::PROXY_TEXTURE_1D
    };

    enum class Texture2DKind : Enum {
        TEXTURE_2D = gl::TEXTURE_2D,
        PROXY_2D = gl::PROXY_TEXTURE_2D,
        TEXTURE_1D_ARRAY = gl::TEXTURE_1D_ARRAY,
        PROXY_1D_ARRAY = gl::PROXY_TEXTURE_1D_ARRAY,
        TEXTURE_RECTANGLE = gl::TEXTURE_RECTANGLE,
        PROXY_RECTANGLE = gl::PROXY_TEXTURE_RECTANGLE,
        CUBE_MAP_POS_X = gl::TEXTURE_CUBE_MAP_POSITIVE_X,
        CUBE_MAP_NEG_X = gl::TEXTURE_CUBE_MAP_NEGATIVE_X,
        CUBE_MAP_POS_Y = gl::TEXTURE_CUBE_MAP_POSITIVE_Y,
        CUBE_MAP_NEG_Y = gl::TEXTURE_CUBE_MAP_NEGATIVE_Y,
        CUBE_MAP_POS_Z = gl::TEXTURE_CUBE_MAP_POSITIVE_Z,
        CUBE_MAP_NEG_Z = gl::TEXTURE_CUBE_MAP_NEGATIVE_Z,
        PROXY_CUBE_MAP = gl::PROXY_TEXTURE_CUBE_MAP
    };

    enum class Texture3DKind : Enum {
        TEXTURE_3D = gl::TEXTURE_3D,
        PROXY_3D = gl::PROXY_TEXTURE_3D,
        TEXTURE_2D_ARRAY = gl::TEXTURE_2D_ARRAY, 
        PROXY_2D_ARRAY = gl::PROXY_TEXTURE_2D_ARRAY
    };
}