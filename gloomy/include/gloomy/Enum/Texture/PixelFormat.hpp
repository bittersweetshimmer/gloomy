#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class PixelFormat : Enum {
        RED = gl::raw::RED,
        RED_GREEN = gl::raw::RG,
        BGR = gl::raw::BGR,
        BGRA = gl::raw::BGRA,
        RGB = gl::raw::RGB,
        RGBA = gl::raw::RGBA,
        STENCIL_INDEX = gl::raw::STENCIL_INDEX,
        DEPTH_COMPONENT = gl::raw::DEPTH_COMPONENT,
        DEPTH_STENCIL = gl::raw::DEPTH_STENCIL
    };
}