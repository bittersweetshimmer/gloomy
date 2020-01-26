#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class PixelFormat : Enum {
        RED = gl::RED,
        RED_GREEN = gl::RG,
        BGR = gl::BGR,
        BGRA = gl::BGRA,
        RGB = gl::RGB,
        RGBA = gl::RGBA,
        STENCIL_INDEX = gl::STENCIL_INDEX,
        DEPTH_COMPONENT = gl::DEPTH_COMPONENT,
        DEPTH_STENCIL = gl::DEPTH_STENCIL
    };
};