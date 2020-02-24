#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class Texture1DKind : Enum {
        TEXTURE_1D = gl::raw::TEXTURE_1D,
        PROXY_1D = gl::raw::PROXY_TEXTURE_1D
    };

    enum class Texture2DKind : Enum {
        TEXTURE_2D = gl::raw::TEXTURE_2D,
        PROXY_2D = gl::raw::PROXY_TEXTURE_2D,
        TEXTURE_1D_ARRAY = gl::raw::TEXTURE_1D_ARRAY,
        PROXY_1D_ARRAY = gl::raw::PROXY_TEXTURE_1D_ARRAY,
        TEXTURE_RECTANGLE = gl::raw::TEXTURE_RECTANGLE,
        PROXY_RECTANGLE = gl::raw::PROXY_TEXTURE_RECTANGLE,
        CUBE_MAP_POS_X = gl::raw::TEXTURE_CUBE_MAP_POSITIVE_X,
        CUBE_MAP_NEG_X = gl::raw::TEXTURE_CUBE_MAP_NEGATIVE_X,
        CUBE_MAP_POS_Y = gl::raw::TEXTURE_CUBE_MAP_POSITIVE_Y,
        CUBE_MAP_NEG_Y = gl::raw::TEXTURE_CUBE_MAP_NEGATIVE_Y,
        CUBE_MAP_POS_Z = gl::raw::TEXTURE_CUBE_MAP_POSITIVE_Z,
        CUBE_MAP_NEG_Z = gl::raw::TEXTURE_CUBE_MAP_NEGATIVE_Z,
        PROXY_CUBE_MAP = gl::raw::PROXY_TEXTURE_CUBE_MAP
    };

    enum class Texture3DKind : Enum {
        TEXTURE_3D = gl::raw::TEXTURE_3D,
        PROXY_3D = gl::raw::PROXY_TEXTURE_3D,
        TEXTURE_2D_ARRAY = gl::raw::TEXTURE_2D_ARRAY, 
        PROXY_2D_ARRAY = gl::raw::PROXY_TEXTURE_2D_ARRAY
    };
}